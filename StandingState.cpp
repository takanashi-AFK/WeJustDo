#include "StandingState.h"
#include "Engine/Input.h"
#include "Player.h"

void StandingState::Update(Player* _p)
{
	static float angle; angle+=0.1f;
	_p->SetRotateY(angle);


	

	//“ü—Íˆ—
	HandleInput(_p);
}

void StandingState::Enter(Player* _p)
{
	_p->SetPositionY(2);
}

void StandingState::HandleInput(Player* _p)
{
	if (Input::IsKeyDown(DIK_SPACE)){
		_p->GetState()->ChangeState(_p->GetState()->pRunning_, _p);
	}
}
