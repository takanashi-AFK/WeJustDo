#pragma once
#include "Engine/Global.h"

//�O���錾
class Player;

/// <summary>
/// �v���C���[�̏�Ԋ��N���X
/// </summary>
class PlayerState
{
public:
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="_p">Player�̃|�C���^</param>
	virtual void Update(Player* _p){}

	/// <summary>
	/// ���͂ɂ���ď�Ԃ�ω�����
	/// </summary>
	/// <param name="player">Player�̃|�C���^</param>
	virtual void HandleInput(Player* _p) {};

	/// <summary>
	/// ��ԕω������Ƃ��Ɉ�x�����Ă΂��֐�
	/// </summary>
	/// <param name="player">Player�̃|�C���^</param>
	virtual void Enter(Player* _p) {};

	/// <summary>
	/// ��ԕύX
	/// </summary>
	/// <param name="_currentState">���݂̏��</param>
	/// <param name="_nextState">�ω����������</param>
	void ChangeState(PlayerState* _currentState, PlayerState* _nextState);


};

