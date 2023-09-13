#include "Button.h"
#include "Engine/Image.h"

Button::Button(GameObject* parent)
	:GameObject(parent,"Button")
{
}

void Button::Initialize()
{
	//‰æ‘œ‚Ìƒ[ƒh
	std::string filename[ImageNum]={
		"Buttons/CommonButtonBack.png",
		"Buttons/CommonButtonBackDisable.png",
		"Buttons/FoodButtonGive,png",
		"Buttons/FoodButtonGiveDisable.png"
	};
	for (int i = 0; i < ImageNum; i++) {
		hPict_[i] = Image::Load(filename->c_str());
	}
}

void Button::Update()
{
}

void Button::Draw()
{
	//‰æ‘œ‚Ì•`‰æ
	Image::SetTransform(hPict_[CommonButtonBack], transform_);
	Image::Draw(hPict_[CommonButtonBack]);
}

void Button::Release()
{
}
