#include "Transition.h"
#include "Sprite.h"
#include "Global.h"

namespace Transition 
{
	TRANSITION_ID type_ = TID_NONE;
	Sprite* pSprite_ = nullptr;

	bool isActive_ = false;	//���s�����ۂ�
	bool isChange_ = false;	//�V�[����ύX���ėǂ���
	float time_ = 0;		//�g�����W�V�����̍Đ�����
	float EndTime_ = 0;		//�g�����W�V�����̏I������
	
	Transform transform_;	//�ό`�s��
	RECT rect_;				//�摜�T�C�Y
	float alpha_;			//�摜�̓����x

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
	//Rect�̏�����
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