#include "Timer.h"

static const int FPS = 60;

Timer::Timer(GameObject* obj)
	: GameObject(obj, "Timer"), frame(0), active(false), drawX(600), drawY(400)
{
	num = new Text;
	num->Initialize();
}

Timer::~Timer()
{
	delete num;
}

void Timer::Initialize()
{
	frame = 0;
	active = false;
}

void Timer::Update()
{
	if (active) {
		if (frame > 0) {
			frame--;
		}
	}
}

void Timer::Draw()
{
	if (!(IsFinished()))
	{
		num->SetScale(5.0f);
		if (frame % FPS < 10)
			num->SetScale((frame % FPS) * 0.3f + 5.0f);
		else
			num->SetScale(5.0f);
		int sec = (frame / FPS) + 1;
		num->Draw(drawX+50, drawY, sec);
	}
	else
	{

	}
}

void Timer::Release()
{
}

void Timer::SetLimit(float seconds)
{
	frame = (int)(seconds * FPS);
}

void Timer::Start()
{
	active = true;
}

void Timer::Stop()
{
	active = false;
}

bool Timer::IsFinished()
{
	return (frame == 0);
}
