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

	//�v���C���[�̃g�����X�t�H�[�������擾
	Transform* pt_Player = _p->GetTransformAddress();

	RayCastData downDataRight; {
		//���C�̊J�n�n�_��ݒ�
		downDataRight.start = pt_Player->position_;
		downDataRight.start.x += ((PLAYER_MODEL_SIZE.x));
		downDataRight.start.y -= ((PLAYER_MODEL_SIZE.x/2)-0.1);

		//���C�̔��˕�����ݒ�
		XMStoreFloat3(&downDataRight.dir, XMVectorSet(0, -1, 0, 0));

		//���C�𔭎�
		Model::RayCast(_p->GetPlayerOnGround(), &downDataRight);
	}
	if (downDataRight.dist <= (PLAYER_MODEL_SIZE.y / 2)) {
		//�߂荞�ݕ��A�ʒu��߂�
		XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - std::abs(downDataRight.dist-0.1f),0 };
		XMStoreFloat3(&pt_Player->position_, XMLoadFloat3(&pt_Player->position_) + length);

		//�d�͂����Z�b�g
		_p->IsAddGravity(false);
		_p->SetAcceleration(0);
	}

	RayCastData downDataLeft; {
		//���C�̊J�n�n�_��ݒ�
		downDataLeft.start = pt_Player->position_;
		downDataLeft.start.x -= ((PLAYER_MODEL_SIZE.x) - 0.1f);
		downDataLeft.start.y -= ((PLAYER_MODEL_SIZE.x/2)-0.1);

		//���C�̔��˕�����ݒ�
		XMStoreFloat3(&downDataLeft.dir, XMVectorSet(0, -1, 0, 0));

		//���C�𔭎�
		Model::RayCast(_p->GetPlayerOnGround(), &downDataLeft);
	}
	if (downDataLeft.dist <= (PLAYER_MODEL_SIZE.y / 2)) {
		//�߂荞�ݕ��A�ʒu��߂�
		XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - std::abs(downDataLeft.dist-0.1f),0 };
		XMStoreFloat3(&pt_Player->position_, XMLoadFloat3(&pt_Player->position_) + length);

		//�d�͂����Z�b�g
		_p->IsAddGravity(false);
		_p->SetAcceleration(0);
	}
	XMFLOAT3 ppos;
	ppos = _p->GetPosition();
	//���͏���
	HandleInput(_p);

	{//State�ω�

		//standing
		if (!Input::IsKey(DIK_D) && !Input::IsKey(DIK_A)) {
			_p->GetState()->ChangeState(_p->GetState()->pStanding_, _p, true);
			AudioManager::Stop_FootSound();
		}
		//dead
		if (ppos.y <= -10 && ppos.y >= -13) {
			_p->GetState()->ChangeState(_p->GetState()->pDead_, _p, true);
			AudioManager::Stop_FootSound();
		}

		if (Input::IsKeyDown(DIK_SPACE)) {
			_p->GetState()->ChangeState(_p->GetState()->pJumping_, _p, true);
			AudioManager::Stop_FootSound();
		}
	}
}

//�J�n
void RunningState::Enter(Player* _p)
{
	if (AudioManager::isJetPlayNow())
		AudioManager::Stop_JetSound();

	Model::SetAnimFrame(_p->GetModelHandle(), 0, 44, 1);
	AudioManager::Play_FootSound();

}

//���͏���
void RunningState::HandleInput(Player* _p)
{
	Transform* TRunning = _p->GetTransformAddress();
	float s = _p->GetSpeed();
	if (Input::IsKey(DIK_A)) { TRunning->position_.x -= s; TRunning->rotate_.y = -90; /*PolyJetEmitPos.x = PolyJetEmitPos.x + 0.5;*/ }
	else if (Input::IsKey(DIK_D)) { TRunning->position_.x += s; TRunning->rotate_.y = 90; }
}
