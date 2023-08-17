#include "Player.h"

Player::Player(GameObject* _parent, string _modelFileName)
	:SolidObject(_parent,_modelFileName,"Player")
{
	ASSIGN(pState_,new PlayerStateManager);
}

void Player::ChildInitialize()
{
	//ó‘Ô‚Ì‰Šú‰»
	ASSIGN(pState_->playerState_, pState_->pStanding_);
	pState_->Enter(this);
}

void Player::ChildUpdate()
{
	//XV
	pState_->Update(this);
}

void Player::ChildRelease()
{
	SAFE_DELETE(pState_);
}
