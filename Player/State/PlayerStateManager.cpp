#include "PlayerStateManager.h"
#include "StandingState.h"

PlayerStateManager::PlayerStateManager()
{
	StatePool_.push_back(new StandingState);//立ち状態
	nowState_ = StatePool_[eState_Standing];
}

void PlayerStateManager::Update(Player* player)
{
	nowState_->Update(player);
	//ジャンプ状態に変更
}

void PlayerStateManager::Enter(Player* player)
{
}
