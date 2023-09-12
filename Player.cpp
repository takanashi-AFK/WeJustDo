#include "Player.h"

//インクルード
#include "Engine/Input.h"
#include "Stage.h"
#include "Engine/Transition.h"
#include "Engine/Image.h"
#include "Engine/Debug.h"
#include "Engine/Camera.h"
#include "AudioManager.h"
#include "Engine/Audio.h"
#include "Engine/SceneManager.h"

//コンストラクタ
Player::Player(GameObject* _parent, string _modelFileName)
	:SolidObject(_parent,_modelFileName,"Player")
	,hDebugBox_(-1),pJet(nullptr),pState_(nullptr),hGroundModel_(0)
	,acceleration_(0),isAddGravity_(false),isMove_(false),speed_(0)
	,RandEffectData_(),DeadEffectData(),PlusOneEffectData()
{
	//プレイヤーの状態を「立ち状態」で初期化
	ASSIGN(pState_,new PlayerStateManager);
}

//初期化
void Player::ChildInitialize()
{
	//状態の初期化
	ASSIGN(pState_->playerState_, pState_->pStanding_);
	
	//モデルのロード-debug用
	ASSIGN(hDebugBox_, Model::Load("Models/defaultModel.fbx"));

	//位置の初期化
	SetPositionY(1.0f);
	SetRotateY(90);

	//初期状態の開始処理
	pState_->Enter(this);

	//各エフェクトの初期化
	{
		InitDeadEffect();
		InitRandEffect();
		InitPlusOneEffect();
		InitBombEffect();
		//pDead = new PolyLine(1,50);
		//pDead->Load("Effects/Tex.png");

		pJet = new PolyLine(0.4, 10);
		pJet->Load("Effects/Fire.png");
	}
	
	//カメラの初期化
	Camera::SetPosition(transform_.position_.x + 5, transform_.position_.y + 3, -13.0f);
	Camera::SetTarget(transform_.position_.x + 5, transform_.position_.y + 3, 0.0f);

}

//更新
void Player::ChildUpdate()
{
	//かいだカメラ
	{
		static float camMove = 4.5f;
		if (!(transform_.position_.y > 9))
		{
			if (camMove > 4.5f)
				camMove -= 0.3f;
			else camMove = 4.5f;
		}
		else
		{
			if (camMove < 14)
				camMove += 0.3f;
			else
				camMove = 14.0f;
		}
		Camera::SetPosition(transform_.position_.x + 5, camMove, -13.0f);
		Camera::SetTarget(transform_.position_.x + 5, camMove - 0.5f, 0.0f);
	}
	
	//たかなしカメラ
	{
		/*
		if (transform_.position_.y >= -1 && transform_.position_.y <= 15) {
			Camera::SetPosition(transform_.position_.x + 5, transform_.position_.y + 3, -13.0f);
			Camera::SetTarget(transform_.position_.x + 5, transform_.position_.y + 3, 0.0f);
		}
		else if (transform_.position_.y > 15) {
			Camera::SetPosition(transform_.position_.x + 5, Camera::GetPosition().y, -13.0f);
			Camera::SetTarget(transform_.position_.x + 5, Camera::GetTarget().y, 0.0f);
		}
		else if (transform_.position_.y <= -3 && transform_.position_.y >= -5)
		{
			Camera::SetPosition(Camera::GetPosition().x, Camera::GetPosition().y, Camera::GetPosition().z);
			Camera::SetTarget(Camera::GetTarget());
		}*/
	}

	//falseなら動作処理を行わずreturn
	if (!isMove_)return;

	//ジェット時のエフェクト位置を調整
	{
		pJet->AddPosition(XMFLOAT3(
			transform_.position_.x - (PLAYER_MODEL_SIZE.x / 4),	//x
			transform_.position_.y - (PLAYER_MODEL_SIZE.x / 4),	//y
			transform_.position_.z));							//z
	}

	if (Input::IsKeyDown(DIK_RETURN))
	{
		SetIsMove(false);
		bombEffectData.position = XMFLOAT3(transform_.position_.x, transform_.position_.y, transform_.position_.z -2);
		int a = VFX::Start(bombEffectData);
		SceneManager* pScM = (SceneManager*)FindObject("SceneManager");
		pScM->ChangeScene(SCENE_ID_RESULT, TID_WHITEOUT);
	}

	//重力を加える
	AddGravity(&transform_);

	//地形(Stage)との判定時の処理
	TerrainInteraction();

	//状態ごとの更新(※StageRayCast()より後に処理するとバグる)
	pState_->Update(this);

	//ステージとの当たり判定
	StageRayCast();

}

//開放
void Player::ChildRelease()
{
	SAFE_DELETE(pState_);
	pJet->Release();
}

//描画
void Player::ChildDraw()
{
	//debug-UnlitBoxDraw
	{
		/*Direct3D::SetShader(Direct3D::SHADER_UNLIT);
		Transform t_Box; t_Box.position_ = transform_.position_; t_Box.position_.y + 0.5f;
		Model::SetTransform(hBox_, t_Box);Model::Draw(hBox_);*/
	}
	
}

void Player::StageRayCast()
{
	//ステージのモデル番号を取得
	ASSIGN(hGroundModel_, dynamic_cast<Stage*>(FindObject("Stage"))->GetStageModelHandle(m_Ground));

	//左方向の当たり判定
	{
		RayCastData leftData; {
			leftData.start = transform_.position_;
			XMStoreFloat3(&leftData.dir, XMVectorSet(-1, 0, 0, 0));
			Model::RayCast(hGroundModel_, &leftData);
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
			downData_ = downData;
		}
		if (downData.dist < (PLAYER_MODEL_SIZE.y / 2)) {
			//状態を"Standing"に変更
			pState_->ChangeState(pState_->pStanding_, this);
		}
		else
			isAddGravity_ = true;
	}
}

void Player::AddGravity(Transform* _transform)
{
	//加えないならreturn
	if (!isAddGravity_)return;

	//重力を加える
	_transform->position_ = Transform::Float3Add(_transform->position_, VectorToFloat3((XMVectorSet(0, -1, 0, 0) / 10) * acceleration_));
	acceleration_ += GRAVITY_ADDITION;
}

void Player::InitDeadEffect()
{
	//エフェクト情報を設定
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

void Player::InitBombEffect()
{
	bombEffectData.textureFileName = "Effects/cloudA.png";
	bombEffectData.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	bombEffectData.delay = 0;
	bombEffectData.number = 1;
	bombEffectData.lifeTime = 25;
	bombEffectData.speed = 0.05f;
	bombEffectData.speedRnd = 0.0;
	bombEffectData.size = XMFLOAT2(5,5);
	bombEffectData.scale = XMFLOAT2(1.01, 1.01);
	bombEffectData.color = XMFLOAT4(1, 0, 0, 1);

}

void Player::InitRandEffect()
{	
	//エフェクト情報を設定
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

void Player::InitPlusOneEffect()
{
	PlusOneEffectData.textureFileName = "Effects/PlusOneR.png";
	PlusOneEffectData.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	PlusOneEffectData.delay = 0;
	PlusOneEffectData.number = 1;
	PlusOneEffectData.lifeTime = 25;
	PlusOneEffectData.speed = 0.05f;
	PlusOneEffectData.speedRnd = 0.0;
	PlusOneEffectData.size = XMFLOAT2(0.75, 0.75);
	PlusOneEffectData.scale = XMFLOAT2(1.01, 1.01);
	PlusOneEffectData.color = XMFLOAT4(1, 1, 1, 1);
}


void Player::OnWoodPickup(Stage* pS)
{
	//プレイヤーの位置が１or２なら...
	if (pS->AtItem(this, 1) || pS->AtItem(this,2)) {

		//薪を1本(*5)取得する
		Global::gFireWood += 5;

		//エフェクト
		PlusOneEffectData.position = (XMFLOAT3(transform_.position_.x - 0.5, transform_.position_.y + 0.5, 0));
		VFX::Start(PlusOneEffectData);

		AudioManager::Play_WoodSound();

		//その場所の薪を消して空気に変換
		pS->SetItem(round(transform_.position_.x), round(transform_.position_.y), 0);
	}
}

const float GOAL_POINT = 285.0f;

bool Player::isGoal()
{
	return transform_.position_.x >= GOAL_POINT;
}

void Player::TerrainInteraction()
{
	//ステージ情報を取得
	Stage* pS = (Stage*)(FindObject("Stage"));

	//薪を取得する
	OnWoodPickup(pS);

	//足場が泥の時
	if (pS->AtItem(this, 2))
	{
		//※うまく行かない(検討中)
	}
	else SetSpeed(0.1f);
}

void Player::PolyDraw()
{
	//ジェット状態の時、ポリラインを描画(ジェット噴射effect)
	if (pState_->playerState_ == pState_->pJet_)pJet->Draw();
}

void Player::SetDrawTransform()
{
	//シェーダーを設定
	Direct3D::SetShader(Direct3D::SHADER_3D);
	
	//描画位置を修正(ziro_move.fbxの足元の座標が{0,0,0}の為ずらす必要がある)
	Transform t_Draw; {
		t_Draw = transform_;
		t_Draw.position_.y -= 0.5f;
		t_Draw.scale_ = { 0.1f,0.1f,0.1f };
	}
	Model::SetTransform(hModel_, t_Draw);
}
