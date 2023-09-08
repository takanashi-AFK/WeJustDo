#pragma once
#include "PlayerState.h"
#include "PlayerStateManager.h"
class DeadState : public PlayerState
{
	XMFLOAT3 ppos;
public:

	//更新
	void Update(Player* _p);

	//開始
	void Enter(Player* _p);

	//入力処理
	void HandleInput(Player* _p);
};

