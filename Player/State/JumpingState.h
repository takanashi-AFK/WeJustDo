#pragma once
#include "PlayerState.h"
class JumpingState :
    public PlayerState
{
public:
	void Update(Player* player) override;
	void Enter(Player* player) override;
};

