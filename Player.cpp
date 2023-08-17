#include "Player.h"

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

}

void Player::ChildRelease()
{
	SAFE_DELETE(pState_);
}
