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
	HandleInput(_p);
	//�d�͂����Z�b�g
	_p->IsAddGravity(false);

	Transform *ppos;
	ppos = _p->GetTransformAddress();
	//���͏���

	RayCastData downDataL; {
		//�������Ă��邩�m�F
		downDataL.start = ppos->position_;
		downDataL.start.x = ppos->position_.x - (PLAYER_MODEL_SIZE.x / 2);
		downDataL.start.y = ppos->position_.y + 0.01;
		XMStoreFloat3(&downDataL.dir, XMVectorSet(0, -1, 0, 0));
		Model::RayCast(_p->GetPlayerOnGround(), &downDataL);
	}
	if (downDataL.dist <= 0.5f) {
		//�߂荞�ݕ��A�ʒu��߂�
		XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - (downDataL.dist + 0.5f)  ,0 };
		XMStoreFloat3(&ppos->position_, length);
		_p->SetAcceleration(0);
	}
	RayCastData downDataR; {
		//�������Ă��邩�m�F
		downDataR.start = ppos->position_;
		downDataR.start.x = ppos->position_.x + (PLAYER_MODEL_SIZE.x / 2);
		downDataR.start.y = ppos->position_.y + 0.01;
		XMStoreFloat3(&downDataR.dir, XMVectorSet(0, -1, 0, 0));
		Model::RayCast(_p->GetPlayerOnGround(), &downDataR);
	}
	if (downDataR.dist <= 0.5f) {
		//�߂荞�ݕ��A�ʒu��߂�
		XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - (downDataR.dist + 0.5) ,0 };
		XMStoreFloat3(&ppos->position_,length); 
		_p->SetAcceleration(0);
	}

		{//State�ω�

			//standing
			if (!Input::IsKey(DIK_D) && !Input::IsKey(DIK_A)) {
				_p->GetState()->ChangeState(_p->GetState()->pStanding_, _p, true);
				AudioManager::Stop_FootSound();
			}
			//dead
			if (ppos->position_.y <= -10 && ppos->position_.y >= -13) {
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
