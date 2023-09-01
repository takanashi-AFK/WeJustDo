#pragma once
#include "PlayerState.h"

class jumpingState : public PlayerState
{
public:
	//更新
	void Update(Player* _p);

	//開始
	void Enter(Player* _p);

	//入力処理
	void HandleInput(Player* _p);
};

