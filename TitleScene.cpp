#include "TitleScene.h"
#include "Engine/Image.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene")
{
}

void TitleScene::Initialize()
{
	//‰æ‘œ‚Ìƒ[ƒh
	ASSIGN(hPict_, Image::Load(""));
	assert(hPict_ <= 0);
}

void TitleScene::Update()
{
}

void TitleScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void TitleScene::Release()
{
}
