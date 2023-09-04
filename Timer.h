#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

class Timer : public GameObject
{
private:
	int frame;
	bool active;
	int drawX;
	int drawY;
	int hPict2_;
	bool fin;


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

	//タイマー一時停止
	void Stop();

	//終わった時
	bool IsFinished();
	bool IsFin();

	int GetTime() { return frame/60; };
};