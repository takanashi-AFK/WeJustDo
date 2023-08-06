#include "backGround.h"
#include "Engine/Image.h"
#include "TestPlayer.h"

backGround::backGround(GameObject* parent)
	:GameObject(parent,"backGround")
{
}

void backGround::Initialize()
{
	hPict_ = Image::Load("haikei.png");
}

void backGround::Draw()
{
	TestPlayer* pP = (TestPlayer*)FindObject("TestPlayer");
	Image::SetRect(hPict_, 0-((0-pP->GetPosition().x)*10), 720, 1280, 720);
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}
