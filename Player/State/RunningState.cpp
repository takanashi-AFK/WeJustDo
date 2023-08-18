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
	player->Update();
}


