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
	}

	//csvの情報を取得する
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
	
	//シェーダーのリセット
	SetShader(SHADER_3D);
}

void Stage::Release()
{
}
