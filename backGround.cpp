#include "backGround.h"
#include "Engine/Image.h"
#include "TestPlayer.h"

backGround::backGround(GameObject* parent)
	:GameObject(parent,"backGround")
{
}

void backGround::Initialize()
{
	hPict_ = Image::Load("2.png");
}

void backGround::Draw()
{
	TestPlayer* pP = (TestPlayer*)FindObject("TestPlayer");
	Image::SetRect(hPict_, 0-((0-pP->GetPosition().x)*10), 250, 1280, 720);
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}
