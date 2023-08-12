#include "yuka.h"
#include "Engine/Model.h"
//�R���X�g���N�^
yuka::yuka(GameObject* parent)
	: GameObject(parent, "yuka")
{
}

//������
void yuka::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("yuka.fbx");
	assert(hModel_ >= 0);
	transform_.position_.y = -2.0f;
}

//�X�V
void yuka::Update()
{
}

//�`��
void yuka::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void yuka::Release()
{
}
