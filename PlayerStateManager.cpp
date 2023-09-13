#include "PlayerStateManager.h"

//コンストラクタ
PlayerStateManager::PlayerStateManager()
{
	ASSIGN(pStanding_, new StandingState);
	ASSIGN(pRunning_, new RunningState);
	ASSIGN(pJumping_, new JumpingState);
	ASSIGN(pMovie_, new MovieState);
	ASSIGN(pDead_, new DeadState);
	ASSIGN(pJet_, new JetState);
	//立ち状態で初期化
	ASSIGN(playerState_,pStanding_);
}
PlayerStateManager::~PlayerStateManager()
{
	delete pStanding_;
	delete pRunning_;
	delete pJumping_;
	delete pMovie_;
	delete pDead_;
	delete pJet_;
}
//更新
void PlayerStateManager::Update(Player* _p)
{
	//現在の状態の更新
	playerState_->Update(_p);
}

//入力処理
void PlayerStateManager::HandleInput(Player* _p)
{

}

//開始
void PlayerStateManager::Enter(Player* _p)
{
	//現在の状態の開始処理
	playerState_->Enter(_p);
}

//状態遷移
void PlayerStateManager::ChangeState(PlayerState* change, Player* _p, bool flag)
{
	prevState_ = playerState_;
	if (prevState_ != change)
	{
		//状態を変更する
		playerState_ = change;
		if (flag) {
			//開始処理を行う
			playerState_->Enter(_p);
		}
	}

}

void PlayerStateManager::ChangeState(PlayerState* change, Player* player)
{
	ChangeState(change, player,true);
}
