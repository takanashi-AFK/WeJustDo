#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage")
{
}

void Stage::Initialize()
{
	//モデルデータのファイルパスを格納
	string fileNames[] = {
		"Models/Stage300.fbx",
		"Models/defaultModel.fbx"
	};
	int arraySize = sizeof(fileNames) / sizeof(fileNames[0]);

	//モデルデータ分のモデルをロードし、モデル番号を取得
	//ステージにセット
	for (int i = 0; i < arraySize; i++) {
		SetStageModel(Model::Load(fileNames[i]));
	};
	hFirewood_ = Model::Load("Models/wood.fbx");

	//csvの情報を取得する
	CsvReader csv; {
		csv.Load("Datas/Stage.csv");
		ItemPlacement_.resize(csv.GetWidth(), vector<int>(csv.GetHeight(), 0));
		for (int x = 0; x < csv.GetWidth(); x++)
			for (int y = 0; y < csv.GetHeight(); y++)
				ItemPlacement_[x][y] = csv.GetValue(x, ((csv.GetHeight() - 1) - y));
	};
}

void Stage::Update()
{
}

void Stage::Draw()
{
	//シェーダーをセット
	using namespace Direct3D;
	SetShader(SHADER_NOSHADE);

	//m_Ground
	{
		//位置・角度・大きさ
		Transform t_Ground;t_Ground.SetRotateY(180);

		//描画
		Model::SetTransform(StageModelList_[m_Ground], t_Ground);
		Model::Draw(StageModelList_[m_Ground]);
	}
	//////////////////////////////////////////////////////////////////////

	//m_Block
	{
		//位置・角度・大きさ
		Transform t_Block; t_Block.SetPosition( 5, 5, 0 );

		Model::SetRayFlag(StageModelList_[m_Block],true);

		//描画
		Model::SetTransform(StageModelList_[m_Block], t_Block);
		Model::Draw(StageModelList_[m_Block]);
	}
	//////////////////////////////////////////////////////////////////////
	
	//m_Firewood
	{
		//位置・角度・大きさ
		Transform t_Firewood; t_Firewood.SetPosition(0, 5, 0);
		static float angle; angle++;t_Firewood.SetRotateY(angle);

		//描画
		Model::SetTransform(hFirewood_, t_Firewood);
		Model::Draw(hFirewood_);
	}
	//////////////////////////////////////////////////////////////////////

	//シェーダーのリセット
	SetShader(SHADER_3D);
}

void Stage::Release()
{
}
