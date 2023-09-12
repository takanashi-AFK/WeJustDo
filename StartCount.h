#pragma once
#include "Engine/GameObject.h"

//前方宣言
class Timer;

class StartCount : public GameObject
{
private:
	int hPict_[4];	//画像番号
	bool isfinished_;	//終了したかどうか
	Timer* pTimer_;	//タイマー

public:
	//コンストラクタ
	StartCount(GameObject* obj);
	//継承{初期化,更新,描画,開放}
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Release()override;

	/// <summary>
	/// 終了したかどうかを返す関数
	/// </summary>
	/// <returns>終了したらtrue</returns>
	bool IsFinished();

	/// <summary>
	/// タイマーを０にし、再度開始
	/// </summary>
	void Start();
private:
	/// <summary>
	/// 開始カウントを描画する
	/// </summary>
	/// <param name="time">時間(秒)</param>
	void CountDraw(int time);

};