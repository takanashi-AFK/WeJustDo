#include "Player.h"

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

}

void Player::ChildRelease()
{
	SAFE_DELETE(pState_);
}
