#include "PlayerStateManager.h"

PlayerStateManager::PlayerStateManager()
{
	pStanding_ = new StandingState;
	pRunning_ = new RunningState;
	playerState_ = pStanding_;
}

void PlayerStateManager::Update(Player* _p)
{
	//Œ»İ‚Ìó‘Ô‚ÌXV
	playerState_->Update(_p);

	
}

void PlayerStateManager::HandleInput(Player* _p)
{

}

void PlayerStateManager::Enter(Player* _p)
{
	playerState_->Enter(_p);
}

void PlayerStateManager::ChangeState(PlayerState* change, Player* _p)
{
	playerState_ = change;
	playerState_->Enter(_p);
}
