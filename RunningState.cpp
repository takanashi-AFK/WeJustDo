#include "RunningState.h"

//インクルード
#include "Player.h"
#include "AudioManager.h"
#include "Engine/VFX.h"
#include "PlayerStateManager.h"
#include "Engine/Input.h"


//更新
void RunningState::Update(Player* _p)
{
	XMFLOAT3 ppos;
	ppos = _p->GetPosition();
	//入力処理
	HandleInput(_p);
	//死亡時エフェクト
	if (ppos.y <= -3 && ppos.y >= -5)
	{
		_p->GetState()->ChangeState(_p->GetState()->pDead_, _p,true);
	}

	//ジェット使用時
	if (Input::IsKey(DIK_LSHIFT))
	{
		_p->GetState()->ChangeState(_p->GetState()->pJet_, _p,false);

		if (_p->GetState()->playerState_ == _p->GetState()->pStanding_)
		{
			_p->GetState()->ChangeState(_p->GetState()->pStanding_, _p, false);
		}
	}
	
}

//開始
void RunningState::Enter(Player* _p)
{
}

//入力処理
void RunningState::HandleInput(Player* _p)
{
}
