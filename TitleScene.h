#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// �^�C�g���C���[�W��\������V�[���I�u�W�F�N�g
/// </summary>
class TitleScene : public GameObject
{
	bool increasing_;
	int opacity_;
private:
	int hPict_;	//�摜�ԍ�
	int hPict2_;//�摜�ԍ��Q
	int hPict3_;//�N���W�b�g��Pless C��UI
	int hModel_;//���f���ԍ�
public:
	//�R���X�g���N�^
	TitleScene(GameObject* parent);

	//�p��{�������E�X�V�E�`��E�J��}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override{}
};

