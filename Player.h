#pragma once
#include "Engine/SolidObject.h"

//�C���N���[�h
#include "PlayerStateManager.h"
#include "Engine/Model.h"
#include "Engine/VFX.h"

//�O���錾
class Stage;

/// <summary>
/// �Q�[�����A��ʏ�ɕ\�������v���C���[�I�u�W�F�N�g
/// </summary>
class Player : public SolidObject
{
protected:
	///// �K�v�ȏ�� ////////////////////////////////////////
	PlayerStateManager* pState_;	//Player�̏�ԊǗ�

	///// �����蔻�� ////////////////////////////////////////
	RayCastData underRay_;		//�v���C���[�̉��ɐL�т郌�C
	Stage*		pStage_;		//�X�e�[�W�N���X�̃|�C���^
	int			hGroundModel_;	//�X�e�[�W�̃��f���ԍ�������ϐ�
	float		acceleration_;	//�d�͂̉����x
	EmitterData data;
	int hFireEffectEmit;


public:
	//�R���X�g���N�^
	Player(GameObject* _parent, string _modelFileName);

	//�p��{�������E�X�V�E�`��E�J��}
	void ChildInitialize() override;
	void ChildUpdate() override;
	void ChildRelease() override;
	void ChildDraw() override;

	///// �K�v�Ȋ֐� //////////////////////////////////////// 

	/// <summary>
	/// �v���C���[�����肷��X�e�[�W�̃��f���ԍ����擾
	/// </summary>
	/// <returns>�X�e�[�W�̃��f���ԍ�</returns>
	int GetPlayerOnGround() { return hGroundModel_; }

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

	/// �d�͂��Z�b�g
	/// </summary>
	/// <param name="acceleration">�Z�b�g�������d�͂̒l</param>
	void SetAcceleration(const float& acceleration) { acceleration_ = acceleration; }
};
