#pragma once

//�O���錾
class Player;

class PlayerState
{
public:
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="_player"></param>
	virtual void Update(Player* _player) = 0;

	/// <summary>
	/// ��ԑJ�ڎ��Ɉ�x�����Ăяo�����
	/// </summary>
	/// <param name="_player">�v���C���[���</param>
	virtual void Enter(Player* _player) {};
};

