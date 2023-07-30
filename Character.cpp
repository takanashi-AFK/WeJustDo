#include "Character.h"
#include "Engine/Model.h"

Character::Character(GameObject* _parent,std::string _modelFilePath)
	:GameObject(_parent, "Character"),hModel_(-1),normal_(XMVectorSet(0,-1,0,0)),pStage_(nullptr), modelFilePath_(_modelFilePath), hStageModel_(0)
{
}

void Character::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load(modelFilePath_);
	assert(hModel_ >= 0);

	//�p����̏�����
	ChildInitialize();

	//�X�e�[�W���̎擾
	//pStage_ = (Stage*)FindObject("Stage");
	//hStageModel_ = pStage_->GetModelHandle();
	//if (!pStage_)return;

}

void Character::Update()
{
}

void Character::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Character::Release()
{
}

void Character::TerrainAlign()
{
}
