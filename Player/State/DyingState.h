#pragma once
#include "PlayerState.h"
class DyingState :
    public PlayerState
{
public:
	void Update(Player* player) override;
	void Enter(Player* player) override;
};

