#include "StandingState.h"
#include "Engine/Input.h"
#include "Player.h"
#include "StageManager.h"

void StandingState::Update(Player* _p)
{
	//���͏���
	HandleInput(_p);

	RayCastData downData; {
		//�������Ă��邩�m�F
		downData.start = _p->GetPosition();
		downData.start.y = _p->GetPosition().y - (float)(PLAYER_MODEL_SIZE.y / 2);
		XMStoreFloat3(&downData.dir, XMVectorSet(0, -1, 0, 0));
		Model::RayCast(_p->GetPlayerOnGround(), &downData);
	}
	//���C�̒�����1.0f��菬�����Ȃ�...
	if (downData.dist < 1.0f){
		//���n�_�Ɉʒu�����킹��
		//_p->SetPositionY(_p->GetPosition().y - downData.dist);
		//�߂荞�ݕ��A�ʒu��߂�
		XMVECTOR length = { 0,-downData.dist,0 };
		XMFLOAT3 tmpPos = _p->GetPosition();
		XMStoreFloat3(&tmpPos, XMLoadFloat3(&tmpPos) - (XMVectorSet(0, -1, 0, 0) - length));

		static float h=0;
		if (Input::IsKeyDown(DIK_UP))h += 0.1f;
		if (Input::IsKeyDown(DIK_DOWN))h -= 0.1f;
		tmpPos.y -= h;
		_p->SetPosition(tmpPos);
	}
}

void StandingState::Enter(Player* _p)
{
}

void StandingState::HandleInput(Player* _p)
{
	if (Input::IsKeyDown(DIK_SPACE)){
		_p->GetState()->ChangeState(_p->GetState()->pRunning_, _p);
	}
}
