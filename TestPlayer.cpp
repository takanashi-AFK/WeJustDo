#include "TestPlayer.h"
#include "Engine/Model.h"
#include "TestStage.h"

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
	Model::DebugMove(&transform_);

	//PlayerObjectから下方向に対して伸びる直線を用意
	RayCastData data;
	data.start = transform_.position_;
	data.dir = XMFLOAT3(0, -1, 0);
	Model::RayCast((*(TestStage*)FindObject("TestStage")).GetModelHandle(), &data); //レイを発射

	if (data.hit){
		//オブジェクトの下にオブジェクトが存在する場合の処理
		if (true);//オブジェクト同士が接触している場合の処理
		else;	//オブジェクト同士が接触していない場合の処理
	}
	else {
		//オブジェクトの足元にオブジェクトが存在しない場合の処理
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
