#pragma once

namespace AudioManager {

	/// <summary>
	/// 和太鼓一発ドン再生
	/// </summary>
	void Play_DonSound();

	/// <summary>
	/// 和太鼓停止
	/// </summary>
	void Stop_DonSound();

	/// <summary>
	///タイトルシーンBGM再生 
	/// </summary>
	void Play_TitleMusic();

	/// <summary>
	/// 確定音再生
	/// </summary>
	void Play_ConfirmSound();

	/// <summary>
	/// プレイシーンBGM再生
	/// </summary>
	void Play_PlayMusic();

	/// <summary>
	/// 死亡時サウンド再生
	/// </summary>
	void Play_DeadSound();

	/// <summary>
	/// ジャンプ時サウンド再生
	/// </summary>
	void Play_JumpSound();

	/// <summary>
	/// ジェットサウンド再生
	/// </summary>
	void Play_JetSound();

	/// <summary>
	/// ジェットサウンド停止
	/// </summary>
	void Stop_JetSound();

	/// <summary>
	/// 足音再生
	/// </summary>
	void Play_FootSound();

	/// <summary>
	/// 足音停止
	/// </summary>
	void Stop_FootSound();

	void Play_WoodSound();

	void Release();
};