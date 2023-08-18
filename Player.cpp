#include "Player.h"

//�萔�錾
namespace {
	//�d�͂̉��Z�l
	static const float GRAVITY_ADDITION = 0.03f;

	//Player�̃��f���T�C�Y
	static const XMFLOAT3 PLAYER_MODEL_SIZE = {1.0f,1.0f,1.0f};
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

void Player::StageRayCast()
{
	//���n�_�Ƃ̓����蔻��̈׈ꎞ�I�ɕۑ�(PlayerPosition)
	XMFLOAT3 tmpPos = transform_.position_;
	tmpPos.y += (PLAYER_MODEL_SIZE.y / 2);



	////dist��0.9��菬�������
	//if (underRay_.dist <= 0.9f) {
	//	//�n�ʂɈʒu�����킹��
	//	transform_.position_.y = (tmpPos.y - underRay_.dist);
	//}
	//else{
	//	transform_.position_.y -= 0.03f;
	//}
}
