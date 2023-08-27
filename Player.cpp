#include "Player.h"
#include "StageManager.h"
#include "Engine/Input.h"
#include "Stage.h"
#include "Engine/Direct3D.h"

//定数宣言
namespace {
	//重力の加算値
	static const float GRAVITY_ADDITION = 0.03f;

	
}

Player::Player(GameObject* _parent, string _modelFileName)
	:SolidObject(_parent,_modelFileName,"Player")
{
	ASSIGN(pState_,new PlayerStateManager);
}

void Player::ChildInitialize()
{
	//状態の初期化
	ASSIGN(pState_->playerState_, pState_->pStanding_);
	//pState_->Enter(this);

	PosMarker = Model::Load("Models/debugMarker.fbx");
}

void Player::ChildUpdate()
{
	{//debug-PlayerMove
	if (Input::IsKey(DIK_W))transform_.position_.y += 0.1;
	if (Input::IsKey(DIK_A))transform_.position_.x -= 0.1;
	if (Input::IsKey(DIK_S))transform_.position_.y -= 0.1;
	if (Input::IsKey(DIK_D))transform_.position_.x += 0.1;
	if (Input::IsKey(DIK_RIGHT))transform_.rotate_.y -= 1;
	if (Input::IsKey(DIK_LEFT))transform_.rotate_.y += 1;
	}

	
	//更新
	//pState_->Update(this);
	
	//ステージとのあたり判定
	StageRayCast();

	if (Input::IsKeyDown(DIK_R))transform_.position_.y = 10;;

}

void Player::ChildRelease()
{
	SAFE_DELETE(pState_);
}

void Player::ChildDraw()
{
}


void Player::StageRayCast()
{
	//ステージのモデル番号を取得
	hGroundModel_ = dynamic_cast<SolidObject*>((Stage*)FindObject("Stage"))->GetModelHandle();

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
