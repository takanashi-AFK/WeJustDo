#include "MovieState.h"
#include "Player.h"
#include "AudioManager.h"

void MovieState::Update(Player* _p)
{
	Transform* t_Player = _p->GetTransformAddress();

	if (t_Player->position_.x >= prevPosX_ + 0.3f) {
		
	}
	else {
		t_Player->position_.x += 0.1f;
	}

}

void MovieState::Enter(Player* _p)
{
	_p->SetIsMove(false);
	_p->IsAddGravity(false);
	_p->GetState()->StateChangeProhibited();
	prevPosX_ = _p->GetPosition().x;
}

void MovieState::HandleInput(Player* _p)
{
}
