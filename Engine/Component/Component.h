#pragma once

//�O���錾
class GameObject;

/// <summary>
/// �R���|�[�l���g���N���X
/// </summary>
class Component
{
public:
    GameObject* parent_;//�e�I�u�W�F�N�g
public:
    //�R���X�g���N�^
    Component() :parent_(nullptr) {}

    //�f�X�g���N�^
    virtual ~Component() {}

    //�J�n(�ŏ��̈�񂾂��Ă΂��)
    virtual void Start() {}

    //�X�V
    virtual void Update() {}

    //�`��
    virtual void Draw() {}
};