#pragma once
#include "PlayerState.h"

class MovieState : public PlayerState
{
	float prevPosX_;
public:
	//�X�V
	void Update(Player* _p);

	//�J�n
	void Enter(Player* _p);

	//���͏���
	void HandleInput(Player* _p);
};

