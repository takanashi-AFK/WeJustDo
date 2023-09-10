#pragma once

namespace AudioManager {

	/// <summary>
	/// �a���ۈꔭ�h���Đ�
	/// </summary>
	void Play_DonSound();

	/// <summary>
	/// �a���ے�~
	/// </summary>
	void Stop_DonSound();

	/// <summary>
	///�^�C�g���V�[��BGM�Đ� 
	/// </summary>
	void Play_TitleMusic();

	/// <summary>
	/// �m�艹�Đ�
	/// </summary>
	void Play_ConfirmSound();

	/// <summary>
	/// �v���C�V�[��BGM�Đ�
	/// </summary>
	void Play_PlayMusic();

	/// <summary>
	/// ���S���T�E���h�Đ�
	/// </summary>
	void Play_DeadSound();

	/// <summary>
	/// �W�����v���T�E���h�Đ�
	/// </summary>
	void Play_JumpSound();

	/// <summary>
	/// �W�F�b�g�T�E���h�Đ�
	/// </summary>
	void Play_JetSound();

	/// <summary>
	/// �W�F�b�g�T�E���h��~
	/// </summary>
	void Stop_JetSound();

	/// <summary>
	/// �����Đ�
	/// </summary>
	void Play_FootSound();

	/// <summary>
	/// ������~
	/// </summary>
	void Stop_FootSound();

	void Play_WoodSound();

	void Release();
};