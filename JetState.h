#pragma once
#include "PlayerState.h"
#include "PolyLine.h"
#include"PlayerStateManager.h"

class JetState : public PlayerState
{
	PolyLine jett;

public:
	//�X�V
	void Update(Player* _p);

	//�J�n
	void Enter(Player* _p);

	//���͏���
	void HandleInput(Player* _p);
};

