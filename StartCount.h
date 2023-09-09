#pragma once
#include "Engine/GameObject.h"

class Timer;

class StartCount :
    public GameObject
{
private:
	int hPict_[4];
	bool flg_;
	Timer* pTimer_;

public:
	StartCount(GameObject* obj);
	~StartCount();

	void Initialize()override;

	void Update()override;

	//Žc‚èŽžŠÔ‚ð•\Ž¦‚µ‚Ü‚·
	void Draw()override;

	void Release()override;

	bool IsFinished();
	void Count(int time);
};