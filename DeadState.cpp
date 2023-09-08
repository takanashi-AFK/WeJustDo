#include "DeadState.h"
#include "Player.h"

#include "AudioManager.h"
#include "Engine/Input.h"
#include "Engine/VFX.h"
#include "Engine/Camera.h"

void DeadState::Update(Player* _p)
{

	ppos = _p->GetPosition();

	//���͏���
	HandleInput(_p);
}

void DeadState::Enter(Player* _p)
{
	

	ppos = _p->GetPosition();
	EmitterData dead = _p->GetDeadEData();
	_p->InitDeadEffect();
	dead.position = XMFLOAT3(ppos.x, 0, -1);
	VFX::Start(dead);
	AudioManager::Play_DeadSound();
}

void DeadState::HandleInput(Player* _p)
{
}
