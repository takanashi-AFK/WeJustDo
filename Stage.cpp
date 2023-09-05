#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"
#include "Engine/Input.h"
#include "Engine/Global.h"

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
	};
	hFirewood_ = Model::Load("Models/wood.fbx");

	//csv�̏����擾����
	CsvReader csv; {
		csv.Load("Datas/Stage.csv");
		iP_Width_ = csv.GetWidth();
		iP_Height_ = csv.GetHeight();
		ItemPlacement_.resize(iP_Width_, vector<int>(iP_Height_, 0));
		for (int x = 0; x < iP_Width_; x++)
			for (int y = 0; y < iP_Height_; y++)
				ItemPlacement_[x][y] = csv.GetValue(x, ((iP_Height_ - 1) - y));
	};
	
}

void Stage::Update()
{
	static int i = 0;
	if (Input::IsKey(DIK_L)) {
		SetItem(sin(i), i, 1);
		i++;
	}
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
	
	//m_Firewood
	{
		//�ʒu�E�p�x�E�傫��
		Transform t_Firewood; t_Firewood.SetPosition(0, 5, 0);
		static float angle; angle++;t_Firewood.SetRotateY(angle);

		//�`��
		for (int x = 0; x < iP_Width_; x++)for (int y = 0; y < iP_Height_; y++) {
		t_Firewood.position_ = { (float)x,(float)y-1,0 };

			if (ItemPlacement_[x][y] == 0){
				Model::SetTransform(hFirewood_, t_Firewood);
				Model::Draw(hFirewood_);
			}
		}
	}
	//////////////////////////////////////////////////////////////////////

	//�V�F�[�_�[�̃��Z�b�g
	SetShader(SHADER_3D);
}

void Stage::Release()
{
}

bool Stage::AtItem(GameObject* _obj, int _hItem) {
	
	return ItemPlacement_[_obj->GetPosition().x][_obj->GetPosition().y] == _hItem;
}

void Stage::SetItem(int x, int y, int _hItem)
{
	//NullCheck
	NULLCHECK_ARRAY(x, iP_Width_);
	NULLCHECK_ARRAY(y, iP_Height_);
	//if (x < 0 || x >= iP_Width_)return;
	//if (y < 0 || y >= iP_Height_)return;

	ItemPlacement_[x][y] = _hItem;
}
