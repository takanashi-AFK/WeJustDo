#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

/// <summary>
/// �`�[�����S��\������V�[���I�u�W�F�N�g
/// </summary>
class StaffRollScene : public GameObject
{
private:
	int hPict_;	//�摜�ԍ�
	float scroll = -7.9f;
	int posi;

	Text* pText;

public:
	//�R���X�g���N�^
	StaffRollScene(GameObject* parent);

	//�p��{�������E�X�V�E�`��E�J��}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {}
};