#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

class Timer : public GameObject
{
private:
	int frame;
	int flimit;
	bool active;
	bool limitActive;
	int drawX;
	int drawY;

	Text* num;
	Transform pictPos;
public:
	Timer(GameObject* obj);
	~Timer();
	//Timerのイニシャライズ
	void Initialize()override;

	//タイマーがスタートしていたら設定時間カウントダウンする
	void Update()override;

	//残り時間を表示します
	void Draw()override;

	void Release()override;

	//制限時間を【秒】で入力します。
	void SetLimit(float seconds);

	//タイマー開始
	void Start();
	void TimeLimitStart();

	//タイマー一時停止
	void Stop();
	void TimeLimitStop();

	//終わった時
	bool IsFinished();
	bool IsLimitEnd();

	int GetTime() { return frame/60; };
};