#include "PlayerStateManager.h"
#include "StandingState.h"

PlayerStateManager::PlayerStateManager()
{
	StatePool_.push_back(new StandingState);//�������
	nowState_ = StatePool_[eState_Standing];
}

void PlayerStateManager::Update(Player* player)
{
	nowState_->Update(player);
	//�W�����v��ԂɕύX
}

void PlayerStateManager::Enter(Player* player)
{
}