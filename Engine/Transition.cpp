#include "Transition.h"
#include "Sprite.h"
#include "Global.h"

namespace Transition 
{
	TRANSITION_ID type_ = TID_NONE;
	Sprite* pSprite_ = nullptr;

	bool isActive_ = false;
	float time_ = 0;
	float EndTime_ = 0;
}

void Transition::Initialize()
{
	pSprite_ = new Sprite;
	pSprite_->Load("BlackOut.png");
}

void Transition::Update()
{
	switch (type_)
	{
	case TID_NONE:
		break;
	case TID_BLACKOUT:
		break;
	case TID_WHITEOUT:
		break;
	}
}

void Transition::Draw()
{
	Transform t;RECT r;
	r.left = 0;r.right = pSprite_->GetTextureSize().x;
	r.top = 0; r.bottom = pSprite_->GetTextureSize().y;
	static float a = 255;
	pSprite_->Draw(t, r, (a/255.0f));
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
	return time_ == (EndTime_/2.0f);
}
