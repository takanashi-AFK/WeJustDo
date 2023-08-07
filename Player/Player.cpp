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
	//現在の状態の動作処理
	pState_->Update(this);
}

void Player::Draw()
{
}

void Player::Release()
{
}
