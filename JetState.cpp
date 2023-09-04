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
		_p->GetState()->ChangeState(_p->GetState()->pRunning_, _p, false);
	}

	Transform* TRunning = _p->GetTransformAddress();
	{//debug-PlayerMove
		//if (Input::IsKey(DIK_W))transform_.position_.y += 0.1;
		if (Input::IsKey(DIK_A)) { TRunning->position_.x -= 0.1; TRunning->rotate_.y = -90; /*PolyJetEmitPos.x = PolyJetEmitPos.x + 0.5;*/ }
		//if (Input::IsKey(DIK_S))transform_.position_.y -= 0.1;
		else if (Input::IsKey(DIK_D)) { TRunning->position_.x += 0.1; TRunning->rotate_.y = 90; }
	}
}
