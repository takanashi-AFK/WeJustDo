#include "Player.h"

//インクルード
#include "Engine/Input.h"
#include "Stage.h"
#include "Engine/Transition.h"
#include "Engine/Image.h"
#include "Engine/Debug.h"
#include "Engine/Camera.h"
#include "AudioManager.h"
#include "Engine/VFX.h"
#include <cmath>

//たかなしめも
//まきエフェクト->８本レイ(Now)->駒村先生に映像の撮り直し

//コンストラクタ
Player::Player(GameObject* _parent, string _modelFileName)
	:SolidObject(_parent,_modelFileName,"Player"),
	pState_(nullptr),pStage_(),hGroundModel_(0),acceleration_(0)
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
	transform_.position_.y = 2;
	//初期状態の開始処理
	pState_->Enter(this);

	isMove_ = true;

	InitDeadEffect();
	InitRandEffect();
	InitGetEffect();

	//pDead = new PolyLine(1,50);
	//pDead->Load("Effects/Tex.png");
	pJet = new PolyLine(0.2, 10);
	pJet->Load("Effects/Fire.png");

	firewoodNum_ = 8000;

}

//更新
void Player::ChildUpdate()
{
	PolyJetEmitPos = XMFLOAT3(transform_.position_.x - (PLAYER_MODEL_SIZE.x / 4), transform_.position_.y - (PLAYER_MODEL_SIZE.x / 4), transform_.position_.z);
	pJet->AddPosition(PolyJetEmitPos);

	//重力を加える
	AddGravity(&transform_);

	//アイテムとの当たり判定
	GetFirewood();

	//状態ごとの更新
	pState_->Update(this);

	//ステージとのあたり判定
	StageRayCast();

	Camera::SetPosition(transform_.position_.x + 5, transform_.position_.y+3, -13.0f);
	Camera::SetTarget(transform_.position_.x + 5, transform_.position_.y+3, 0.0f);
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
	// ステージのモデル番号を取得
	ASSIGN(hGroundModel_, dynamic_cast<Stage*>(FindObject("Stage"))->GetStageModelHandle(m_Ground));

	// レイの方向を定義
	const XMVECTOR rayDirections[8] = {
		XMVectorSet(-1, 0, 0, 0),   // 左
		XMVectorSet(1, 0, 0, 0),    // 右
		XMVectorSet(0, 1, 0, 0),    // 上
		XMVectorSet(0, -1, 0, 0),   // 下
		XMVectorSet(-1, 1, 0, 0),   // 左上
		XMVectorSet(1, 1, 0, 0),    // 右上
		XMVectorSet(-1, -1, 0, 0),  // 左下
		XMVectorSet(1, -1, 0, 0)    // 右下
	};

	// レイキャストの結果を格納する配列
	RayCastData rayData[8];

	for (int i = 0; i < 8; ++i)
	{
		rayData[i].start = transform_.position_;

		// レイの長さを適切に設定
		if (i < 4)
		{
			if (i % 2 == 0)
			{
				rayData[i].start.x += -(PLAYER_MODEL_SIZE.x / 2);
			}
			else
			{
				rayData[i].start.x += (PLAYER_MODEL_SIZE.x / 2);
			}

			if (i < 2)
			{
				rayData[i].start.y += PLAYER_MODEL_SIZE.y;
			}
			else
			{
				rayData[i].start.y +=  -(PLAYER_MODEL_SIZE.y / 2) + 0.03;
			}
			
		}
		else
		{

			if (i % 2 == 0)
			{
				rayData[i].start.x += -(PLAYER_MODEL_SIZE.x / 2);
			}
			else
			{
				rayData[i].start.x += (PLAYER_MODEL_SIZE.x / 2);
			}

			if (i < 6)
			{
				rayData[i].start.y += PLAYER_MODEL_SIZE.y;
			}
			else
			{
				rayData[i].start.y += -(PLAYER_MODEL_SIZE.y / 2) + 0.03;
			}
		}

		rayData[i].dir = VectorToFloat3( rayDirections[i]);
		Model::RayCast(hGroundModel_, &rayData[i]);

		// レイキャスト結果に基づいて処理を行う
		if (rayData[i].dist < (PLAYER_MODEL_SIZE.x / 2) || rayData[i].dist < (PLAYER_MODEL_SIZE.y / 2))
		{

			float posA{}, posB{};
			if (i % 2 == 0) - rayData[i].dist - (PLAYER_MODEL_SIZE.x / 2);
			else 0;

			if (i < 4)0;
			else (PLAYER_MODEL_SIZE.y / 2) + rayData[i].dist;
			// めり込み分、位置を戻す
			XMVECTOR length = XMVectorSet(
				posA,
				posB,
				0,
				0
			);
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (rayDirections[i] - length));
		}
	}


	////ステージのモデル番号を取得
	//ASSIGN(hGroundModel_, dynamic_cast<Stage*>(FindObject("Stage"))->GetStageModelHandle(m_Ground));

	////左方向の当たり判定
	//{
	//	RayCastData leftData; {
	//		leftData.start = transform_.position_;
	//		RayStartPos = leftData.start;
	//		XMStoreFloat3(&leftData.dir, XMVectorSet(-1, 0, 0, 0));
	//		Model::RayCast(hGroundModel_, &leftData);
	//		leftLandingPoint = leftData.pos;
	//	}
	//	if (leftData.dist < (PLAYER_MODEL_SIZE.x / 2)) {
	//		//めり込み分、位置を戻す
	//		XMVECTOR length = { -leftData.dist - (PLAYER_MODEL_SIZE.x / 2),0,0 };
	//		XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(-1, 0, 0, 0) - length));
	//	}
	//}

	////右方向のあたり判定
	//{
	//	RayCastData rightData; {
	//		//当たっているかを確認
	//		rightData.start = transform_.position_;					//発射位置の指定
	//		XMStoreFloat3(&rightData.dir, XMVectorSet(1, 0, 0, 0));	//発射方向の指定
	//		Model::RayCast(hGroundModel_, &rightData);				//レイを発射
	//		rightLandingPoint = rightData.pos;
	//	}
	//	//レイの長さが1.0以下だったら...
	//	if (rightData.dist < (PLAYER_MODEL_SIZE.x / 2)) {
	//		//めり込み分、位置を戻す
	//		XMVECTOR length = { rightData.dist + (PLAYER_MODEL_SIZE.x / 2),0,0 };
	//		XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(1, 0, 0, 0) - length));
	//	}
	//}

	////上方向のあたり判定
	//{
	//	RayCastData upData; {
	//		//当たっているか確認
	//		upData.start = transform_.position_;
	//		XMStoreFloat3(&upData.dir, XMVectorSet(0, 1, 0, 0));
	//		Model::RayCast(hGroundModel_, &upData);
	//		upLandingPoint = upData.pos;
	//	}
	//	//レイの長さが1.0以下だったら...
	//	if (upData.dist < (PLAYER_MODEL_SIZE.y / 2)) {
	//		//めり込み分、位置を戻す
	//		XMVECTOR length = { 0, (PLAYER_MODEL_SIZE.y / 2) + upData.dist,0 };
	//		XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(0, 1, 0, 0) - length));
	//		SetAcceleration(2);
	//	}
	//}

	////StandingState,RunningStateときのみ行うからState内で処理を行う
	////下方向のあたり判定
	//{
	//	RayCastData downData; {
	//		//当たっているか確認
	//		downData.start = transform_.position_;
	//		XMStoreFloat3(&downData.dir, XMVectorSet(0, -1, 0, 0));
	//		Model::RayCast(hGroundModel_, &downData);
	//		downLandingPoint = downData.pos;
	//		downData_ = downData;
	//	}
	//	if (downData.dist < (PLAYER_MODEL_SIZE.y / 2)) {
	//		//状態を"Standing"に変更
	//		pState_->ChangeState(pState_->pStanding_, this);

	//		//jump状態を終了
	//		isJumpNow_ = false;
	//	}
	//	else
	//		isAddGravity_ = true;
	//}

	// その他の処理を続行
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

void Player::InitGetEffect()
{
	ItemGetEffectData.textureFileName = "Effects/kira.png";
	ItemGetEffectData.position = XMFLOAT3(transform_.position_.x, transform_.position_.y - 0.2, 0);
	ItemGetEffectData.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	ItemGetEffectData.delay = 0;
	ItemGetEffectData.number = 1;
	ItemGetEffectData.lifeTime = 40;
	ItemGetEffectData.speed = 0.01f;
	ItemGetEffectData.speedRnd = 0.0;
	ItemGetEffectData.size = XMFLOAT2(1, 0.5);
	ItemGetEffectData.scale = XMFLOAT2(1.01, 1.01);
	ItemGetEffectData.color = XMFLOAT4(1, 1, 1, 1);
	ItemGetEffectData.deltaColor = XMFLOAT4(0, 0, 0, -0.1);
}



EmitterData Player::GetDeadEData()
{
	return DeadEffectData;
}

EmitterData Player::GetRandEData()
{
	return RandEffectData_;
}

EmitterData Player::GetGetEData()
{
	return ItemGetEffectData;
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
	if (pS->AtItem(this, 1)) {

		//エフェクト

		firewoodNum_+= 10;//ここを後々firewoodNum_++にしたい
		//エフェクト

		pS->SetItem(transform_.position_.x, transform_.position_.y, 0);
		ItemGetEffectData.position = transform_.position_;
		VFX::Start(ItemGetEffectData);
	}
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
