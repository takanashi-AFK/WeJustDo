#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage")
{
}

void Stage::Initialize()
{
	//���f���f�[�^�̃t�@�C���p�X���i�[
	string fileNames[] = {
		"Models/Stage300.fbx",
		"Models/defaultModel.fbx"
	};
	int arraySize = sizeof(fileNames) / sizeof(fileNames[0]);

	//���f���f�[�^���̃��f�������[�h���A���f���ԍ����擾
	//�X�e�[�W�ɃZ�b�g
	for (int i = 0; i < arraySize; i++) {
		SetStageModel(Model::Load(fileNames[i]));
	}

	//csv�̏����擾����
	CsvReader csv; csv.Load("Datas/Stage.csv");
	int a = csv.GetHeight();
	int b = csv.GetWidth();

	/*ItemPlacement_.resize(, vector<int>(vertical, 0));
	for (int x = 0; x < horizontal; x++)
		for (int y = 0; y < vertical; y++)
			Table_[x][y] = CsvFile_.GetValue(x, ((vertical - 1) - y));*/
}

void Stage::Update()
{
}

void Stage::Draw()
{
	//�V�F�[�_�[���Z�b�g
	using namespace Direct3D;
	SetShader(SHADER_NOSHADE);

	//m_Ground
	{
		//�ʒu�E�p�x�E�傫��
		Transform t_Ground;t_Ground.SetRotateY(180);

		//�`��
		Model::SetTransform(StageModelList_[m_Ground], t_Ground);
		Model::Draw(StageModelList_[m_Ground]);
	}
	//////////////////////////////////////////////////////////////////////

	//m_Block
	{
		//�ʒu�E�p�x�E�傫��
		Transform t_Block; t_Block.SetPosition( 5, 5, 0 );

		Model::SetRayFlag(StageModelList_[m_Block],true);

		//�`��
		Model::SetTransform(StageModelList_[m_Block], t_Block);
		Model::Draw(StageModelList_[m_Block]);
	}
	//////////////////////////////////////////////////////////////////////
	
	//�V�F�[�_�[�̃��Z�b�g
	SetShader(SHADER_3D);
}

void Stage::Release()
{
}
