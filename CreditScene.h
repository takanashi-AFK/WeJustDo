#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// �Q�[���v���C��ʂ�\������V�[���I�u�W�F�N�g
/// </summary>
class CreditScene : public GameObject
{
private:
	int hPict_;	//�摜�ԍ�
public:
	//�R���X�g���N�^
	CreditScene(GameObject* parent);

	//�p��{�������E�X�V�E�`��E�J��}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};
