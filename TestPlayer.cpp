#include "TestPlayer.h"
#include "Engine/Model.h"

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
}

void TestPlayer::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TestPlayer::Release()
{
}
