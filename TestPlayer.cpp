#include "TestPlayer.h"
#include "Engine/Model.h"
#include "TestStage.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Direct3D.h"

TestPlayer::TestPlayer(GameObject* parent)
	:GameObject(parent, "TestPlayer"),isJumping(false),moveY(0),Deg(0)
{
}

void TestPlayer::Initialize()
{
	hModel_ = Model::Load("Models/Player.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { 0.0f,1.8f,0.0f };
	transform_.rotate_.y = 180;

	
}

void TestPlayer::Update()
{
	//Model::DebugMove(&transform_,0.15f);

	Camera::SetPosition(transform_.position_.x+5, 3.5f, -15.0f);
	Camera::SetTarget(transform_.position_.x + 5,5.5f,0.0f);

	//PlayerObjectから下方向に対して伸びる直線を用意
	RayCastData data;
	data.start = transform_.position_;
		
	XMFLOAT3 playerNormal = {0.0f,-1.0f,0.0f};
	//XMVECTOR wPlayerNormal = XMVector3Transform(XMLoadFloat3(&playerNormal), GetWorldMatrix());

	data.dir = { 0.0f,-1.0f,0.0f };
	Model::RayCast((*(TestStage*)FindObject("TestStage")).GetModelHandle(), &data); //レイを発射

	if (data.hit) {
		//オブジェクトの下にオブジェクトが存在する場合の処理

		//ジャンプの処理
		if (Input::IsKeyDown(DIK_SPACE) && isJumping == false)
		{
			//【ジャンプの上方向の加速度＝〇〇】
			moveY += 0.3f;

			//【ジャンプしているフラグを立てる】
			isJumping = true;
		}

		//【地に足がついていない時】
		else if(isJumping == true)
		{
			//【重力加速度＝〇〇】
			moveY -= 0.02f;
			transform_.rotate_.z = 0.0f;

			//【もしも下方向の加速度が一定値〇〇以下であれば
			if (moveY <= -0.3f)
			{
				//【下方向の加速度を〇〇に固定する】
				moveY = -0.3f;
			}
		}

		//【プレイヤーと地面の位置が一定距離〇〇になったら】
		if ((data.dist <= 0.4f))
		{
			//【上下方向の加速度は０。】
			moveY = 0.0f;
			
			//【地に足がついている】
			isJumping = false;
		}

		//【地に足がついているとき】
		if (isJumping == false)
		{
			//【レイの当たった高さに自身を置く】
			transform_.position_.y -= (data.dist-0.5f);
		}

		//【プレイヤーのY座標の移動】
		transform_.position_.y += moveY;
		

		//２つのベクトルから内積を取得する
		XMVECTOR dot = XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&playerNormal)), XMVector3Normalize(data.normal));

		//角度(Radian)を計算する(狭い方の角度を取得)
		float angle = acos(XMVectorGetX(dot));

		//ラジアン角からディグリー角に変換する
		Deg = XMConvertToDegrees(angle);
		
		//外積から負の値か正の値かを判断する
		if (XMVectorGetZ(XMVector3Cross(data.normal, XMLoadFloat3(&playerNormal))) < 0) 
		{
			Deg *= -1;//負の値の場合は-1をかける
		}

		//角度分、ｚ回転させる
		transform_.rotate_.z = (Deg);
	}
	else {
		//オブジェクトの足元にオブジェクトが存在しない場合の処理
		transform_.rotate_.z = 0;

		moveY -= 0.02f;
		transform_.position_.y += moveY;
	}

}

void TestPlayer::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

}

void TestPlayer::Release()
{
}

//https://github.com/takanashi-AFK/WeJustDo/tree/Jump_Test