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
	//���͏���
	HandleInput(_p);

	{//State�ω�

		//standing
		if (!Input::IsKey(DIK_D) && !Input::IsKey(DIK_A))
			_p->GetState()->ChangeState(_p->GetState()->pStanding_, _p, false);
		//dead
		if (ppos.y <= -3 && ppos.y >= -5)
			_p->GetState()->ChangeState(_p->GetState()->pDead_, _p, true);

		if(Input::IsKeyDown(DIK_SPACE))
			_p->GetState()->ChangeState(_p->GetState()->pJumping_, _p, true);
	}


}

//�J�n
void RunningState::Enter(Player* _p)
{
	Model::SetAnimFrame(_p->GetModelHandle(), 0, 44, 1);
}

//���͏���
void RunningState::HandleInput(Player* _p)
{
	Transform* TRunning = _p->GetTransformAddress();
	float s = 0.1f;
	if (Input::IsKey(DIK_A)) { TRunning->position_.x -= s; TRunning->rotate_.y = -90; /*PolyJetEmitPos.x = PolyJetEmitPos.x + 0.5;*/ }
	else if (Input::IsKey(DIK_D)) { TRunning->position_.x += s; TRunning->rotate_.y = 90; }
}
