#include "RunningState.h"
#include "Engine/Input.h"
#include "Player.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"


void RunningState::Update(Player* _p)
{
	Camera::SetPosition(XMFLOAT3(_p->GetPosition().x, 3, -8));

	Camera::SetTarget(_p->GetPosition());

	//入力処理
	HandleInput(_p);
}

void RunningState::Enter(Player* _p)
{
	_p->SetPositionY(-2);
}

void RunningState::HandleInput(Player* _p)
{
	if (Input::IsKey(DIK_D))
	{
		static float s; s += 0.1f;
		_p->SetPositionX(s);
	}
	
	if (Input::IsKeyDown(DIK_C)) {
		_p->GetState()->ChangeState(_p->GetState()->pStanding_, _p);
	}

	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager *toResult = _p->GetSceneData();
		toResult->ChangeScene(SCENE_ID_RESULT, TID_BLACKOUT);//あとでタイトルにする
	}
}
