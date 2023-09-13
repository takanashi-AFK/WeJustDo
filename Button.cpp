#include "Button.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"

Button::Button(GameObject* _parent)
	:GameObject(_parent,"Button")
{
}

void Button::Initialize()
{
}

void Button::Update()
{
}

void Button::Draw()
{
}

void Button::Release()
{
}

void Button::SetImage(std::string _released, std::string _pressed)
{
	//押されていない状態の画像をロード
	hReleased_ = Image::Load("Buttons/" + _released + ".png");
	assert(hReleased_ <= 0);

	//押されている状態の画像をロード
	hPressed_ = Image::Load("Buttons/"+ _pressed + ".png");
	assert(hPressed_ <= 0);
}


void Button::SetPosition(int _x, int _y)
{
	transform_.position_.x = (_x - Direct3D::screenWidth_ / 2) / Direct3D::screenWidth_;
	transform_.position_.y = (_y - Direct3D::screenHeight_ / 2) / Direct3D::screenHeight_;

}

void Button::Push(bool _pushed)
{
}

void Button::MouseInArea(XMFLOAT3 _mousePos)
{
}
