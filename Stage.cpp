#include "Stage.h"

//インクルード
#include <cmath>
#include "Engine/Model.h"
#include "Engine/CsvReader.h"
#include "Engine/Input.h"
#include "Engine/Global.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), StageModelList_{},ItemPlacement_{},iP_Height_(0),iP_Width_(0),hFirewood_(-1)
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
		AddStageModel(Model::Load(fileNames[i]));
	};

	//csvの情報を取得し、格納する
	CsvReader csv; {
		csv.Load("Datas/uo.csv");
		iP_Width_ = csv.GetWidth();
		iP_Height_ = csv.GetHeight();
		ItemPlacement_.resize(iP_Width_, vector<int>(iP_Height_, 0));
		for (int x = 0; x < iP_Width_; x++)
			for (int y = 0; y < iP_Height_; y++)
				ItemPlacement_[x][y] = csv.GetValue(x, ((iP_Height_ - 1) - y));
	};
	
	//アイテム(薪)モデルのロード
	hFirewood_ = Model::Load("Models/wood.fbx");

	hGoalPaul_ = Model::Load("Models/Goal_Paul.fbx");

}

void Stage::Update()
{
	//debug-SetItem
	//static int i = 0;
	/*if (Input::IsKey(DIK_L)) {
		SetItem(sin(i), i, 1);
		i++;
	}*/
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
		//Model::SetTransform(StageModelList_[m_Block], t_Block);
		//Model::Draw(StageModelList_[m_Block]);
	}
	//////////////////////////////////////////////////////////////////////
	
	//m_Firewood
	{
		//シェーダーを適用
		//SetShader(SHADER_FWOOD);

		//位置・角度・大きさ
		Transform t_Firewood; t_Firewood.SetPosition(0, 5, 0);
		static float angle; angle++;t_Firewood.SetRotateY(angle);

		//描画
		for (int x = 0; x < iP_Width_; x++)for (int y = 0; y < iP_Height_; y++) {
		t_Firewood.position_ = { (float)x,(float)y,0 };

			if (ItemPlacement_[x][y] == 1 || ItemPlacement_[x][y] == 2){
				Model::SetTransform(hFirewood_, t_Firewood);
				Model::Draw(hFirewood_);
			}
		}
	}
	//////////////////////////////////////////////////////////////////////

	//GoalPole
	{
		Transform t_GoalPole; t_GoalPole.SetPosition(285.0f, -0.5, 0);
		t_GoalPole.rotate_.y = 270;
		Model::SetTransform(hGoalPaul_, t_GoalPole);
		Model::Draw(hGoalPaul_);

	}

	//シェーダーのリセット
	SetShader(SHADER_3D);
}

void Stage::Release()
{
	StageModelList_.clear();

	for (int i = 0; i < ItemPlacement_.size(); ++i) {
		ItemPlacement_[i].clear();
	}
	ItemPlacement_.clear();
}

bool Stage::AtItem(GameObject* _obj, int _hItem) 
{
	//四捨五入
	int x = std::round(_obj->GetPosition().x);
	int y = std::round(_obj->GetPosition().y);

	//NULLチェック
	if (x < 0 || x >= iP_Width_)return false;
	if (y < 0 || y >= iP_Height_)return false;

	return ItemPlacement_[x][y] == _hItem;
	//return ItemPlacement_[_obj->GetPosition().x][_obj->GetPosition().y] == _hItem;
}

void Stage::SetItem(int x, int y, int _hItem)
{
	//NULLチェック
	if (x < 0 || x >= iP_Width_)return;
	if (y < 0 || y >= iP_Height_)return;

	ItemPlacement_[x][y] = _hItem;
}
