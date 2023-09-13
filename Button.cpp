#include "Button.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"

Button::Button(GameObject* _parent)
	:GameObject(_parent,"Button")
	,hReleased_(-1),hPressed_(-1),pushed_(false),center_{},size_{}
	,startPos_{},endPos_{},totalTime_(0),currentTime_(0)
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
		//押されている状態の画像を描画
		Image::SetTransform(hPressed_, transform_);
		Image::Draw(hPressed_);
	}
	else {
		//押されていない状態の画像を描画
		Image::SetTransform(hReleased_, transform_);
		Image::Draw(hReleased_);
	}
}

void Button::SetImage(std::string _released, std::string _pressed)
{
	//押されていない状態の画像をロード
	hReleased_ = Image::Load("Buttons/" + _released + ".png");assert(hReleased_ <= 0);

	//押されている状態の画像をロード
	hPressed_ = Image::Load("Buttons/"+ _pressed + ".png");assert(hPressed_ <= 0);

	//画像サイズを取得
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

bool Button::MouseInArea(XMFLOAT3 _mousePos)
{
	if (abs(_mousePos.x - center_.x) > size_.x / 2)return false;
	if (abs(_mousePos.y - center_.y) > size_.y / 2)return false;
	return true;
}

void Button::SetMovePosition(int _toX, int _toY, float _second)
{
	startPos_ = center_;//今の座標をコピー
	endPos_ = XMFLOAT3((float)_toX, (float)_toY, 0);
	totalTime_ = _second;
	currentTime_ = 0.0f;
}
