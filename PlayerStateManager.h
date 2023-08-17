#pragma once
#include "PlayerState.h"
#include "StandingState.h"
#include "RunningState.h"

class Player;

class PlayerStateManager : public PlayerState
{
public:
	PlayerState* playerState_;

	//�e��ԕϐ�
	StandingState* pStanding_;
	RunningState* pRunning_;
public:
	//�R���X�g���N�^
	PlayerStateManager();

	//�X�V
	virtual void Update(Player* _p) override;

	//���͂ɂ���ď�ԕω�����
	virtual void HandleInput(Player* player)override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	virtual void Enter(Player* player)override;

	//��ԃ`�F���W�p
	void ChangeState(PlayerState* change, Player* player);
};

