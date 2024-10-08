#include "JetState.h"
#include "Engine/Input.h"

#include "Player.h"
#include "AudioManager.h"
#include "Engine/SceneManager.h"

void JetState::Update(Player* _p)
{
	////入力処理
	//HandleInput(_p);
	XMFLOAT3 ppos;
	ppos = _p->GetPosition();
	Transform* TJumping = _p->GetTransformAddress();

	//{//State変化

	//	////ここ要検討
	//	//if (!Input::IsKey(DIK_D) && !Input::IsKey(DIK_A))
	//	//	_p->GetState()->ChangeState(_p->GetState()->pStanding_, _p, true);

		//dead
		if (ppos.y <= -10 && ppos.y >= -13)
			_p->GetState()->ChangeState(_p->GetState()->pDead_, _p, true);

	//	if (Input::IsKeyUp(DIK_SPACE)) {
	//	
	//		_p->GetState()->ChangeState(_p->GetState()->pJumping_, _p, true);
	//	}

	//}

	static float acs = 0 ;
	//プレイヤーの情報を取得
	Transform* t_Player = _p->GetTransformAddress();
	if (_p->GetState()->playerState_ != _p->GetState()->pJumping_  && Input::IsKeyDown(DIK_SPACE)) {
		acs = 0; 
	}
	if (_p->GetState()->playerState_ != _p->GetState()->pJumping_ && Input::IsKey(DIK_SPACE) && (Global::gFireWood > 0)) {
		_p->SetAcceleration(0);
		t_Player->position_.y += acs;
		if (acs < 0.1f)acs += 0.003f;
		Global::gFireWood--;
	}

	//横移動の処理
	float s = _p->GetSpeed()+0.02;
	if (Input::IsKey(DIK_A)) { t_Player->position_.x -= s; t_Player->rotate_.y = -90; /*PolyJetEmitPos.x = PolyJetEmitPos.x + 0.5;*/ }
	else if (Input::IsKey(DIK_D)) { t_Player->position_.x += s; t_Player->rotate_.y = 90; }

	//SPACEキーから手が離れたら&地面との距離がn以下なら
	float Clearance = (PLAYER_MODEL_SIZE.y / 2);
	if (Input::IsKeyUp(DIK_SPACE) && (_p->GetDownData().dist < Clearance*1.2)) {
		_p->SetAcceleration(0);//重力をリセット
		_p->GetState()->ChangeState(_p->GetState()->pStanding_, _p);//着地状態に移動
		AudioManager::Stop_JetSound();
	}

	if (Input::IsKeyUp(DIK_SPACE)) {
		AudioManager::Stop_JetSound();
	}
}

void JetState::Enter(Player* _p)
{
	//_p->SetIsJetNow(true);
	Model::SetAnimFrame(_p->GetModelHandle(), 0, 0, 0);
	AudioManager::Play_JetSound();
}

void JetState::HandleInput(Player* _p)
{
	//Transform* TJet = _p->GetTransformAddress();
	////ジェットパックの挙動　いったんstandingへの遷移が完成するまで保留
	//if (Input::IsKey(DIK_A)) { TJet->position_.x -= 0.5; TJet->rotate_.y = -90; /*PolyJetEmitPos.x = PolyJetEmitPos.x + 0.5;*/ }
	//else if (Input::IsKey(DIK_D)) { TJet->position_.x += 0.5; TJet->rotate_.y = 90; }

	//if (Input::IsKey(DIK_SPACE))
	//{
	//	TJet->position_.y += 0.2;
	//	
	//}

}
