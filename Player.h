#pragma once
#include "Engine/SolidObject.h"
#include "PlayerStateManager.h"
#include "Engine/Model.h"
/// <summary>
/// Player�̊��N���X
/// </summary>
class Player : public SolidObject
{
protected:
	///// �K�v�ȏ�� ////////////////////////////////////////
	PlayerStateManager* pState_;	//Player�̏�ԊǗ�

	RayCastData underRay_;	//�v���C���[�̉��ɐL�т郌�C
public:
	//�R���X�g���N�^
	Player(GameObject* _parent, string _modelFileName);

	//�p��{�������E�X�V�E�J��}
	void ChildInitialize() override;
	void ChildUpdate() override;
	void ChildRelease() override;

	///// �K�v�Ȋ֐� //////////////////////////////////////// 

	/// <summary>
	/// ��Ԃ��擾
	/// </summary>
	/// <returns>���</returns>
	PlayerStateManager* GetState(){return pState_;};

	/// <summary>
	/// ���ɐL�т郌�C�L���X�g�����擾
	/// </summary>
	/// <returns>���C�L���X�g���</returns>
	RayCastData GetUnderRay() { return underRay_; }

	/// <summary>
	/// �X�e�[�W�Ƃ̐ڐG���菈�����s��
	/// </summary>
	void StageRayCast();
};
