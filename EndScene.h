#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

/// <summary>
/// �`�[�����S��\������V�[���I�u�W�F�N�g
/// </summary>
class EndScene : public GameObject
{
private:
	int hPict_;	//�摜�ԍ�
	float scroll;
	int posi;

	Text* pText;

public:
	//�R���X�g���N�^
	EndScene(GameObject* parent);

	//�p��{�������E�X�V�E�`��E�J��}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {}
};
