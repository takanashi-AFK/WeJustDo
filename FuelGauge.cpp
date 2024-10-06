#include "FuelGauge.h"
#include "Player.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

FuelGauge::FuelGauge(GameObject* parent)
	:GameObject(parent, "FuelGauge"), hPictGauge_(-1), hPictFrame_(-1), nowFuel_(0), maxFuel_(100)
{
	hPictGauge_ = Image::Load("Image/Gauge.png");
	assert(hPictGauge_ >= 0);
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
}

void FuelGauge::Draw()
{
	Transform gauge;

	gauge.scale_ = {0.5f,1.5f,0.5f};

	gauge.position_.x = GaugePositon;

	gauge.position_.y = -1.0f;

	gauge.scale_.y = nowFuel_*3/maxFuel_;

	gauge.rotate_.z = 90;

	Image::SetTransform(hPictGauge_, gauge);
	Image::Draw(hPictGauge_);
}

void FuelGauge::Release()
{
}