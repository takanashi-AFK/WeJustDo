#include "Player.h"

//定数宣言
namespace {
	//重力の加算値
	static const float GRAVITY_ADDITION = 0.03f;

	//Playerのモデルサイズ
	static const XMFLOAT3 PLAYER_MODEL_SIZE = {1.0f,1.0f,1.0f};
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
	pState_->Enter(this);
}

void Player::ChildUpdate()
{
	//更新
	pState_->Update(this);


	// ロードしたモデルすべてにレイキャストを常に打つ
	// hit情報がtrueのモノだけをまとめたヒットリストを作成
	// ヒットリスト内の情報からdistが一番近いRayCastDataを返す
	{
		RayCastData under;
		ASSIGN(under.start, transform_.position_);
		ASSIGN(under.dir, VectorToFloat3(XMVectorSet(0, -1, 0, 0)));
		underRay_ = Model::GetNeardistRayData(under);
	}

	StageRayCast();	//ステージとのあたり判定
}

void Player::ChildRelease()
{
	SAFE_DELETE(pState_);
}

void Player::StageRayCast()
{
	//着地点との当たり判定の為一時的に保存(PlayerPosition)
	XMFLOAT3 tmpPos = transform_.position_;
	tmpPos.y += (PLAYER_MODEL_SIZE.y / 2);



	////distが0.9より小さければ
	//if (underRay_.dist <= 0.9f) {
	//	//地面に位置を合わせる
	//	transform_.position_.y = (tmpPos.y - underRay_.dist);
	//}
	//else{
	//	transform_.position_.y -= 0.03f;
	//}
}
