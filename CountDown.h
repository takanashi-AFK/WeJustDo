#pragma once
#include "Engine/GameObject.h"
#include "Timer.h"

class CountDown :
    public GameObject
{
private:
	int time;
	int hPict_[4];
	Timer* pTimer;
	bool flg_;

public:
	CountDown(GameObject* obj);
	~CountDown();

	void Initialize()override;

	void Update()override;

	//残り時間を表示します
	void Draw()override;

	void Release()override;

	bool IsFinished();
};

