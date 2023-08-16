#include "asiba.h"
#include "Engine/Model.h"
//�R���X�g���N�^
asiba::asiba(GameObject* parent)
	: GameObject(parent, "asiba")
{
}

//������
void asiba::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("asiba.fbx");
	assert(hModel_ >= 0);

	transform_.position_.y = 3.0f;
	transform_.position_.x = 7.0f;
}

//�X�V
void asiba::Update()
{
}

//�`��
void asiba::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void asiba::Release()
{
}
