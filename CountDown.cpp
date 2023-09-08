#include "CountDown.h"
#include "Timer.h"
#include <string>

CountDown::CountDown(GameObject* obj)
	:GameObject(obj,"CountDown"),flg_(false)
{
}

CountDown::~CountDown()
{
}

void CountDown::Initialize()
{
	pTimer = Instantiate<Timer>(this);
	pTimer->Start();

	string file;
	file = "Image/Count";

	for (int i = 0; i < 4; i++)
	{
		string fileName = file + std::to_string(i) + ".png";
		hPict_[i] = Image::Load(fileName);
	}
}

void CountDown::Update()
{
}

void CountDown::Draw()
{
	Count(pTimer->GetTime());
}

void CountDown::Release()
{
}

bool CountDown::IsFinished()
{
	return flg_;
}

void CountDown::Count(int time)
{
	if (time == 1)
	{
		Image::SetTransform(hPict_[3], transform_);
		Image::Draw(hPict_[3]);
	}
	else if (time == 2)
	{
		Image::SetTransform(hPict_[3], transform_);
		Image::Draw(hPict_[2]);
	}
	else if (time == 3)
	{
		Image::SetTransform(hPict_[3], transform_);
		Image::Draw(hPict_[1]);
	}
	else if (time == 4)
	{
		Image::SetTransform(hPict_[0], transform_);
		Image::Draw(hPict_[0]);
		flg_ = true;
	}
}