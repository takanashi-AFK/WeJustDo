#pragma once
#include "PlayerState.h"
class StandingState : public PlayerState
{
public:
	void Update(Player* _player);
	void Enter(Player* _player);
};

