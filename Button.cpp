#include "Button.h"
#include "Engine/Image.h"

Button::Button(GameObject* parent)
	:GameObject(parent,"Button")
{
}

void Button::Initialize()
{
	//�摜�̃��[�h
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
	//�摜�̕`��
	Image::SetTransform(hPict_[CommonButtonBack], transform_);
	Image::Draw(hPict_[CommonButtonBack]);
}

void Button::Release()
{
}
