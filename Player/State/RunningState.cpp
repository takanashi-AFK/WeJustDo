#include "RunningState.h"
#include "../Player.h"
#include "../../Engine/Input.h"

void RunningState::Update(Player* player)
{
	if (Input::IsKey(DIK_D))
	{
		player->SetPosition(0.2f,0.0f,0.0f);
	}
}

void RunningState::Enter(Player* player)
{
	player->
}

void RunningState::RunState()
{
	switch (RunState_) 
	{
	case 0:
		speed_ += 0.02f;
		if (speed_ > 0.5)
		{
			RunState_++;
		}
	case 1:
		speed_ = 0.5f;
	}
		
}
