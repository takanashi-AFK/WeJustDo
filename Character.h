#pragma once
#include "Engine/GameObject.h"
#include <string>

class Stage;

/// <summary>
/// 動作する3Dキャラクターオブジェクトの基底クラス
/// Player
/// </summary>
class Character : public GameObject
{
protected:
	///// -キャラクターの保持する情報- ////////////////////
	int hModel_;				//モデル番号
	std::string modelFilePath_;	//モデルファイルのパス
	XMVECTOR normal_;			//キャラクターから下方向に伸びる法線
	Stage* pStage_;				//ステージの情報
	int hStageModel_;			//ステージのモデル番号
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親オブジェクト</param>
	Character(GameObject* _parent,std::string _modelFilePath);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 開放
	/// </summary>
	void Release() override;

	/// <summary>
	/// 継承先用のUpdate
	/// </summary>
	virtual void ChildUpdate() {};

	/// <summary>
	/// 継承先用の初期化
	/// </summary>
	virtual void ChildInitialize() {};

	/// <summary>
	/// 継承先用の描画
	/// </summary>
	virtual void ChildDraw() {};

	/// <summary>
	/// 継承先用の開放
	/// </summary>
	virtual void ChildRelease() {};

	/// <summary>
	/// 地形情報に合わせた姿勢に調整
	/// </summary>
	virtual void TerrainAlign();

	/// <summary>
	/// キャラクターの法線を設定
	/// </summary>
	/// <param name="nor">法線情報</param>
	void SetNormal(const XMVECTOR& _n) { normal_ = _n; }

	/// <summary>
	/// キャラクターの法線を取得
	/// </summary>
	/// <returns>キャラクターの法線</returns>
	XMVECTOR GetNormal() { return normal_; }

	/// <summary>
	/// モデル番号を取得
	/// </summary>
	/// <returns>モデル番号</returns>
	int GetModelHandle() { return hModel_; }

};

