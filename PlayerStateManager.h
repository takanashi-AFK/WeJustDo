#pragma once
#include "PlayerState.h"

//�C���N���[�h
#include "StandingState.h"
#include "RunningState.h"
#include "JumpingState.h"
#include "MovieState.h"

//�O���錾
class Player;

/// <summary>
/// �v���C���[�̊e��Ԃ̑J�ڂ��Ǘ�����N���X
/// </summary>
class PlayerStateManager : public PlayerState
{
public:
	PlayerState* playerState_;

	//�e��ԕϐ�
	StandingState* pStanding_;
	RunningState* pRunning_;
	JumpingState* pJumping_;
	MovieState* pMovie_;
public:
	//�R���X�g���N�^
	PlayerStateManager();

	//�X�V
	virtual void Update(Player* _p) override;

	/// <summary>
	/// ���͏���
	/// </summary>
	/// <param name="player">�v���C���[�̃|�C���^</param>
	virtual void HandleInput(Player* player)override;

	/// <summary>
	/// �J�n���Ɉ�x�Ă΂��
	/// </summary>
	/// <param name="player">�v���C���[�̃|�C���^</param>
	virtual void Enter(Player* player)override;

	/// <summary>
	/// ��Ԃ�ύX����
	/// </summary>
	/// <param name="change">�ύX��̏��</param>
	/// <param name="player">�ύX����v���C���[�̃|�C���^</param>
	void ChangeState(PlayerState* change, Player* player);
};

