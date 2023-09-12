#pragma once
#include "PlayerState.h"

//�C���N���[�h
#include "StandingState.h"
#include "RunningState.h"
#include "JumpingState.h"
#include "MovieState.h"
#include "DeadState.h"
#include "JetState.h"

//�O���錾
class Player;
class StandingState;
class RunningState;
class JumpingState;
class MovieState;
class DeadState;
class JetState;

/// <summary>
/// �v���C���[�̊e��Ԃ̑J�ڂ��Ǘ�����N���X
/// </summary>
class PlayerStateManager : public PlayerState
{
public:
	PlayerState* playerState_;
	PlayerState* prevState_;

	StandingState* pStanding_;
	RunningState* pRunning_;
	JumpingState* pJumping_;
	MovieState* pMovie_;
	DeadState* pDead_;
	JetState* pJet_;

	bool isProhibited_;				//State��ύX�\���ǂ���
public:
	//�R���X�g���N�^
	PlayerStateManager();
	~PlayerStateManager();

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
	/// State�̕ύX���ւ���
	/// </summary>
	void StateChangeProhibited() { isProhibited_ = true; }

	/// <summary>
	/// ��Ԃ�ύX����
	/// </summary>
	/// <param name="change">�ύX��̏��</param>
	/// <param name="player">�ύX����v���C���[�̃|�C���^</param>
	/// <param name="flag">true=enter���s��</param>
	void ChangeState(PlayerState* change, Player* player, bool flag);

	void ChangeState(PlayerState* change, Player* player);
};