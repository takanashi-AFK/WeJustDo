#pragma once
#include "PlayerState.h"

/// <summary>
/// �v���C���[�̑����Ԃ��Ǘ�����N���X
/// </summary>
class RunningState : public PlayerState
{
public:
	//�X�V
	void Update(Player* _p);

	//�J�n
	void Enter(Player* _p);

	//���͏���
	void HandleInput(Player* _p);
};

