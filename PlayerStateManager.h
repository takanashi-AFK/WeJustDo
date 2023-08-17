#pragma once
#include "PlayerState.h"
#include "StandingState.h"
#include "RunningState.h"

class Player;

class PlayerStateManager : public PlayerState
{
public:
	PlayerState* playerState_;

	//各状態変数
	StandingState* pStanding_;
	RunningState* pRunning_;
public:
	//コンストラクタ
	PlayerStateManager();

	//更新
	virtual void Update(Player* _p) override;

	//入力によって状態変化する
	virtual void HandleInput(Player* player)override;

	//状態変化したとき一回だけ呼ばれる関数
	virtual void Enter(Player* player)override;

	//状態チェンジ用
	void ChangeState(PlayerState* change, Player* player);
};

