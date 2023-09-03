#include "RunningState.h"

//�C���N���[�h
#include "Player.h"
#include "AudioManager.h"
#include "Engine/VFX.h"
#include "PlayerStateManager.h"
#include "Engine/Input.h"


//�X�V
void RunningState::Update(Player* _p)
{
	XMFLOAT3 ppos;
	ppos = _p->GetPosition();
	//���͏���
	HandleInput(_p);
	//���S���G�t�F�N�g
	if (ppos.y <= -3 && ppos.y >= -5)
	{
		_p->GetState()->ChangeState(_p->GetState()->pDead_, _p,true);
	}

	//�W�F�b�g�g�p��
	if (Input::IsKey(DIK_LSHIFT))
	{
		_p->GetState()->ChangeState(_p->GetState()->pJet_, _p,false);

		if (_p->GetState()->playerState_ == _p->GetState()->pStanding_)
		{
			_p->GetState()->ChangeState(_p->GetState()->pStanding_, _p, false);
		}
	}
	
}

//�J�n
void RunningState::Enter(Player* _p)
{
}

//���͏���
void RunningState::HandleInput(Player* _p)
{
}
