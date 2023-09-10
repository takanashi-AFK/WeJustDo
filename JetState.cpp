#include "JetState.h"
#include "Engine/Input.h"

#include "Player.h"
#include "AudioManager.h"

void JetState::Update(Player* _p)
{
	////���͏���
	//HandleInput(_p);
	XMFLOAT3 ppos;
	ppos = _p->GetPosition();
	Transform* TJumping = _p->GetTransformAddress();

	//{//State�ω�

	//	////�����v����
	//	//if (!Input::IsKey(DIK_D) && !Input::IsKey(DIK_A))
	//	//	_p->GetState()->ChangeState(_p->GetState()->pStanding_, _p, true);

		//dead
		if (ppos.y <= -3 && ppos.y >= -5)
			_p->GetState()->ChangeState(_p->GetState()->pDead_, _p, true);

	//	if (Input::IsKeyUp(DIK_SPACE)) {
	//	
	//		_p->GetState()->ChangeState(_p->GetState()->pJumping_, _p, true);
	//	}


	//}

	static float acs = 0 ;
	//�v���C���[�̏����擾
	Transform* t_Player = _p->GetTransformAddress();
	if (_p->GetState()->playerState_ != _p->GetState()->pJumping_  && Input::IsKeyDown(DIK_SPACE)) {
		acs = 0; 
	}
	if (_p->GetState()->playerState_ != _p->GetState()->pJumping_ && Input::IsKey(DIK_SPACE) && (Global::gFireWood > 0)) {
		_p->SetAcceleration(0);
		t_Player->position_.y += acs;
		if (acs < 0.1f)acs += 0.003f;
		Global::gFireWood - 1;
	}

	//���ړ��̏���
	float s = 0.1f;
	if (Input::IsKey(DIK_A)) { t_Player->position_.x -= s; t_Player->rotate_.y = -90; /*PolyJetEmitPos.x = PolyJetEmitPos.x + 0.5;*/ }
	else if (Input::IsKey(DIK_D)) { t_Player->position_.x += s; t_Player->rotate_.y = 90; }

	//SPACE�L�[����肪���ꂽ��&�n�ʂƂ̋�����n�ȉ��Ȃ�
	float Clearance = (PLAYER_MODEL_SIZE.y / 2);
	if (Input::IsKeyUp(DIK_SPACE) && (_p->GetDownData().dist < Clearance*1.2)) {
		_p->SetAcceleration(0);//�d�͂����Z�b�g
		_p->GetState()->ChangeState(_p->GetState()->pStanding_, _p);//���n��ԂɈړ�
	}


}

void JetState::Enter(Player* _p)
{
	//_p->SetIsJetNow(true);
	Model::SetAnimFrame(_p->GetModelHandle(), 0, 0, 0);
}

void JetState::HandleInput(Player* _p)
{
	//Transform* TJet = _p->GetTransformAddress();
	////�W�F�b�g�p�b�N�̋����@��������standing�ւ̑J�ڂ���������܂ŕۗ�
	//if (Input::IsKey(DIK_A)) { TJet->position_.x -= 0.5; TJet->rotate_.y = -90; /*PolyJetEmitPos.x = PolyJetEmitPos.x + 0.5;*/ }
	//else if (Input::IsKey(DIK_D)) { TJet->position_.x += 0.5; TJet->rotate_.y = 90; }

	//if (Input::IsKey(DIK_SPACE))
	//{
	//	TJet->position_.y += 0.2;
	//	
	//}

}
