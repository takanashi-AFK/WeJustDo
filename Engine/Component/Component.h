#pragma once

//�O���錾
class GameObject;

/// <summary>
/// �R���|�[�l���g���N���X
/// </summary>
class Component
{
public:
	GameObject* parent;	//�e�I�u�W�F�N�g
public:
	//�R���X�g���N�^
	Component():parent(nullptr){}

    //�f�X�g���N�^
    virtual ~Component() {}

    //������(�ŏ��̈�񂾂��Ă΂��)
    virtual void Initialize() {}

    //�X�V
    virtual void Update() {}

    //�`��
    virtual void Draw() {}
};