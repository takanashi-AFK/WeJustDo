#pragma once
#include "PlayerState.h"

class WalkingState : public PlayerState
{
	void Update(Player* player) override;
	void Enter(Player* player) override;
};

