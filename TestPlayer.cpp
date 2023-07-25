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

		//着地させる
		transform_.position_.y -= (data.dist - 0.5f) ;

		//２つのベクトルから内積を取得する
		XMVECTOR dot = XMVector3Dot(XMLoadFloat3(&underNormal),data.normal);
		
		//ベクトルの長さを取得する
		float length1 = XMVectorGetX(XMVector3Length(XMLoadFloat3(&underNormal)));
		float length2 = XMVectorGetX(XMVector3Length(data.normal));

		//角度(Radian)を計算する
		float angle = acos(XMVectorGetX(dot) / (length1 * length2));
		
		//ラジアン角からディグリー角に変換する
		float Deg = XMConvertToDegrees(angle);

		//角度分、ｚ回転させる
		transform_.rotate_.z = Deg;
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
