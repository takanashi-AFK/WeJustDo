#include "Player.h"

//インクルード
#include "Engine/Input.h"
#include "Stage.h"
#include "Engine/Transition.h"
#include "Engine/Image.h"
#include "Engine/Debug.h"
#include "Engine/Camera.h"
#include "AudioManager.h"

//コンストラクタ
Player::Player(GameObject* _parent, string _modelFileName)
	:SolidObject(_parent,_modelFileName,"Player"),
	pState_(nullptr),pStage_(),hGroundModel_(0),acceleration_(0),speed_(0)
{
	//プレイヤーの状態を「立ち状態」で初期化
	ASSIGN(pState_,new PlayerStateManager);
}

//初期化
void Player::ChildInitialize()
{
	//状態の初期化
	ASSIGN(pState_->playerState_, pState_->pStanding_);
	
	//モデルのロード
	ASSIGN(Marker, Model::Load("Models/debugMarker.fbx"));
	ASSIGN(hBox_, Model::Load("Models/defaultModel.fbx"));

	//位置の初期化
	transform_.position_ = { 0.0f,1.0f,0.0f };
	transform_.rotate_.y = 90;
	//初期状態の開始処理
	pState_->Enter(this);

	isMove_ = true;

	InitDeadEffect();
	InitRandEffect();

	//pDead = new PolyLine(1,50);
	//pDead->Load("Effects/Tex.png");
	pJet = new PolyLine(0.4, 10);
	pJet->Load("Effects/Fire.png");

	Camera::SetPosition(transform_.position_.x + 5, transform_.position_.y + 3, -13.0f);
	Camera::SetTarget(transform_.position_.x + 5, transform_.position_.y + 3, 0.0f);

}

//更新
void Player::ChildUpdate()
{
	PolyJetEmitPos = XMFLOAT3(transform_.position_.x - (PLAYER_MODEL_SIZE.x / 4), transform_.position_.y - (PLAYER_MODEL_SIZE.x / 4), transform_.position_.z);
	pJet->AddPosition(PolyJetEmitPos);

	//重力を加える
	AddGravity(&transform_);

	//アイテムとの当たり判定
	if (isMove_) {
		
		GetFirewood();
		
		TerrainInteraction();

		//状態ごとの更新
		pState_->Update(this);

		//ステージとのあたり判定
		StageRayCast();


		Camera::SetPosition(transform_.position_.x + 5, transform_.position_.y + 3, -13.0f);
		Camera::SetTarget(transform_.position_.x + 5, transform_.position_.y + 3, 0.0f);
	}
}

//開放
void Player::ChildRelease()
{
	SAFE_DELETE(pState_);
	//ポリライン解放
	pJet->Release();
}

//描画
void Player::ChildDraw()
{
	//ボックスを描画
	Direct3D::SetShader(Direct3D::SHADER_UNLIT);
	Transform t_Box; t_Box.position_ = transform_.position_; t_Box.position_.y + 0.5f;
	Model::SetTransform(hBox_, t_Box);Model::Draw(hBox_);
}

void Player::StageRayCast()
{
	//ステージのモデル番号を取得
	ASSIGN(hGroundModel_, dynamic_cast<Stage*>(FindObject("Stage"))->GetStageModelHandle(m_Ground));

	//左方向の当たり判定
	{
		RayCastData leftData; {
			leftData.start = transform_.position_;
			RayStartPos = leftData.start;
			XMStoreFloat3(&leftData.dir, XMVectorSet(-1, 0, 0, 0));
			Model::RayCast(hGroundModel_, &leftData);
			leftLandingPoint = leftData.pos;
		}
		if (leftData.dist < (PLAYER_MODEL_SIZE.x / 2)) {
			//めり込み分、位置を戻す
			XMVECTOR length = { -leftData.dist - (PLAYER_MODEL_SIZE.x / 2),0,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(-1, 0, 0, 0) - length));
		}
	}

	//右方向のあたり判定
	{
		RayCastData rightData; {
			//当たっているかを確認
			rightData.start = transform_.position_;					//発射位置の指定
			XMStoreFloat3(&rightData.dir, XMVectorSet(1, 0, 0, 0));	//発射方向の指定
			Model::RayCast(hGroundModel_, &rightData);				//レイを発射
			rightLandingPoint = rightData.pos;
		}
		//レイの長さが1.0以下だったら...
		if (rightData.dist < (PLAYER_MODEL_SIZE.x / 2)) {
			//めり込み分、位置を戻す
			XMVECTOR length = { rightData.dist + (PLAYER_MODEL_SIZE.x / 2),0,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(1, 0, 0, 0) - length));
		}
	}

	//上方向のあたり判定
	{
		RayCastData upData; {
			//当たっているか確認
			upData.start = transform_.position_;
			XMStoreFloat3(&upData.dir, XMVectorSet(0, 1, 0, 0));
			Model::RayCast(hGroundModel_, &upData);
			upLandingPoint = upData.pos;
		}
		//レイの長さが1.0以下だったら...
		if (upData.dist < (PLAYER_MODEL_SIZE.y / 2)) {
			//めり込み分、位置を戻す
			XMVECTOR length = { 0, (PLAYER_MODEL_SIZE.y / 2) + upData.dist,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(0, 1, 0, 0) - length));
			SetAcceleration(2);
		}
	}

	//StandingState,RunningStateときのみ行うからState内で処理を行う
	//下方向のあたり判定
	{
		RayCastData downData; {
			//当たっているか確認
			downData.start = transform_.position_;
			XMStoreFloat3(&downData.dir, XMVectorSet(0, -1, 0, 0));
			Model::RayCast(hGroundModel_, &downData);
			downLandingPoint = downData.pos;
			downData_ = downData;
		}
		if (downData.dist < (PLAYER_MODEL_SIZE.y / 2)) {
			//状態を"Standing"に変更
			pState_->ChangeState(pState_->pStanding_, this);

			//jump状態を終了
			isJumpNow_ = false;
		}
		else
			isAddGravity_ = true;
	}
}

void Player::AddGravity(Transform* _transform)
{
	if (!isAddGravity_)return;

	//重力を加える
	_transform->position_ = Transform::Float3Add(_transform->position_, VectorToFloat3((XMVectorSet(0, -1, 0, 0) / 10) * acceleration_));
	acceleration_ += GRAVITY_ADDITION;
}

void Player::InitDeadEffect()
{
	DeadEffectData.textureFileName = "Effects/cloudA.png";
	DeadEffectData.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	DeadEffectData.delay = 0;
	DeadEffectData.number = 1;
	DeadEffectData.lifeTime = 60;
	DeadEffectData.gravity = -0.002f;
	DeadEffectData.direction = XMFLOAT3(0, 1, 0);
	DeadEffectData.directionRnd = XMFLOAT3(0, 0, 0);
	DeadEffectData.speed = 0.01f;
	DeadEffectData.speedRnd = 0.0;
	DeadEffectData.size = XMFLOAT2(1,10);
	DeadEffectData.sizeRnd = XMFLOAT2(0.4, 0.4);
	DeadEffectData.scale = XMFLOAT2(1.01, 1.01);
	DeadEffectData.color = XMFLOAT4(0, 0, 1, 1);
	DeadEffectData.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);
	
}

void Player::InitRandEffect()
{
	RandEffectData_.textureFileName = "Effects/RandSmoke2.png";
	RandEffectData_.position = XMFLOAT3(transform_.position_.x, transform_.position_.y - 0.2,0);
	RandEffectData_.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	RandEffectData_.delay = 0;
	RandEffectData_.number = 1;
	RandEffectData_.lifeTime = 40;
	RandEffectData_.speed = 0.01f;
	RandEffectData_.speedRnd = 0.0;
	RandEffectData_.size = XMFLOAT2(1,0.5);
	RandEffectData_.scale = XMFLOAT2(1.01, 1.01);
	RandEffectData_.color = XMFLOAT4(1,1,1,1);
	RandEffectData_.deltaColor = XMFLOAT4(0, 0, 0, -0.1);
}

EmitterData Player::GetDeadEData()
{
	return DeadEffectData;
}

EmitterData Player::GetRandEData()
{
	return RandEffectData_;
}

PolyLine Player::GetJettPData()
{
	return *pJet;
}

void Player::SetIsJetNow(bool _jet)
{
	isJetNow_ = _jet;
}

void Player::GetFirewood()
{
	Stage* pS = (Stage*)(FindObject("Stage"));
	if (pS->AtItem(this, 1) || pS->AtItem(this,2)) {

		//エフェクト
		firewoodNum_+=5;
		//エフェクト

		pS->SetItem(round(transform_.position_.x), round(transform_.position_.y), 0);
	}
}

void Player::TerrainInteraction()
{
	Stage* pS = (Stage*)(FindObject("Stage"));

	//足場が泥の時
	if (pS->AtItem(this, 2))
	{
		SetSpeed(0.01f);
	}
	else SetSpeed(0.1f);
}

void Player::PolyDraw()
{
	//ポリラインを描画(ジェット噴射effect)
	if (pState_->playerState_ == pState_->pJet_)pJet->Draw();
}

void Player::SetDrawTransform()
{
	Direct3D::SetShader(Direct3D::SHADER_3D);
	Transform t_Draw; t_Draw = transform_;
	t_Draw.position_.y -= 0.5f;
	t_Draw.scale_ = { 0.1f,0.1f,0.1f };

	Model::SetTransform(hModel_, t_Draw);
}
