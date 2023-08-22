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
		_p->SetPositionY(_p->GetPosition().y - downData.dist);
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
