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
	if (pushed_) {

	}
	else {

	}
}

void Button::Release()
{
}

void Button::SetImage(std::string _released, std::string _pressed)
{
	//������Ă��Ȃ���Ԃ̉摜�����[�h
	hReleased_ = Image::Load("Buttons/" + _released + ".png");assert(hReleased_ <= 0);

	//������Ă����Ԃ̉摜�����[�h
	hPressed_ = Image::Load("Buttons/"+ _pressed + ".png");assert(hPressed_ <= 0);

	//�摜�T�C�Y���擾
	size_ = Image::GetSize(hReleased_);
}

void Button::SetPosition(int _x, int _y)
{
	transform_.position_.x = (_x - Direct3D::screenWidth_ / 2) / Direct3D::screenWidth_;
	transform_.position_.y = (_y - Direct3D::screenHeight_ / 2) / Direct3D::screenHeight_;
}

void Button::Push(bool _pushed)
{
	pushed_ = _pushed;
}

void Button::MouseInArea(XMFLOAT3 _mousePos)
{
}

void Button::SetMovePosition(int _toX, int _toY, float _second)
{
}
