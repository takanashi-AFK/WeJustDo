#pragma once
#include "PlayerState.h"

/// <summary>
/// �v���C���[�̑ҋ@���(�������)���Ǘ�����N���X
/// </summary>
class StandingState : public PlayerState
{

public:
	//�X�V
	void Update(Player* _p);

	//�J�n
	void Enter(Player* _p);

	//���͏���
	void HandleInput(Player* _p);

};

