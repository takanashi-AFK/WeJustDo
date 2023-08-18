#include "Player.h"
#include "../Engine/Model.h"
#include "State/PlayerStateManager.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player")
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Models/Player.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { 0.0f,1.8f,0.0f };
	transform_.rotate_.y = 180;
}

void Player::Update()
{

	//Œ»Ý‚Ìó‘Ô‚Ì“®ìˆ—
	pState_->Update(this);

}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

}

void Player::Release()
{
}
