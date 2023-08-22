#include "Player.h"
#include "StageManager.h"
#include "Engine/Input.h"
#include "Stage.h"
#include "Engine/Direct3D.h"

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
	//pState_->Enter(this);


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

	
	//�X�V
	pState_->Update(this);
	StageRayCast();	//�X�e�[�W�Ƃ̂����蔻��

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
	//�X�e�[�W�̃��f���ԍ����擾
	hGroundModel_ = dynamic_cast<SolidObject*>((Stage*)FindObject("Stage"))->GetModelHandle();

	//�E�����̂����蔻��
	{
		RayCastData rightData; {
			//�������Ă��邩���m�F
			rightData.start = transform_.position_;					//���ˈʒu�̎w��
			rightData.start.x = transform_.position_.x - (PLAYER_MODEL_SIZE.x / 2);
			XMStoreFloat3(&rightData.dir, XMVectorSet(1, 0, 0, 0));	//���˕����̎w��
			Model::RayCast(hGroundModel_, &rightData);				//���C�𔭎�
		}
		//���C�̒�����1.0�ȉ���������...
		if (rightData.dist <= 1.0f) {
			//�߂荞�ݕ��A�ʒu��߂�
			XMVECTOR length = { rightData.dist,0,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(1, 0, 0, 0) - length));
		}
	}

	//�������̓����蔻��
	{
		RayCastData leftData; {
			//�������Ă��邩�m�F
			leftData.start = transform_.position_;
			leftData.start.x = transform_.position_.x - (float)(PLAYER_MODEL_SIZE.x / 2);
			XMStoreFloat3(&leftData.dir, XMVectorSet(-1, 0, 0, 0));
			Model::RayCast(hGroundModel_, &leftData);
		}
		//���C�̒�����1.0�ȉ���������...
		if (leftData.dist <= 1.0f) {
			//�߂荞�ݕ��A�ʒu��߂�
			XMVECTOR length = { -leftData.dist,0,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(-1, 0, 0, 0) - length));
		}
	}

	//������̂����蔻��
	{
		RayCastData upData; {
			//�������Ă��邩�m�F
			upData.start = transform_.position_;
			upData.start.y = transform_.position_.y + (float)(PLAYER_MODEL_SIZE.y / 2);
			XMStoreFloat3(&upData.dir, XMVectorSet(0, 1, 0, 0));
			Model::RayCast(hGroundModel_,&upData);
		}
		//���C�̒�����1.0�ȉ���������...
		if (upData.dist <= 1.0f) {
			//�߂荞�ݕ��A�ʒu��߂�
			XMVECTOR length = {0, upData.dist,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(0, 1, 0, 0) - length));
		}
	}

	//�������̂����蔻��
	{
		RayCastData downData; {
			//�������Ă��邩�m�F
			downData.start = transform_.position_;
			downData.start.y = transform_.position_.y - (float)(PLAYER_MODEL_SIZE.y / 2);
			XMStoreFloat3(&downData.dir, XMVectorSet(0, -1, 0, 0));
			Model::RayCast(hGroundModel_,&downData);
		}
		//���C�̒�����1.0�ȏゾ������...
		if (downData.dist >= 1.0f) {
			//�ʒu���d�͕�
			//transform_.position_.y -= 0.03f;

			transform_.position_ = Transform::Float3Add(transform_.position_, VectorToFloat3((XMVectorSet(0, -1, 0, 0) / 10) * acceleration_));
			acceleration_ += GRAVITY_ADDITION;
		}
		else {
			pState_->ChangeState(pState_->pStanding_, this);
			ONE_ASSIGN(acceleration_);
		}
	}
}
