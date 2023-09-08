#include "FuelGauge.h"
#include "Player.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

FuelGauge::FuelGauge(GameObject* parent)
	:GameObject(parent, "FuelGauge"), hPictGauge_(-1), hPictFrame_(-1), nowFuel_(0), maxFuel_(100)
{
	hPictGauge_ = Image::Load("Image/Gauge.png");
	assert(hPictGauge_ >= 0);

	hPictFrame_ = Image::Load("Image/GaugeFrame.png");
	assert(hPictFrame_ >= 0);
}

FuelGauge::~FuelGauge()
{
}


void FuelGauge::Initialize()
{
	//if (Player* pPlayer = (Player*)FindObject("Player"))
	//{
	//	pPlayer->GetPosition();
	//	
	//}
}

void FuelGauge::Update()
{
	if (Input::IsKey(DIK_I))
	{
		nowFuel_ += 1;
		if (nowFuel_ > (maxFuel_ / 2))
		{
			nowFuel_ = 50;
		}
	}

	if (Input::IsKey(DIK_O))
	{
		nowFuel_ -= 1;
		if (nowFuel_ < 0)
		{
			nowFuel_ = 0;
		}
	}
}

void FuelGauge::Draw()
{
	Transform frame;
	Transform gauge;

	gauge.scale_ = {0.5f,0.5f,0.5f};
	frame.scale_ = { 0.5f,0.5f,0.5f };

	gauge.position_.x = GaugePositon;
	frame.position_.x = GaugePositon;

	gauge.position_.y = -0.8f;
	frame.position_.y= -0.8f;

	gauge.scale_.y = nowFuel_/maxFuel_;

	gauge.rotate_.z = 180;
	frame.rotate_.z = 180;

	Image::SetTransform(hPictGauge_, gauge);
	Image::Draw(hPictGauge_);

	Image::SetTransform(hPictFrame_, frame);
	Image::Draw(hPictFrame_);
}

void FuelGauge::Release()
{
}