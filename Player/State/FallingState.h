#pragma once
#include "PlayerState.h"
class FallingState :
    public PlayerState
{
public:
	void Update(Player* player) override;
	void Enter(Player* player) override;
};

