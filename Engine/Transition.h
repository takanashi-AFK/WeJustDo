#pragma once

enum TRANSITION_ID {
	TID_NONE,
	TID_BLACKOUT,
	TID_WHITEOUT,
	TID_SLIDEOUT,
	TID_MAX,
};

class Sprite;

namespace Transition
{
	//���s����
	void Initialize();
	void Update();
	void Draw();
	void Release();

	/// <summary>
	/// �g�����W�V������ݒ�
	/// </summary>
	/// <param name="_type">�g�����W�V����ID</param>
	/// <returns>�g�����W�V�������g��Ȃ�(TID_NONE)�ꍇ��false</returns>
	bool SetTransition(TRANSITION_ID _type);

	/// <summary>
	/// �g�����W�V�������J�n
	/// </summary>
	void Start();

	/// <summary>
	/// �g�����W�V�������V�[���̕ύX����^�C�~���O�ɍ����|���������ǂ�����Ԃ�
	/// </summary>
	/// <returns>�����|��������true</returns>
	bool IsChangePoint();

	////////// Toransition pattern //////////////////////////////
	
	/// <summary>
	/// �Ó]
	/// </summary>
	void BlackOut();

	/// <summary>
	/// �z���C�g�A�E�g
	/// </summary>
	void WhiteOut();

	void SlideOut();

};
