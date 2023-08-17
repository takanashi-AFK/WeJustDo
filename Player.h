#pragma once
#include "Engine/SolidObject.h"
#include "PlayerStateManager.h"

/// <summary>
/// Player�̊��N���X
/// </summary>
class Player : public SolidObject
{
protected:
	///// �K�v�ȏ�� ////////////////////////////////////////
	PlayerStateManager* pState_;	//Player�̏�ԊǗ�
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
};
