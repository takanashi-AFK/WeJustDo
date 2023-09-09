#include "StartCount.h"
#include "Timer.h"
#include <string>
#include "Engine/Image.h"

StartCount::StartCount(GameObject* obj)
	:GameObject(obj,"StartCount"),flg_(false),hPict_{},pTimer_(nullptr)
{
}

StartCount::~StartCount()
{
}

void StartCount::Initialize()
{
	pTimer_ = Instantiate<Timer>(this);
	pTimer_->Start(true);

	string file;
	file = "Image/Count";

	for (int i = 0; i < 4; i++)
	{
		string fileName = file + std::to_string(i) + ".png";
		hPict_[i] = Image::Load(fileName);
	}
}

void StartCount::Update()
{
}

void StartCount::Draw()
{
	//Count(pTimer_->GetTime());
}

void StartCount::Release()
{
}

bool StartCount::IsFinished()
{
	return flg_;
}

void StartCount::Count(int time)
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