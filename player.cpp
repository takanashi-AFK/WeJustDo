#include "player.h"
#include "Engine/Model.h"
#include"Engine/Input.h"
#include "yuka.h"
#include"asiba.h"
#include"Engine/Camera.h"
#include"Engine/Debug.h"


//コンストラクタ
player::player(GameObject* parent)
	: GameObject(parent, "player"),hModel_(-1)
{
}

//初期化
void player::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("DebugCollision/SphereCollider.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { 0.0f,1.8f,0.0f };
	transform_.rotate_.y = 180;
}

//更新
void player::Update()
{
	std::vector<Model::DaH> DaHList;
	Camera::SetPosition(XMFLOAT3(transform_.position_.x + 5, 3.5f, -15.0f));
	Camera::SetTarget(XMFLOAT3(transform_.position_.x + 5, 1.5f, 0.0f));

	//PlayerObjectから下方向に対して伸びる直線を用意
	RayCastData DownRayData;
	DownRayData.start = transform_.position_;
	DownRayData.dir = { 0.0f,-1.0f,0.0f };

	DaHList = Model::GetHitModelList(&DownRayData, hModel_);
	Model::DaH nearDist = Model::SortList(DaHList);

	RayCastData UpRayData;
	UpRayData.start = transform_.position_;
	UpRayData.dir = { 0.0f,1.0f,0.0f };

	XMFLOAT3 playerNormal = { 0.0f,-1.0f,0.0f };
	//XMVECTOR wPlayerNormal = XMVector3Transform(XMLoadFloat3(&playerNormal), GetWorldMatrix());
	
	Model::RayCast((*(asiba*)FindObject("asiba")).GetModelHandle(), &UpRayData); //レイを発射
/*
	if (transform_.position_.y >= 2.5f) {
		Model::RayCast((*(asiba*)FindObject("asiba")).GetModelHandle(), &DownRayData); //レイを発射
	}
	else
	{
		Model::RayCast((*(yuka*)FindObject("yuka")).GetModelHandle(), &DownRayData); //レイを発射
	}
*/


	if (DownRayData.hit) {
		//オブジェクトの下にオブジェクトが存在する場合の処理

		//ジャンプの処理
		if (Input::IsKeyDown(DIK_SPACE) && isJumping == false)
		{
			flame = 0;
			//【ジャンプの上方向の加速度＝〇〇】
			moveY += 0.5f;

			//【ジャンプしているフラグを立てる】
			isJumping = true;
		}

		//【地に足がついていない時】
		else if (isJumping == true)
		{
			flame++;
			//【重力加速度＝〇〇】
			moveY -= 0.02f;

			//【もしも下方向の加速度が一定値〇〇以下であれば
			if (moveY <= -0.3f)
			{
				//【下方向の加速度を〇〇に固定する】
				moveY = -0.3f;
			}
		}

		//【プレイヤーと地面の位置が一定距離〇〇になったら】
		if ((DownRayData.dist <= 0.4f))
		{
			//【上下方向の加速度は０】
			moveY = 0.0f;

			//【地に足がついている】
			isJumping = false;
		}

		//【地に足がついているとき】
		if (isJumping == false)
		{
			//【レイの当たった高さに自身を置く】
			transform_.position_.y -= (nearDist.Dist - 1);
		}

		//【プレイヤーのY座標の移動】
		transform_.position_.y += moveY;

	}
	else {
		//オブジェクトの足元にオブジェクトが存在しない場合の処理
		transform_.rotate_.z = 0;

		moveY -= 0.02f;
		transform_.position_.y += moveY;
	}


	if (UpRayData.hit&&UpRayData.dist<=1.5f)
	{
		moveY -= 0.2;
		//【プレイヤーのY座標の移動】
		transform_.position_.y += moveY;
	}


	if (Input::IsKey(DIK_A))
	{
		transform_.position_.x -= 0.5;
	}
	if (Input::IsKey(DIK_D))
	{
		transform_.position_.x += 0.5;
	}

	if (Input::IsKeyDown(DIK_V))
	{
		Debug::Log(flame);
	}

}

//描画
void player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void player::Release()
{
}
