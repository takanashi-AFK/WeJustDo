#include "StandingState.h"

//インクルード
#include "Player.h"


//更新
void StandingState::Update(Player* _p)
{
	//入力処理
	HandleInput(_p);

	RayCastData downData; {
		//当たっているか確認
		downData.start = _p->GetPosition();
		XMStoreFloat3(&downData.dir, XMVectorSet(0, -1, 0, 0));
		Model::RayCast(_p->GetPlayerOnGround(), &downData);
	}
	if (downData.dist < (PLAYER_MODEL_SIZE.y / 2)) {

		//めり込み分、位置を戻す
		XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - downData.dist,0 };
		XMFLOAT3 tmpPos = _p->GetPosition();
		XMStoreFloat3(&tmpPos, XMLoadFloat3(&tmpPos) + length); _p->SetPosition(tmpPos);

		//重力をリセット
		_p->IsAddGravity(false);
		_p->SetAcceleration(0);
	}
}

//開始
void StandingState::Enter(Player* _p)
{
}

//入力処理
void StandingState::HandleInput(Player* _p)
{
}
