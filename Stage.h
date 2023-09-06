#pragma once
#include "Engine/Gameobject.h"
#include <vector>

enum ModelName {
	m_Ground,
	m_Block,
	m_Firewood,
};

class Player;

/// <summary>
/// プレイ中、ゲーム画面上に表示されるステージオブジェクト
/// </summary>
class Stage : public GameObject
{
private:
	vector<int> StageModelList_;
	vector<vector<int>> ItemPlacement_;

	int hFirewood_;
	int iP_Height_;
	int iP_Width_;
public:
	//コンストラクタ
	Stage(GameObject* parent);
	
	//継承{更新・描画}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	/// <summary>
	/// ステージに登録されているすべてのモデルを取得する
	/// </summary>
	/// <returns>登録ステージ番号リスト</returns>
	vector<int> GetAllStageModelHandle() { return StageModelList_; }

	/// <summary>
	/// ステージにモデルを登録する
	/// </summary>
	/// <param name="_hModel">登録するモデル番号</param>
	void SetStageModel(int _hModel) { StageModelList_.push_back(_hModel); }

	/// <summary>
	/// ステージに登録されている特定のモデル番号を取得する
	/// </summary>
	/// <param name="_hModel">モデル</param>
	/// <returns>モデル番号</returns>
	int GetStageModelHandle(int _hModel) { return StageModelList_[_hModel]; }

	/// <summary>
	/// Objectの位置と特定のアイテムの位置が重なっていたら
	/// </summary>
	/// <param name="_obj">オブジェクトのポインタ</param>
	/// <param name="_hItem">アイテム</param>
	/// <returns>重なっていたらtrue</returns>
	bool AtItem(GameObject* _obj, int _hItem);

	/// <summary>
	/// 特定の位置のアイテムを設定する
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="_hItem"></param>
	void SetItem(int x, int y, int _hItem);
	void SetItem(float x, float y, int _hItem);




};

