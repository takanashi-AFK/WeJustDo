#pragma once
#include "PlayerState.h"
#include "PlayerStateManager.h"
class DeadState : public PlayerState
{
	XMFLOAT3 ppos;
public:

	//�X�V
	void Update(Player* _p);

	//�J�n
	void Enter(Player* _p);

	//���͏���
	void HandleInput(Player* _p);
};

