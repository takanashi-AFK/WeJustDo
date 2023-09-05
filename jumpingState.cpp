#include "JumpingState.h"
#include "Player.h"

#include "Player.h"
#include "AudioManager.h"
#include "Engine/VFX.h"
#include "PlayerStateManager.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

void JumpingState::Update(Player* _p)
{
}

void JumpingState::Enter(Player* _p)
{
}

void JumpingState::HandleInput(Player* _p)
{
	Transform* TRunning = _p->GetTransformAddress();

	if (Input::IsKey(DIK_A)) { TRunning->position_.x -= 0.1; TRunning->rotate_.y = -90; /*PolyJetEmitPos.x = PolyJetEmitPos.x + 0.5;*/ }
	if (Input::IsKey(DIK_D)) { TRunning->position_.x += 0.1; TRunning->rotate_.y = 90; }
}
