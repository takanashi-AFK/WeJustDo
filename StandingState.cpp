#include "StandingState.h"

//�C���N���[�h
#include "Player.h"
#include "AudioManager.h"
#include "Engine/Input.h"
#include "Engine/VFX.h"


//�X�V
void StandingState::Update(Player* _p)
{
	//���͏���
	HandleInput(_p);

	XMFLOAT3 ppos;
	ppos = _p->GetPosition();
	RayCastData downDataL; {
		//�������Ă��邩�m�F
		downDataL.start = XMFLOAT3(ppos.x - (PLAYER_MODEL_SIZE.x / 2),
			ppos.y,
			ppos.z);
		XMStoreFloat3(&downDataL.dir, XMVectorSet(0, -1, 0, 0));
		Model::RayCast(_p->GetPlayerOnGround(), &downDataL);
	}
	RayCastData downDataR; {
		//�������Ă��邩�m�F
		downDataR.start = XMFLOAT3(ppos.x + (PLAYER_MODEL_SIZE.x / 2),
			ppos.y - (PLAYER_MODEL_SIZE.y / 2),
			ppos.z);
		XMStoreFloat3(&downDataL.dir, XMVectorSet(0, -1, 0, 0));
		Model::RayCast(_p->GetPlayerOnGround(), &downDataR);
	}
	if (downDataL.dist < (PLAYER_MODEL_SIZE.y / 2) && downDataR.dist < (PLAYER_MODEL_SIZE.y / 2)) {

		//�߂荞�ݕ��A�ʒu��߂�
		XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - ((downDataL.dist + downDataR.dist) / 2) - 0.25 ,0 };
		XMFLOAT3 tmpPos = _p->GetPosition();
		XMStoreFloat3(&tmpPos, XMLoadFloat3(&tmpPos) + length); _p->SetPosition(tmpPos);

		//�d�͂����Z�b�g
		_p->IsAddGravity(false);
		_p->SetAcceleration(0);
	}
	{//State�ω�

		//running
		if (Input::IsKey(DIK_D) || Input::IsKey(DIK_A))
			_p->GetState()->ChangeState(_p->GetState()->pRunning_, _p, true);
		//dead
		if (ppos.y <= -10 && ppos.y >= -13)
			_p->GetState()->ChangeState(_p->GetState()->pDead_, _p, true);

		if (Input::IsKeyDown(DIK_SPACE))
			_p->GetState()->ChangeState(_p->GetState()->pJumping_, _p, true);

	}
}
//�J�n
void StandingState::Enter(Player* _p)
{
	if(AudioManager::isJetPlayNow())
	AudioManager::Stop_JetSound();

	//�d�͂����Z�b�g
	_p->SetAcceleration(0);

	//�A�j���[�V�������X�g�b�v
	Model::SetAnimFrame(_p->GetModelHandle(), 0, 0, 1);

	//�G�t�F�N�g����
	_p->InitRandEffect();
	EmitterData Emit = _p->GetRandEData();
	VFX::Start(Emit);
}

//���͏���	
void StandingState::HandleInput(Player* _p)
{

	
}


