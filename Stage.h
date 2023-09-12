#pragma once
#include "Engine/Gameobject.h"

//インクルード
#include <vector>

//モデル番号
enum ModelName {
	m_Ground,
	m_Block,
	m_Firewood,
};

//前方宣言
class Player;

/// <summary>
/// プレイ中、ゲーム画面上に表示されるステージオブジェクト
/// </summary>
class Stage : public GameObject
{
private:
// ステージ情報 //////////////////////////////////
	vector<int> StageModelList_;
	vector<vector<int>> ItemPlacement_;
	int iP_Height_;
	int iP_Width_;

// アイテム情報 //////////////////////////////////

	int hFirewood_;	//モデル番号(ステージ情報とは異なるモノの為)

public:
	//コンストラクタ
	Stage(GameObject* parent);
	
	//継承{初期化.更新,描画,開放}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;


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
	/// <param name="x">座標x</param>
	/// <param name="y">座標y</param>
	/// <param name="_hItem">アイテム番号</param>
	void SetItem(int x, int y, int _hItem);

public:
// ゲッター・セッター ///////////////////////////////////

	//取得：ステージ情報として登録されているすべてのモデル番号
	vector<int> GetAllStageModelHandle() { return StageModelList_; }

	//追加：ステージ情報にモデル番号を加える
	void AddStageModel(int _hModel) { StageModelList_.push_back(_hModel); }

	//取得：ステージ情報として登録されている特定のモデル番号
	int GetStageModelHandle(int _hModel) { return StageModelList_[_hModel]; }
};

