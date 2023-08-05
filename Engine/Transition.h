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
	//実行処理
	void Initialize();
	void Update();
	void Draw();
	void Release();

	/// <summary>
	/// トランジションを設定
	/// </summary>
	/// <param name="_type">トランジションID</param>
	/// <returns>トランジションを使わない(TID_NONE)場合はfalse</returns>
	bool SetTransition(TRANSITION_ID _type);

	/// <summary>
	/// トランジションを開始
	/// </summary>
	void Start();

	/// <summary>
	/// トランジションがシーンの変更するタイミングに差し掛かったかどうかを返す
	/// </summary>
	/// <returns>差し掛かったらtrue</returns>
	bool IsChangePoint();

	////////// Toransition pattern //////////////////////////////
	
	/// <summary>
	/// 暗転
	/// </summary>
	void BlackOut();

	/// <summary>
	/// ホワイトアウト
	/// </summary>
	void WhiteOut();

	void SlideOut();

};
