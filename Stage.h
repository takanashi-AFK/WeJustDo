#pragma once
#include "Engine/SolidObject.h"

/// <summary>
/// �v���C���A�Q�[����ʏ�ɕ\�������X�e�[�W�I�u�W�F�N�g
/// </summary>
class Stage : public SolidObject
{
public:
	//�R���X�g���N�^
	Stage(GameObject* parent, string modelFileName);
	
	//�p��{�X�V�E�`��}
	void ChildInitialize() override;
	void ChildUpdate() override;
	void ChildDraw() override;
};

