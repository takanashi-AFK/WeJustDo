#include "JumpingState.h"

#include "Player.h"
#include "AudioManager.h"
#include "Engine/VFX.h"
#include "PlayerStateManager.h"
#include "Engine/Input.h"
#include "Engine/Model.h"



void JumpingState::Update(Player* _p)
{
	Transform* TJumping = _p->GetTransformAddress();

	TJumping->position_.y += 0.12f;
	HandleInput(_p);

	XMFLOAT3 ppos;
	ppos = _p->GetPosition();

	{//State•Ï‰»
		
		//standing
		if (_p->GetAccelaration() >= 5.0f)
			_p->GetState()->ChangeState(_p->GetState()->pStanding_, _p, true);
		//dead
		if (ppos.y <= -3 && ppos.y >= -5)
			_p->GetState()->ChangeState(_p->GetState()->pDead_, _p, true);

		if(Input::IsKeyDown(DIK_SPACE) && (Global::gFireWood >0))
			_p->GetState()->ChangeState(_p->GetState()->pJet_, _p, true);
	}
}

void JumpingState::Enter(Player* _p)
{
}

void JumpingState::HandleInput(Player* _p)
{
	Transform* TRunning = _p->GetTransformAddress();

	float s = 0.1f;
	if (Input::IsKey(DIK_A)) { TRunning->position_.x -= s; TRunning->rotate_.y = -90; /*PolyJetEmitPos.x = PolyJetEmitPos.x + 0.5;*/ }
	else if (Input::IsKey(DIK_D)) { TRunning->position_.x += s; TRunning->rotate_.y = 90; }
}
