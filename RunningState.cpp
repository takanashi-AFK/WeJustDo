#include "RunningState.h"
#include "Engine/Input.h"
#include "Player.h"

void RunningState::Update(Player* _p)
{
	static float s; s += 0.01f;
	_p->SetPositionX(s);

	//“ü—Íˆ—
	HandleInput(_p);
}

void RunningState::Enter(Player* _p)
{
	_p->SetPositionY(-2);
}

void RunningState::HandleInput(Player* _p)
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		_p->GetState()->ChangeState(_p->GetState()->pStanding_, _p);
	}
}
