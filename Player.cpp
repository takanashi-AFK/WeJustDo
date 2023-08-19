#include "Player.h"
#include "StageManager.h"
#include "Engine/Input.h"
#include "Stage.h"

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
	}

	{//debug-PlayerJump

		//PlayerObject���牺�����ɑ΂��ĐL�т钼����p��
		RayCastData data;
		data.start = transform_.position_;

		XMFLOAT3 playerNormal = { 0.0f,-1.0f,0.0f };
		//XMVECTOR wPlayerNormal = XMVector3Transform(XMLoadFloat3(&playerNormal), GetWorldMatrix());

		data.dir = { 0.0f,-1.0f,0.0f };
		Model::RayCast((*(Stage*)FindObject("Stage")).GetModelHandle(), &data); //���C�𔭎�

		if (data.hit) {
			//�I�u�W�F�N�g�̉��ɃI�u�W�F�N�g�����݂���ꍇ�̏���

			//�W�����v�̏���
			if (Input::IsKeyDown(DIK_SPACE) && isJumping == false)
			{
				//�y�W�����v�̏�����̉����x���Z�Z�z
				moveY += 0.3f;

				//�y�W�����v���Ă���t���O�𗧂Ă�z
				isJumping = true;
			}

			//�y�n�ɑ������Ă��Ȃ����z
			else if (isJumping == true)
			{
				//�y�d�͉����x���Z�Z�z
				moveY -= 0.02f;
				transform_.rotate_.z = 0.0f;

				//�y�������������̉����x�����l�Z�Z�ȉ��ł����
				if (moveY <= -0.3f)
				{
					//�y�������̉����x���Z�Z�ɌŒ肷��z
					moveY = -0.3f;
				}
			}

			//�y�v���C���[�ƒn�ʂ̈ʒu����苗���Z�Z�ɂȂ�����z
			if ((data.dist <= 0.4f))
			{
				//�y�㉺�����̉����x�͂O�B�z
				moveY = 0.0f;

				//�y�n�ɑ������Ă���z
				isJumping = false;
			}

			//�y�n�ɑ������Ă���Ƃ��z
			if (isJumping == false)
			{
				//�y���C�̓������������Ɏ��g��u���z
				transform_.position_.y -= (data.dist - 0.5f);
			}

			//�y�v���C���[��Y���W�̈ړ��z
			transform_.position_.y += moveY;


			//�Q�̃x�N�g��������ς��擾����
			XMVECTOR dot = XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&playerNormal)), XMVector3Normalize(data.normal));

			//�p�x(Radian)���v�Z����(�������̊p�x���擾)
			float angle = acos(XMVectorGetX(dot));

			//���W�A���p����f�B�O���[�p�ɕϊ�����
			Deg = XMConvertToDegrees(angle);

			//�O�ς��畉�̒l�����̒l���𔻒f����
			if (XMVectorGetZ(XMVector3Cross(data.normal, XMLoadFloat3(&playerNormal))) < 0)
			{
				Deg *= -1;//���̒l�̏ꍇ��-1��������
			}

			//�p�x���A����]������
			transform_.rotate_.z = (Deg);
		}
		else {
			//�I�u�W�F�N�g�̑����ɃI�u�W�F�N�g�����݂��Ȃ��ꍇ�̏���
			transform_.rotate_.z = 0;

			moveY -= 0.02f;
			transform_.position_.y += moveY;
		}
	}

	//�X�V
	//pState_->Update(this);

	// ���[�h�������f�����ׂĂɃ��C�L���X�g����ɑł�
	// hit���true�̃��m�������܂Ƃ߂��q�b�g���X�g���쐬
	// �q�b�g���X�g���̏�񂩂�dist����ԋ߂�RayCastData��Ԃ�
	{
		/*RayCastData under;
		ASSIGN(under.start, transform_.position_);
		ASSIGN(under.dir, VectorToFloat3(XMVectorSet(0, -1, 0, 0)));
		underRay_ = Model::GetNeardistRayData(under);*/
	}
	//StageRayCast();	//�X�e�[�W�Ƃ̂����蔻��

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
	//�X�e�[�W�̃��f���ԍ����擾
	hGroundModel_ = dynamic_cast<SolidObject*>((Stage*)FindObject("Stage"))->GetModelHandle();

	//�E�����̂����蔻��
	RayCastData rightData;{
		rightData.start = transform_.position_;					//���ˈʒu�̎w��
		rightData.start.x = rightData.start.x + (PLAYER_MODEL_SIZE.x / 2);
		XMStoreFloat3(&rightData.dir, XMVectorSet(0, 1, 0, 0));	//���˕����̎w��
		Model::RayCast(hGroundModel_, &rightData);				//���C�𔭎�
	}
	if (rightData.dist <= 0.9f){
		XMVECTOR length = { rightData.dist,0,0,0 };
		XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(1, 0, 0, 0) - length));
	}

	////�e����
	//RayCastData rightData;
	//RayCastData leftData;
	//RayCastData upData;
	//RayCastData downData;

	////�������Ă邩�m�F
	//HitTest(&rightData,XMVectorSet(1, 0, 0, 0));
	//HitTest(&leftData, XMVectorSet(-1, 0, 0, 0));
	//HitTest(&upData, XMVectorSet(0, 1, 0, 0));
	//HitTest(&downData, XMVectorSet(0, -1, 0, 0));

	////////////////////////////////�͂ݏo������������//////////////////////////////////////

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
