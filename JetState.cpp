#include "JetState.h"
#include "Engine/Input.h"

#include "Player.h"
#include "AudioManager.h"

void JetState::Update(Player* _p)
{
	//���͏���
	HandleInput(_p);
	XMFLOAT3 ppos;
	ppos = _p->GetPosition();
	Transform* TJumping = _p->GetTransformAddress();

	{//State�ω�

		////�����v����
		//if (!Input::IsKey(DIK_D) && !Input::IsKey(DIK_A))
		//	_p->GetState()->ChangeState(_p->GetState()->pStanding_, _p, true);

		//dead
		if (ppos.y <= -3 && ppos.y >= -5)
			_p->GetState()->ChangeState(_p->GetState()->pDead_, _p, true);

		if (Input::IsKeyUp(DIK_SPACE)) {
		
			_p->GetState()->ChangeState(_p->GetState()->pJumping_, _p, true);
		}


	}
}

void JetState::Enter(Player* _p)
{

}

void JetState::HandleInput(Player* _p)
{
	Transform* TJet = _p->GetTransformAddress();
	//�W�F�b�g�p�b�N�̋����@��������standing�ւ̑J�ڂ���������܂ŕۗ�
	if (Input::IsKey(DIK_A)) { TJet->position_.x -= 0.5; TJet->rotate_.y = -90; /*PolyJetEmitPos.x = PolyJetEmitPos.x + 0.5;*/ }
	else if (Input::IsKey(DIK_D)) { TJet->position_.x += 0.5; TJet->rotate_.y = 90; }

	if (Input::IsKey(DIK_SPACE))
	{
		TJet->position_.y += 0.2;
		
	}

}
