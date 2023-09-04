#include "JumpingState.h"

#include "Player.h"
#include "AudioManager.h"
#include "Engine/VFX.h"
#include "PlayerStateManager.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

void JumpingState::Update(Player* _p)
{
	RayCastData downdata = _p->GetDownData();
	XMFLOAT3 ppos;
	ppos = _p->GetPosition();
	Transform* TJumping = _p->GetTransformAddress();

		TJumping->position_.y += 0.1f;
		HandleInput(_p);
	

	{

		if (Input::IsKeyDown(DIK_SPACE))
			_p->GetState()->ChangeState(_p->GetState()->pJet_, _p, true);

		if (ppos.y <= -3 && ppos.y >= -5)
			_p->GetState()->ChangeState(_p->GetState()->pDead_, _p, true);

		//’…’n‚µ‚½‚ç
		if(downdata.dist > (PLAYER_MODEL_SIZE.y / 2))
			_p->GetState()->ChangeState(_p->GetState()->pStanding_, _p, true);
	
	}

}

void JumpingState::Enter(Player* _p)
{
	Transform* TJumping = _p->GetTransformAddress();

	if (Input::IsKeyDown(DIK_SPACE)) {
		AudioManager::Play_JumpSound();
	}
}

void JumpingState::HandleInput(Player* _p)
{
	Transform* TRunning = _p->GetTransformAddress();

	if (Input::IsKey(DIK_A)) { TRunning->position_.x -= 0.1; TRunning->rotate_.y = -90; /*PolyJetEmitPos.x = PolyJetEmitPos.x + 0.5;*/ }
	if (Input::IsKey(DIK_D)) { TRunning->position_.x += 0.1; TRunning->rotate_.y = 90; }
}
