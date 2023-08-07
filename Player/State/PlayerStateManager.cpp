#include "PlayerStateManager.h"
#include "StandingState.h"

PlayerStateManager::PlayerStateManager()
{
	StatePool_.push_back(new StandingState);//—§‚¿ó‘Ô
	nowState_ = StatePool_[eState_Standing];
}

void PlayerStateManager::Update(Player* player)
{
	nowState_->Update(player);
	//ƒWƒƒƒ“ƒvó‘Ô‚É•ÏX
}

void PlayerStateManager::Enter(Player* player)
{
}
