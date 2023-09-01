#include "StandingState.h"

//�C���N���[�h
#include "Player.h"


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
}

//�J�n
void StandingState::Enter(Player* _p)
{
}

//���͏���
void StandingState::HandleInput(Player* _p)
{
}
