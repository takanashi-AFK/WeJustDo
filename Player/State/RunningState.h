#pragma once
#include "PlayerState.h"
class RunningState :
    public PlayerState
{
public:
	int RunState_ = 0;

	void Update(Player* player) override;
	void Enter(Player* player) override;
};

