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

	//�v���C���[�̃g�����X�t�H�[�������擾
	Transform* pt_Player = _p->GetTransformAddress();

	RayCastData downDataRight; {
		//���C�̊J�n�n�_��ݒ�
		downDataRight.start = pt_Player->position_;
		downDataRight.start.x += ((PLAYER_MODEL_SIZE.x) - 0.1f);

		//���C�̔��˕�����ݒ�
		XMStoreFloat3(&downDataRight.dir, XMVectorSet(0, -1, 0, 0));

		//���C�𔭎�
		Model::RayCast(_p->GetPlayerOnGround(), &downDataRight);
	}
	if (downDataRight.dist <= (PLAYER_MODEL_SIZE.y / 2)) {
		//�߂荞�ݕ��A�ʒu��߂�
		XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - std::abs(downDataRight.dist),0 };
		XMStoreFloat3(&pt_Player->position_, XMLoadFloat3(&pt_Player->position_) + length);

		//�d�͂����Z�b�g
		_p->IsAddGravity(false);
		_p->SetAcceleration(0);
	}

		RayCastData downDataLeft; {
		//���C�̊J�n�n�_��ݒ�
			downDataLeft.start = pt_Player->position_;
			downDataLeft.start.x -= ((PLAYER_MODEL_SIZE.x) - 0.1f);

		//���C�̔��˕�����ݒ�
		XMStoreFloat3(&downDataLeft.dir, XMVectorSet(0, -1, 0, 0));

		//���C�𔭎�
		Model::RayCast(_p->GetPlayerOnGround(), &downDataLeft);
	}
	if (downDataLeft.dist <= (PLAYER_MODEL_SIZE.y / 2)) {
		//�߂荞�ݕ��A�ʒu��߂�
		XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - std::abs(downDataLeft.dist),0 };
		XMStoreFloat3(&pt_Player->position_, XMLoadFloat3(&pt_Player->position_) + length);

		//�d�͂����Z�b�g
		_p->IsAddGravity(false);
		_p->SetAcceleration(0);
	}


	//RayCastData downData; {
	//	//�������Ă��邩�m�F
	//	downData.start = _p->GetPosition();
	//	XMStoreFloat3(&downData.dir, XMVectorSet(0, -1, 0, 0));
	//	Model::RayCast(_p->GetPlayerOnGround(), &downData);
	//}
	//if (downData.dist < (PLAYER_MODEL_SIZE.y / 2)) {

	//	//�߂荞�ݕ��A�ʒu��߂�
	//	XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - downData.dist,0 };
	//	XMFLOAT3 tmpPos = _p->GetPosition();
	//	XMStoreFloat3(&tmpPos, XMLoadFloat3(&tmpPos) + length); _p->SetPosition(tmpPos);

	//	//�d�͂����Z�b�g
	//	_p->IsAddGravity(false);
	//	_p->SetAcceleration(0);
	//}
	XMFLOAT3 ppos;
	ppos = _p->GetPosition();

	//State�ω�
	{
		//Running->
		if (Input::IsKey(DIK_D) || Input::IsKey(DIK_A))
			_p->GetState()->ChangeState(_p->GetState()->pRunning_, _p, true);

		//Dead->
		if (ppos.y <= -10 && ppos.y >= -13)
			_p->GetState()->ChangeState(_p->GetState()->pDead_, _p, true);

		//Jumping->
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


