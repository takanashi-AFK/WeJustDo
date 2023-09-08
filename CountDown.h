#pragma once
#include "Engine/GameObject.h"

class Timer;

class CountDown :
    public GameObject
{
private:
	int hPict_[4];
	bool flg_;
	Timer* pTimer;

public:
	CountDown(GameObject* obj);
	~CountDown();

	void Initialize()override;

	void Update()override;

	//�c�莞�Ԃ�\�����܂�
	void Draw()override;

	void Release()override;

	bool IsFinished();
	void Count(int time);
};