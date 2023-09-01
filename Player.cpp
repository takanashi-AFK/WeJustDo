#include "Player.h"

//インクルード
#include "Engine/Input.h"
#include "Stage.h"
#include "Engine/Transition.h"
#include "Engine/Debug.h"
#include "Engine/Camera.h"

//コンストラクタ
Player::Player(GameObject* _parent, string _modelFileName)
	:SolidObject(_parent,_modelFileName,"Player"),
	pState_(nullptr), underRay_(),pStage_(),hGroundModel_(0),acceleration_(0)
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
	ASSIGN(ziro, Model::Load("Models/ziro2.fbx"));

	//位置の初期化
	transform_.position_.y = 2;

	//初期状態の開始処理
	pState_->Enter(this);

	isMove_ = true;

	transform_.rotate_.y = 90;

	pLine = new PolyLine;
	pLine->Load("Effects/Fire.png");
}

//更新
void Player::ChildUpdate()
{

	PolyEmitPos = XMFLOAT3(transform_.position_.x - (PLAYER_MODEL_SIZE.x / 4), transform_.position_.y + (PLAYER_MODEL_SIZE.x / 4), transform_.position_.z);
	if (isMove_) {
		{//debug-PlayerMove
			if (Input::IsKey(DIK_UP))transform_.position_.y += 0.1;
			if (Input::IsKey(DIK_LEFT))transform_.position_.x -= 0.1;
			if (Input::IsKey(DIK_DOWN))transform_.position_.y -= 0.1;
			if (Input::IsKey(DIK_RIGHT))transform_.position_.x += 0.1;
		}
	}

	//jump状態にする
	if (Input::IsKey(DIK_SPACE)) {isJumpNow_ = true;
	}

	//jump中の処理を行う
	if (isJumpNow_) {transform_.position_.y += 0.1f;
	}

	Camera::SetPosition(transform_.position_.x + 5, 3.5f, -15.0f);
	Camera::SetTarget(transform_.position_.x + 5, 5.5f, 0.0f);

	//重力を加える
	AddGravity(&transform_);

	//ステージとのあたり判定
	StageRayCast();


	//ポリラインに現在の位置を伝える
	pLine->AddPosition(PolyEmitPos);


	//状態ごとの更新
	pState_->Update(this);
}

//開放
void Player::ChildRelease()
{
	SAFE_DELETE(pState_);
	//ポリライン解放
	pLine->Release();
}

//描画
void Player::ChildDraw()
{
	//レイのスタート位置を描画
	Transform t;
	t.position_ = RayStartPos;
	t.position_.z -= 0.5f;
	Model::SetTransform(Marker, t);
	Model::Draw(Marker);

	//着地点を描画
	Transform d;
	d.position_ = downLandingPoint;
	Model::SetTransform(Marker, d);
	Model::Draw(Marker);

	Transform up;
	up.position_ = upLandingPoint;
	Model::SetTransform(Marker, up);
	Model::Draw(Marker);

	Transform rg;
	rg.position_ = rightLandingPoint;
	Model::SetTransform(Marker, rg);
	Model::Draw(Marker);

	Transform lf;
	lf.position_ = leftLandingPoint;
	Model::SetTransform(Marker, lf);
	Model::Draw(Marker);


	Transform z;
	z.position_ = transform_.position_;
	z.position_.y -= 0.5;
	z.rotate_.y = 90.0f;
	z.scale_ = { 0.1f,0.1f,0.1f };
	Model::SetTransform(ziro, z);
	Model::Draw(ziro);

	Direct3D::SetShader(Direct3D::SHADER_UNLIT);
}


void Player::StageRayCast()
{
	//ステージのモデル番号を取得
	ASSIGN(hGroundModel_,dynamic_cast<SolidObject*>((Stage*)FindObject("Stage"))->GetModelHandle());

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
			XMVECTOR length = { -leftData.dist -(PLAYER_MODEL_SIZE.x/2),0,0};
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
			Model::RayCast(hGroundModel_,&upData);
			upLandingPoint = upData.pos;
		}
		//レイの長さが1.0以下だったら...
		if (upData.dist < (PLAYER_MODEL_SIZE.y / 2)) {
			//めり込み分、位置を戻す
			XMVECTOR length = {0, (PLAYER_MODEL_SIZE.y / 2) + upData.dist,0 };
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
			Model::RayCast(hGroundModel_,&downData);
			downLandingPoint = downData.pos;
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

void Player::PolyDraw()
{
	if (Input::IsKey(DIK_LSHIFT))
	{
		//ポリラインを描画
		pLine->Draw();
	}
}