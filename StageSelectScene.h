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
	XMFLOAT3 posX; //�J�[�\���̈ړ��͂���

	Text* pText;
	Transform a;

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
	/// <summary>
	///	�摜���ϓ��ɐݒu���܂��B
	/// </summary>
	/// <param name="_num">�摜�̖����������ɓ���܂�</param>
	/// <param name="_pos">GameObject Transform::transform_���|�C���^�œn���܂�</param>
	void CalcPosition(int _num);
};
