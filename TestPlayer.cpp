#include "TestPlayer.h"
#include "Engine/Model.h"
#include "TestStage.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

TestPlayer::TestPlayer(GameObject* parent)
	:GameObject(parent,"TestPlayer")
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
	Model::DebugMove(&transform_,0.05f);

	Camera::SetPosition(transform_.position_.x, 5.0f, -10.0f);
	Camera::SetTarget(transform_.position_.x,3.0f,0.0f);

	//PlayerObjectから下方向に対して伸びる直線を用意
	RayCastData data;
	data.start = transform_.position_;
	XMFLOAT3 underNormal = {0.0f,-1.0f,0.0f};
	data.dir = underNormal;
	Model::RayCast((*(TestStage*)FindObject("TestStage")).GetModelHandle(), &data); //レイを発射

	if (data.hit) {
		//オブジェクトの下にオブジェクトが存在する場合の処理
		transform_.position_.y -= (data.dist - 0.5f) ;

		//プレイヤーの下に伸びる法線ベクトルと、ポリゴンの法線ベクトルの内積をとる
		XMVECTOR dot = XMVector3Dot(XMLoadFloat3(&underNormal),-data.pNormal);
		
		//内積の結果から角度を取得
		float angle = acos(XMVectorGetX(dot));

		//ラジアン->度
		float Deg = XMConvertToDegrees(angle);

		//角度分、ｚ回転させる
		//transform_.rotate_.z = Deg;
	}
	else {
		//オブジェクトの足元にオブジェクトが存在しない場合の処理
		transform_.rotate_.z = 0;
		transform_.position_.y-= 0.1f;
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
