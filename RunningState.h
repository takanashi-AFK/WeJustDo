#pragma once
#include "PlayerState.h"
#include "PlayerStateManager.h"
/// <summary>
/// プレイヤーの走り状態を管理するクラス
/// </summary>
class RunningState : public PlayerState
{
public:
	//更新
	void Update(Player* _p);

	//開始
	void Enter(Player* _p);

	//入力処理
	void HandleInput(Player* _p);
};

