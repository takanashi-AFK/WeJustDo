#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// �`�[�����S��\������V�[���I�u�W�F�N�g
/// </summary>
class SplashScene : public GameObject
{
private:
	int hPict_;	//�摜�ԍ�
public:
	//�R���X�g���N�^
	SplashScene(GameObject* parent);
	
	//�p��{�������E�X�V�E�`��E�J��}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override{}
};

