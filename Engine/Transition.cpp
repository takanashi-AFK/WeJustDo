#include "Transition.h"
#include "Sprite.h"
#include "Global.h"

namespace Transition 
{
	TRANSITION_ID type_ = TID_NONE;
	Sprite* pSprite_[TID_MAX] = { nullptr };

	bool isActive_ = false;	//実行中か否か
	bool isChange_ = false;	//シーンを変更して良いか
	bool isFlag = false;
	float time_ = 0;		//トランジションの再生時間
	float EndTime_ = 0;		//トランジションの終了時間
	
	Transform transform_;	//変形行列
	RECT rect_;				//画像サイズ
	float alpha_;			//画像の透明度

}

void Transition::Initialize()
{
	for (int i = 0; i < TID_MAX; i++)
	{
		pSprite_[i] = new Sprite;
	}
	pSprite_[TID_NONE]->Load("Image/BlackOut.png");
	pSprite_[TID_BLACKOUT]->Load("Image/BlackOut.png");
	pSprite_[TID_WHITEOUT]->Load("Image/WhiteOut.png");
}

void Transition::Update()
{
	if (isActive_) {switch (type_) 
	{
	case TID_NONE:	isChange_ = true; break;
	case TID_BLACKOUT:BlackOut();break;
	case TID_WHITEOUT:WhiteOut();break;
	
	}}else {
		//初期化
		time_ = 0;
		isChange_ = false;
		isFlag = false;
		alpha_ = 0;
	}
}

void Transition::Draw()
{
	pSprite_[type_]->Draw(transform_, rect_, (alpha_ / 255.0f));
}

void Transition::Release()
{
	for (int i = 0; i < TID_MAX; i++)
	{
		SAFE_DELETE(pSprite_[i]);
	}
	
}

bool Transition::SetTransition(TRANSITION_ID _type)
{
	type_ = _type;
	return _type != TID_NONE;
}

bool Transition::IsActive()
{
	return isActive_;
}

void Transition::Start()
{
	isActive_ = true;
}

bool Transition::IsChangePoint()
{
	return isChange_;
}

void Transition::BlackOut()
{
	//Rectの初期化
	rect_.left = 0; rect_.right = pSprite_[TID_BLACKOUT]->GetTextureSize().x;
	rect_.top = 0; rect_.bottom = pSprite_[TID_BLACKOUT]->GetTextureSize().y;

	if (alpha_ >= 255) {
		isChange_ = true;
		isFlag = true;
	}

	if (isFlag){
		alpha_-= 5;
		if (alpha_ <= 0) {
			isActive_ = false;
		}
	}
	else	{
		alpha_+=5;
	}
}

void Transition::WhiteOut()
{
	//Rectの初期化
	rect_.left = 0; rect_.right = pSprite_[TID_WHITEOUT]->GetTextureSize().x;
	rect_.top = 0; rect_.bottom = pSprite_[TID_WHITEOUT]->GetTextureSize().y;

	if (alpha_ >= 255) {
		isChange_ = true;
		isFlag = true;
	}

	if (isFlag) {
		alpha_ -= 5;
		if (alpha_ <= 0) {
			isActive_ = false;
		}
	}
	else {
		alpha_ += 5;
	}
}