#include "StandingState.h"

//インクルード
#include "Player.h"
#include "AudioManager.h"
#include "Engine/Input.h"
#include "Engine/VFX.h"


//更新
void StandingState::Update(Player* _p)
{
	//入力処理
	HandleInput(_p);

	//プレイヤーのトランスフォーム情報を取得
	Transform* pt_Player = _p->GetTransformAddress();

	RayCastData downDataRight; {
		//レイの開始地点を設定
		downDataRight.start = pt_Player->position_;
		downDataRight.start.x += ((PLAYER_MODEL_SIZE.x) - 0.1f);

		//レイの発射方向を設定
		XMStoreFloat3(&downDataRight.dir, XMVectorSet(0, -1, 0, 0));

		//レイを発射
		Model::RayCast(_p->GetPlayerOnGround(), &downDataRight);
	}
	if (downDataRight.dist <= (PLAYER_MODEL_SIZE.y / 2)) {
		//めり込み分、位置を戻す
		XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - std::abs(downDataRight.dist),0 };
		XMStoreFloat3(&pt_Player->position_, XMLoadFloat3(&pt_Player->position_) + length);

		//重力をリセット
		_p->IsAddGravity(false);
		_p->SetAcceleration(0);
	}

		RayCastData downDataLeft; {
		//レイの開始地点を設定
			downDataLeft.start = pt_Player->position_;
			downDataLeft.start.x -= ((PLAYER_MODEL_SIZE.x) - 0.1f);

		//レイの発射方向を設定
		XMStoreFloat3(&downDataLeft.dir, XMVectorSet(0, -1, 0, 0));

		//レイを発射
		Model::RayCast(_p->GetPlayerOnGround(), &downDataLeft);
	}
	if (downDataLeft.dist <= (PLAYER_MODEL_SIZE.y / 2)) {
		//めり込み分、位置を戻す
		XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - std::abs(downDataLeft.dist),0 };
		XMStoreFloat3(&pt_Player->position_, XMLoadFloat3(&pt_Player->position_) + length);

		//重力をリセット
		_p->IsAddGravity(false);
		_p->SetAcceleration(0);
	}


	//RayCastData downData; {
	//	//当たっているか確認
	//	downData.start = _p->GetPosition();
	//	XMStoreFloat3(&downData.dir, XMVectorSet(0, -1, 0, 0));
	//	Model::RayCast(_p->GetPlayerOnGround(), &downData);
	//}
	//if (downData.dist < (PLAYER_MODEL_SIZE.y / 2)) {

	//	//めり込み分、位置を戻す
	//	XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - downData.dist,0 };
	//	XMFLOAT3 tmpPos = _p->GetPosition();
	//	XMStoreFloat3(&tmpPos, XMLoadFloat3(&tmpPos) + length); _p->SetPosition(tmpPos);

	//	//重力をリセット
	//	_p->IsAddGravity(false);
	//	_p->SetAcceleration(0);
	//}
	XMFLOAT3 ppos;
	ppos = _p->GetPosition();

	//State変化
	{
		//Running->
		if (Input::IsKey(DIK_D) || Input::IsKey(DIK_A))
			_p->GetState()->ChangeState(_p->GetState()->pRunning_, _p, true);

		//Dead->
		if (ppos.y <= -10 && ppos.y >= -13)
			_p->GetState()->ChangeState(_p->GetState()->pDead_, _p, true);

		//Jumping->
		if (Input::IsKeyDown(DIK_SPACE))
			_p->GetState()->ChangeState(_p->GetState()->pJumping_, _p, true);

	}
}
//開始
void StandingState::Enter(Player* _p)
{
	if(AudioManager::isJetPlayNow())
	AudioManager::Stop_JetSound();

	//重力をリセット
	_p->SetAcceleration(0);

	//アニメーションをストップ
	Model::SetAnimFrame(_p->GetModelHandle(), 0, 0, 1);

	//エフェクト処理
	_p->InitRandEffect();
	EmitterData Emit = _p->GetRandEData();
	VFX::Start(Emit);
}

//入力処理	
void StandingState::HandleInput(Player* _p)
{

	
}


