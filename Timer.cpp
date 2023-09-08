#include "Timer.h"
#include "Engine/Image.h"

static const int FPS = 60;

Timer::Timer(GameObject* obj)
	: GameObject(obj, "Timer"), frame(0), active(false), drawX(1200), drawY(100)
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
		if (flimit / FPS <= 10)
		{
			num->SetScale(0.8f);
			if (flimit % FPS < 10)
				num->SetScale((flimit % FPS) * 0.1f + 1.0f);
			//else
			//	num->SetScale(0.8f);
			int sec = flimit / FPS;
			num->Draw(drawX, drawY, sec);
		}
		else
		{
			num->SetScale(0.8f);
			int sec = flimit / FPS;
			num->Draw(drawX , drawY, sec);
		}
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
	return (flimit <= 0);
}

