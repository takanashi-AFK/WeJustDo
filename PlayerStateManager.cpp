#include "PlayerStateManager.h"

//コンストラクタ
PlayerStateManager::PlayerStateManager()
{
	//各状態インスタンスを用意
	ASSIGN(pStanding_,new StandingState);
	ASSIGN(pRunning_, new RunningState);
	ASSIGN(pJumping_, new JumpingState);
	ASSIGN(pMovie_,new MovieState);

	//立ち状態で初期化
	ASSIGN(playerState_,pStanding_);
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
void PlayerStateManager::ChangeState(PlayerState* change, Player* _p)
{
	//状態を変更する
	playerState_ = change;

	//開始処理を行う
	playerState_->Enter(_p);
}
