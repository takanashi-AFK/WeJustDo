#pragma once
#include "Engine/GameObject.h"

enum {
	CommonButtonBack,
	CommonButtonBackDisable,
	FoodButtonGive,
	FoodButtonGiveDisable,
	ImageNum
};

class Button : public GameObject
{
	int hPict_[ImageNum];
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Button(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

