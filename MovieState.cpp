#include "MovieState.h"
#include "Player.h"
#include "AudioManager.h"

void MovieState::Update(Player* _p)
{
	XMFLOAT3 tmp = _p->GetPosition();
	tmp.x += 0.01f;
	_p->SetPosition(tmp);
}

void MovieState::Enter(Player* _p)
{
	_p->SetIsMove(false);
	_p->IsAddGravity(false);
}

void MovieState::HandleInput(Player* _p)
{
}
