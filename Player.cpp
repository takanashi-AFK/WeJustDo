#include "Player.h"

//インクルード
#include "Engine/Input.h"
#include "Stage.h"
#include "Engine/Transition.h"
#include "Engine/Camera.h"
//定数宣言
namespace {
	//重力の加算値
	static const float GRAVITY_ADDITION = 0.03f;

	//Playerのモデルの大きさ
	static const XMFLOAT3 PLAYER_MODEL_SIZE = { 1.0f,1.0f,1.0f };
}

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

	//初期状態の開始処理
	pState_->Enter(this);
	transform_.scale_ = { 0.1f,0.1f, 0.1f };
	transform_.rotate_.y = 90;

	pLine = new PolyLine;
	pLine->Load("Effects/Fire.png");



	data.textureFileName = "Effects/cloudA.png";
	data.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	data.delay = 5;
	data.number = 1;
	data.direction = XMFLOAT3(-1, 0, 0);
	data.directionRnd = XMFLOAT3(0, 0, 0);
	data.rotate = XMFLOAT3(45, 0, 0);
	data.speed = 0.01f;
	data.speedRnd = 0.0;
	data.size = XMFLOAT2(0.3, 0.3);
	data.sizeRnd = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(1.01, 1.01);
	data.color = XMFLOAT4(1, 1, 0, 1);
	data.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);
}

//更新
void Player::ChildUpdate()
{

	PolyEmitPos = XMFLOAT3(transform_.position_.x - (PLAYER_MODEL_SIZE.x /4), transform_.position_.y + (PLAYER_MODEL_SIZE.x / 4), transform_.position_.z);
	if (!Transition::IsActive()) {
		{//debug-PlayerMove
			if (Input::IsKey(DIK_W))transform_.position_.y += 0.1;
			if (Input::IsKey(DIK_A)) { transform_.position_.x -= 0.1; transform_.rotate_.y = -90; PolyEmitPos.x = PolyEmitPos.x + 0.5; }
			if (Input::IsKey(DIK_S))transform_.position_.y -= 0.1;
			if (Input::IsKey(DIK_D)){transform_.position_.x += 0.1; transform_.rotate_.y = 90; }
			if (Input::IsKey(DIK_RIGHT))transform_.rotate_.y -= 1;
			if (Input::IsKey(DIK_LEFT))transform_.rotate_.y += 1;
		}
	}

	Camera::SetPosition(transform_.position_.x + 5, 3.5f, -15.0f);
	Camera::SetTarget(transform_.position_.x + 5, 5.5f, 0.0f);



	
	//ポリラインに現在の位置を伝える
	pLine->AddPosition(PolyEmitPos);


	//状態ごとの更新
	//pState_->Update(this);
	
	//ステージとのあたり判定
	StageRayCast();
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

}

void Player::PolyDraw()
{
	if (Input::IsKey(DIK_LSHIFT))
	{
		//ポリラインを描画
		pLine->Draw();
	}
}

void Player::StageRayCast()
{
	//ステージのモデル番号を取得
	ASSIGN(hGroundModel_,dynamic_cast<SolidObject*>((Stage*)FindObject("Stage"))->GetModelHandle());

	//左方向の当たり判定
	{
		//RayCastData leftData; {
		//	//当たっているか確認
		//	leftData.start = transform_.position_;
		//	leftData.start.x = transform_.position_.x + (float)(PLAYER_MODEL_SIZE.x / 2);
		//	XMStoreFloat3(&leftData.dir, XMVectorSet(-1, 0, 0, 0));
		//	Model::RayCast(hGroundModel_, &leftData);
		//}
		////レイの長さが1.0以下だったら...
		//if (leftData.dist <= 1.0f) {
		//	//めり込み分、位置を戻す
		//	XMVECTOR length = { -leftData.dist,0,0 };
		//	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(-1, 0, 0, 0) - length));
		//}
	}

	//右方向のあたり判定
	{
		//RayCastData rightData; {
		//	//当たっているかを確認
		//	rightData.start = transform_.position_;					//発射位置の指定
		//	rightData.start.x = transform_.position_.x - (PLAYER_MODEL_SIZE.x / 2);
		//	XMStoreFloat3(&rightData.dir, XMVectorSet(1, 0, 0, 0));	//発射方向の指定
		//	Model::RayCast(hGroundModel_, &rightData);				//レイを発射
		//}
		////レイの長さが1.0以下だったら...
		//if (rightData.dist <= 1.0f) {
		//	//めり込み分、位置を戻す
		//	XMVECTOR length = { rightData.dist,0,0 };
		//	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(1, 0, 0, 0) - length));
		//}
	}

	//上方向のあたり判定
	{
		//RayCastData upData; {
		//	//当たっているか確認
		//	upData.start = transform_.position_;
		//	upData.start.y = transform_.position_.y + (float)(PLAYER_MODEL_SIZE.y / 2);
		//	XMStoreFloat3(&upData.dir, XMVectorSet(0, 1, 0, 0));
		//	Model::RayCast(hGroundModel_,&upData);
		//}
		////レイの長さが1.0以下だったら...
		//if (upData.dist <= 1.0f) {
		//	//めり込み分、位置を戻す
		//	XMVECTOR length = {0, upData.dist,0 };
		//	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(0, 1, 0, 0) - length));
		//}
	}

	//下方向のあたり判定
	{
		//RayCastData downData; {
		//	//当たっているか確認
		//	downData.start = transform_.position_;
		//	downData.start.y = transform_.position_.y -(PLAYER_MODEL_SIZE.y / 2.0f);
		//	XMStoreFloat3(&downData.dir, XMVectorSet(0, -1, 0, 0));
		//	Model::RayCast(hGroundModel_,&downData);
		//}
		//if (downData.dist <= 1.0f) {
		//	//めり込み分、位置を戻す
		//	XMVECTOR length = { 0,-downData.dist,0 };
		//	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(0, -1, 0, 0) - length));
		//}

		//transform_.position_.y -= 0.1;


		////レイの長さが○〇の時(着地点とプレイヤーの足元の位置の距離の長さがn以上の時)
		//if (downData.dist > 1.0f) {
		//	//重力を下方向に加える
		//	transform_.position_.y -= 0.03;
		//}
		//else {
		//	//重力を加えずに、着地点とプレイヤーの足元の位置を合わせる
		//	transform_.position_.y = transform_.position_.y - (downData.dist + (PLAYER_MODEL_SIZE.y /2.0f));
		//}
	}
}
