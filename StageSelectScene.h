#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

class StageSelectScene :
    public GameObject
{
private:
	int hPict_[4];
	int	hPict_2;
	int count;//A,D�L�[���������Ƃ��ɕς��ϐ�
	int numStage; //�X�e�[�W�̐��������ɁB
	XMFLOAT3 posX; //�J�[�\���̈ړ��͂���
	Transform CursorTransform_;

	Text* pText;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	StageSelectScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

