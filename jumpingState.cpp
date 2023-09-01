#include "JumpingState.h"
#include "Player.h"

const float jumpPower = 0.1f;

void JumpingState::Update(Player* _p)
{
	XMFLOAT3 tmp = _p->GetPosition();
	tmp.y += jumpPower;
	_p->SetPosition(tmp);
	_p->IsAddGravity(true);
}

void JumpingState::Enter(Player* _p)
{
}

void JumpingState::HandleInput(Player* _p)
{
}
