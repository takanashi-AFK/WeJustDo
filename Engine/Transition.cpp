#include "Transition.h"
#include "Sprite.h"
#include "Global.h"

namespace Transition 
{
	TRANSITION_ID type_ = TID_NONE;
	Sprite* pSprite_ = nullptr;

	bool isActive_ = false;	//実行中か否か
	bool isChange_ = false;	//シーンを変更して良いか
	float time_ = 0;		//トランジションの再生時間
	float EndTime_ = 0;		//トランジションの終了時間
	
	Transform transform_;	//変形行列
	RECT rect_;				//画像サイズ
	float alpha_;			//画像の透明度

}

void Transition::Initialize()
{
	pSprite_ = new Sprite;
	pSprite_->Load("BlackOut.png");
}

void Transition::Update()
{
	if (isActive_) {switch (type_) 
	{
	case TID_NONE:isChange_ = true; break;
	case TID_BLACKOUT:BlackOut();break;
	case TID_WHITEOUT:WhiteOut();break;
	
	}}else {
		time_ = 0;
	}
}

void Transition::Draw()
{
	
	static float a = 255;
	pSprite_->Draw(transform_, rect_, (alpha_/255.0f));
}

void Transition::Release()
{
	SAFE_DELETE(pSprite_);
}

bool Transition::SetTransition(TRANSITION_ID _type)
{
	type_ = _type;
	return _type != TID_NONE;
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
	rect_.left = 0; rect_.right = pSprite_->GetTextureSize().x;
	rect_.top = 0; rect_.bottom = pSprite_->GetTextureSize().y;

	if (alpha_ >= 255) {
		isChange_ = true;
		alpha_--;
	}
	else {
		alpha_++;
	}
}

void Transition::WhiteOut()
{

}