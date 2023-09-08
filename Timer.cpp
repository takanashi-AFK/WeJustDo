#include "Timer.h"
#include "Engine/Image.h"

static const int FPS = 60;

Timer::Timer(GameObject* obj)
	: GameObject(obj, "Timer"), frame(0), active(false), drawX(600), drawY(400)
{
	num = new Text;
	num->InitializeJiyuu();
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
	if (active)
		frame++;

	if(limitActive)
		flimit--;

}


void Timer::Draw()
{
	if (limitActive)
	{
		num->SetScale(1.0f);
		if (flimit % FPS < 10)
			num->SetScale((flimit % FPS) * 0.2f + 1.0f);
		else
			num->SetScale(1.0f);
		int sec = flimit / FPS;
		num->Draw(drawX + 100, drawY, sec);
	}
}

void Timer::Release()
{
}

void Timer::SetLimit(float seconds)
{
	flimit = (int)(seconds * FPS);
}

void Timer::Start()
{
	active = true;
}

void Timer::TimeLimitStart()
{
	limitActive = true;
}

void Timer::Stop()
{
	active = false;
}

void Timer::TimeLimitStop()
{
	limitActive = false;
}

bool Timer::IsFinished()
{
	return (frame == 0);
}

bool Timer::IsLimitEnd()
{
	return (flimit == 0);
}

