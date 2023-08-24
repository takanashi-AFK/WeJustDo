#include "StandingState.h"
#include "Engine/Input.h"
#include "Player.h"
#include "StageManager.h"

void StandingState::Update(Player* _p)
{
	//入力処理
	HandleInput(_p);

	RayCastData downData; {
		//当たっているか確認
		downData.start = _p->GetPosition();
		downData.start.y = _p->GetPosition().y - (float)(PLAYER_MODEL_SIZE.y / 2);
		XMStoreFloat3(&downData.dir, XMVectorSet(0, -1, 0, 0));
		Model::RayCast(_p->GetPlayerOnGround(), &downData);
	}
	//レイの長さが1.0fより小さいなら...
	if (downData.dist < 1.0f){
		//着地点に位置を合わせる
		//_p->SetPositionY(_p->GetPosition().y - downData.dist);
		//めり込み分、位置を戻す
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
