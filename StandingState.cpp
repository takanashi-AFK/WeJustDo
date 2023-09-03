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

	RayCastData downData; {
		//�������Ă��邩�m�F
		downData.start = _p->GetPosition();
		XMStoreFloat3(&downData.dir, XMVectorSet(0, -1, 0, 0));
		Model::RayCast(_p->GetPlayerOnGround(), &downData);
	}
	if (downData.dist < (PLAYER_MODEL_SIZE.y / 2)) {

		//�߂荞�ݕ��A�ʒu��߂�
		XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - downData.dist,0 };
		XMFLOAT3 tmpPos = _p->GetPosition();
		XMStoreFloat3(&tmpPos, XMLoadFloat3(&tmpPos) + length); _p->SetPosition(tmpPos);

		//�d�͂����Z�b�g
		_p->IsAddGravity(false);
		_p->SetAcceleration(0);
	}

	XMFLOAT3 ppos;
	ppos = _p->GetPosition();
	EmitterData Dead = _p->GetDeadEData();

	//���S���G�t�F�N�g
	if (ppos.y <= -3 && ppos.y >= -5)
	{
		_p->GetState()->ChangeState(_p->GetState()->pDead_, _p,true);
	}

	//�W�F�b�g�g�p��
	if (Input::IsKey(DIK_LSHIFT))
	{
		_p->GetState()->ChangeState(_p->GetState()->pJet_, _p, false);

		if (_p->GetState()->playerState_ == _p->GetState()->pStanding_)
		{
			_p->GetState()->ChangeState(_p->GetState()->pStanding_, _p, false);
		}
	}
}

//�J�n
void StandingState::Enter(Player* _p)
{
	AudioManager::PlayDonSound();
	_p->InitRandEffect();
	EmitterData Emit = _p->GetRandEData();
	VFX::Start(Emit);
}

//���͏���	
void StandingState::HandleInput(Player* _p)
{
	
}


