#include "SolidObject.h"
#include "Model.h"

SolidObject::SolidObject(GameObject* _parent, string _modelFileName, string name)
	:GameObject(_parent,name),modelFileName_(_modelFileName),hModel_(-1)
{
	//�g�����X�t�H�[���R���|�[�l���g��ǉ�
	//ASSIGN(transform_, new Transform);
}

SolidObject::~SolidObject()
{
}

void SolidObject::Initialize()
{
	//���f���̃��[�h
	ASSIGN(hModel_, Model::Load(modelFileName_));
	assert(hModel_ >= 0);

	//�p����̏�����
	ChildInitialize();
}

void SolidObject::Update()
{
	//�p����̍X�V
	ChildUpdate();
}

void SolidObject::Draw()
{
	//�p����̕`��
	ChildDraw();

	//���f���̕`��
	Model::SetTransform(hModel_,transform_);
	Model::Draw(hModel_);

	PolyDraw();

	//�V�F�[�_�[�̃��Z�b�g
	Direct3D::SetShader(Direct3D::SHADER_3D);
}

void SolidObject::Release()
{
	//�p����̊J��
	ChildRelease();

	//�g�����X�t�H�[���R���|�[�l���g�̊J��
	//SAFE_DELETE(transform_);
}

void SolidObject::PolyDraw()
{
}
