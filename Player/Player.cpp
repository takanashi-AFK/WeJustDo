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
	//���݂̏�Ԃ̓��쏈��
	pState_->Update(this);
}

void Player::Draw()
{
}

void Player::Release()
{
}
