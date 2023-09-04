#include "Timer.h"
#include "Engine/Image.h"

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

	hPict_[0] = Image::Load("Image/Count0.png");
	hPict_[1] = Image::Load("Image/Count1.png");
	hPict_[2] = Image::Load("Image/Count2.png");
	hPict_[3] = Image::Load("Image/Count3.png");
}

void Timer::Update()
{
	if (active) {
		if (frame > 0) {
			frame--;
		}
	}
	if (fin)
	{
		Image::Draw(hPict_[0]);
		Image::SetTransform(hPict_[0], pictPos);
	}

}

void Timer::Draw()
{
	/*if (!(IsFinished()))
	{
		num->SetScale(5.0f);
		if (frame % FPS < 10)
			num->SetScale((frame % FPS) * 0.3f + 5.0f);
		else
			num->SetScale(5.0f);
		int sec = (frame / FPS) + 1;
		num->Draw(drawX+50, drawY, sec);
	}*/
	//画像の拡縮をします
	static XMFLOAT3 Scale = { 0.0f,0.0f,0.0f };
	//現在の時間
	 int sec = (frame / FPS)+1;
	
	switch (sec)
	{
	case 0:
		//ここに来れない
		Scale = { 1,1,1 };
		Image::Draw(hPict_[3]);
		Image::SetTransform(hPict_[0], transform_);

		break;

	case 1:
		Scale = { 1,1,1 };

		Image::Draw(hPict_[2]);
		pictPos.scale_ = Scale;
		Image::SetTransform(hPict_[1], pictPos);
		Scale.x += 0.05f;
		Scale.y += 0.05f;
		fin = true;
		break;

	case 2:
		Scale = { 1,1,1 };

		Image::Draw(hPict_[1]);
		pictPos.scale_ = Scale;
		Image::SetTransform(hPict_[2], pictPos);
		Scale.x += 0.05f;
		Scale.y += 0.05f;
		break;

	case 3:
		Scale = { 1,1,1};

		Image::Draw(hPict_[0]);
		pictPos.scale_ = Scale;
		Image::SetTransform(hPict_[3], pictPos);
		Scale.x += 0.05f;
		Scale.y += 0.05f;
		break;
	default:
		break;
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

void Timer::CountDown()
{


}

void Timer::CountTimer()
{

}