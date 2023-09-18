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

	XMFLOAT3 ppos;
	ppos = _p->GetPosition();
	//���͏���

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

			_p->SetAcceleration(0);
		}

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
