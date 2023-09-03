#pragma once
#include "PlayerState.h"

/// <summary>
/// プレイヤーの待機状態(立ち状態)を管理するクラス
/// </summary>
class StandingState : public PlayerState
{

public:
	//更新
	void Update(Player* _p);

	//開始
	void Enter(Player* _p);

	//入力処理
	void HandleInput(Player* _p);

};

