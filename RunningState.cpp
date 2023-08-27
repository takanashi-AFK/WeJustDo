#include "RunningState.h"

//インクルード
#include "Player.h"

//更新
void RunningState::Update(Player* _p)
{
	//入力処理
	HandleInput(_p);
}

//開始
void RunningState::Enter(Player* _p)
{
}

//入力処理
void RunningState::HandleInput(Player* _p)
{
}
