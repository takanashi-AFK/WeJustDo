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
	HandleInput(_p);
	//重力をリセット
	_p->IsAddGravity(false);

	Transform *ppos;
	ppos = _p->GetTransformAddress();
	//入力処理

	RayCastData downDataL; {
		//当たっているか確認
		downDataL.start = ppos->position_;
		downDataL.start.x = ppos->position_.x - (PLAYER_MODEL_SIZE.x / 2);
		downDataL.start.y = ppos->position_.y + 0.01;
		XMStoreFloat3(&downDataL.dir, XMVectorSet(0, -1, 0, 0));
		Model::RayCast(_p->GetPlayerOnGround(), &downDataL);
	}
	if (downDataL.dist <= 0.5f) {
		//めり込み分、位置を戻す
		XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - (downDataL.dist + 0.5f)  ,0 };
		XMStoreFloat3(&ppos->position_, length);
		_p->SetAcceleration(0);
	}
	RayCastData downDataR; {
		//当たっているか確認
		downDataR.start = ppos->position_;
		downDataR.start.x = ppos->position_.x + (PLAYER_MODEL_SIZE.x / 2);
		downDataR.start.y = ppos->position_.y + 0.01;
		XMStoreFloat3(&downDataR.dir, XMVectorSet(0, -1, 0, 0));
		Model::RayCast(_p->GetPlayerOnGround(), &downDataR);
	}
	if (downDataR.dist <= 0.5f) {
		//めり込み分、位置を戻す
		XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - (downDataR.dist + 0.5) ,0 };
		XMStoreFloat3(&ppos->position_,length); 
		_p->SetAcceleration(0);
	}

		{//State変化

			//standing
			if (!Input::IsKey(DIK_D) && !Input::IsKey(DIK_A)) {
				_p->GetState()->ChangeState(_p->GetState()->pStanding_, _p, true);
				AudioManager::Stop_FootSound();
			}
			//dead
			if (ppos->position_.y <= -10 && ppos->position_.y >= -13) {
				_p->GetState()->ChangeState(_p->GetState()->pDead_, _p, true);
				AudioManager::Stop_FootSound();
			}

			if (Input::IsKeyDown(DIK_SPACE)) {
				_p->GetState()->ChangeState(_p->GetState()->pJumping_, _p, true);
				AudioManager::Stop_FootSound();
			}
		}


}
//開始
void RunningState::Enter(Player* _p)
{
	if (AudioManager::isJetPlayNow())
		AudioManager::Stop_JetSound();

	Model::SetAnimFrame(_p->GetModelHandle(), 0, 44, 1);
	AudioManager::Play_FootSound();

}

//入力処理
void RunningState::HandleInput(Player* _p)
{
	Transform* TRunning = _p->GetTransformAddress();
	float s = _p->GetSpeed();
	if (Input::IsKey(DIK_A)) { TRunning->position_.x -= s; TRunning->rotate_.y = -90; /*PolyJetEmitPos.x = PolyJetEmitPos.x + 0.5;*/ }
	else if (Input::IsKey(DIK_D)) { TRunning->position_.x += s; TRunning->rotate_.y = 90; }
}
