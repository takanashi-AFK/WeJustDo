#include "Player.h"
#include "StageManager.h"
#include "Engine/Input.h"
#include "Stage.h"

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
}

void Player::ChildUpdate()
{
	{//debug-PlayerMove
	if (Input::IsKey(DIK_W))transform_.position_.y += 0.1;
	if (Input::IsKey(DIK_A))transform_.position_.x -= 0.1;
	if (Input::IsKey(DIK_S))transform_.position_.y -= 0.1;
	if (Input::IsKey(DIK_D))transform_.position_.x += 0.1;
	}

	StageRayCast();	//ステージとのあたり判定

	//更新
	//pState_->Update(this);

	// ロードしたモデルすべてにレイキャストを常に打つ
	// hit情報がtrueのモノだけをまとめたヒットリストを作成
	// ヒットリスト内の情報からdistが一番近いRayCastDataを返す
	{
		/*RayCastData under;
		ASSIGN(under.start, transform_.position_);
		ASSIGN(under.dir, VectorToFloat3(XMVectorSet(0, -1, 0, 0)));
		underRay_ = Model::GetNeardistRayData(under);*/
	}

}

void Player::ChildRelease()
{
	SAFE_DELETE(pState_);
}



//当たり判定
void Player::HitTest(RayCastData* data, const XMVECTOR& dir)
{
	data->start = transform_.position_;       //レイの発射位置  
	XMStoreFloat3(&data->dir, dir);           //レイの方向
	Model::RayCast(hGroundModel_, data);      //レイを発射                                      
}

void Player::StageRayCast()
{
	//ステージのモデル番号を取得
	hGroundModel_ = dynamic_cast<SolidObject*>((Stage*)FindObject("Stage"))->GetModelHandle();

	//右方向のあたり判定
	RayCastData rightData;{
		rightData.start = transform_.position_;					//発射位置の指定
		rightData.start.x = rightData.start.x + (PLAYER_MODEL_SIZE.x / 2);
		XMStoreFloat3(&rightData.dir, XMVectorSet(0, 1, 0, 0));	//発射方向の指定
		Model::RayCast(hGroundModel_, &rightData);				//レイを発射
	}
	if (rightData.dist <= 0.09){
		XMVECTOR length = { rightData.dist,0,0,0 };
		XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(1, 0, 0, 0) - length));
	}

	////各方向
	//RayCastData rightData;
	//RayCastData leftData;
	//RayCastData upData;
	//RayCastData downData;

	////当たってるか確認
	//HitTest(&rightData,XMVectorSet(1, 0, 0, 0));
	//HitTest(&leftData, XMVectorSet(-1, 0, 0, 0));
	//HitTest(&upData, XMVectorSet(0, 1, 0, 0));
	//HitTest(&downData, XMVectorSet(0, -1, 0, 0));

	////////////////////////////////はみ出した分下げる//////////////////////////////////////

	//if (rightData.dist <= 1){
	//	XMVECTOR dis = { rightData.dist,0,0 };
	//	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(1, 0, 0, 0) - dis));
	//}
	//if (leftData.dist <= 1){
	//	XMVECTOR dis = { -leftData.dist,0,0 };
	//	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(-1, 0, 0, 0) - dis));
	//}
	//if (upData.dist <= 1){
	//	XMVECTOR dis = { 0,upData.dist,0 };
	//	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(0, 1, 0, 0) - dis));
	//}

	//if (downData.dist >= 0.9){
	//	transform_.position_ = Transform::Float3Add(transform_.position_, VectorToFloat3((XMVectorSet(0, -1, 0, 0) / 10) * acceleration_));
	//	acceleration_ += GRAVITY_ADDITION;
	//}
	//else {
	//	pState_->ChangeState(pState_->pStanding_,this);
	//	ONE_ASSIGN(acceleration_);
	//}
}
