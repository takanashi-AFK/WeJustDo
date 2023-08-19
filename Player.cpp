#include "Player.h"
#include "StageManager.h"

//�萔�錾
namespace {
	//�d�͂̉��Z�l
	static const float GRAVITY_ADDITION = 0.03f;

	
}

Player::Player(GameObject* _parent, string _modelFileName)
	:SolidObject(_parent,_modelFileName,"Player")
{
	ASSIGN(pState_,new PlayerStateManager);
}

void Player::ChildInitialize()
{
	//��Ԃ̏�����
	ASSIGN(pState_->playerState_, pState_->pStanding_);
	pState_->Enter(this);
}

void Player::ChildUpdate()
{
	//�X�V
	pState_->Update(this);

	// ���[�h�������f�����ׂĂɃ��C�L���X�g����ɑł�
	// hit���true�̃��m�������܂Ƃ߂��q�b�g���X�g���쐬
	// �q�b�g���X�g���̏�񂩂�dist����ԋ߂�RayCastData��Ԃ�
	{
		RayCastData under;
		ASSIGN(under.start, transform_.position_);
		ASSIGN(under.dir, VectorToFloat3(XMVectorSet(0, -1, 0, 0)));
		underRay_ = Model::GetNeardistRayData(under);
	}

	StageRayCast();	//�X�e�[�W�Ƃ̂����蔻��
}

void Player::ChildRelease()
{
	SAFE_DELETE(pState_);
}



//�����蔻��
void Player::HitTest(RayCastData* data, const XMVECTOR& dir)
{
	data->start = transform_.position_;       //���C�̔��ˈʒu  
	XMStoreFloat3(&data->dir, dir);           //���C�̕���
	Model::RayCast(hGroundModel_, data);      //���C�𔭎�                                      
}

void Player::StageRayCast()
{
	//�e����
	RayCastData rightData;
	RayCastData leftData;
	RayCastData upData;
	RayCastData downData;

	//�������Ă邩�m�F
	HitTest(&rightData,XMVectorSet(1, 0, 0, 0));
	HitTest(&leftData, XMVectorSet(-1, 0, 0, 0));
	HitTest(&upData, XMVectorSet(0, 1, 0, 0));
	HitTest(&downData, XMVectorSet(0, -1, 0, 0));

	//////////////////////////////�͂ݏo������������//////////////////////////////////////

	if (rightData.dist <= 1){
		XMVECTOR dis = { rightData.dist,0,0 };
		XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(1, 0, 0, 0) - dis));
	}
	if (leftData.dist <= 1){
		XMVECTOR dis = { -leftData.dist,0,0 };
		XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(-1, 0, 0, 0) - dis));
	}
	if (upData.dist <= 1){
		XMVECTOR dis = { 0,upData.dist,0 };
		XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(0, 1, 0, 0) - dis));
	}

	if (downData.dist >= 0.9){
		transform_.position_ = Transform::Float3Add(transform_.position_, VectorToFloat3((XMVectorSet(0, -1, 0, 0) / 10) * acceleration_));
		acceleration_ += GRAVITY_ADDITION;
	}
	else {
		pState_->ChangeState(pState_->pStanding_,this);
		ONE_ASSIGN(acceleration_);
	}
}
