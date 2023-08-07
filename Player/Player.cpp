#include "Player.h"
#include "State/PlayerStateManager.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player")
{
}

void Player::Initialize()
{
}

void Player::Update()
{
	//Œ»Ý‚Ìó‘Ô‚Ì“®ìˆ—
	pState_->Update(this);
}

void Player::Draw()
{
}

void Player::Release()
{
}
