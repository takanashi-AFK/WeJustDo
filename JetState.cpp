#include "JetState.h"
#include "Engine/Input.h"

#include "Player.h"
#include "AudioManager.h"

void JetState::Update(Player* _p)
{
	//“ü—Íˆ—
	HandleInput(_p);
}

void JetState::Enter(Player* _p)
{
}

void JetState::HandleInput(Player* _p)
{
	if (Input::IsKey(DIK_LSHIFT))
	{
		_p->SetIsJetNow(true);
		AudioManager::Play_JetSound();
	}
	else if (Input::IsKeyUp(DIK_LSHIFT))
	{
		AudioManager::Stop_JetSound();
		_p->SetIsJetNow(false);
	}
	else
		_p->SetIsJetNow(false);
}
