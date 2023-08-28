#pragma once
#include "Engine/SolidObject.h"

//インクルード
#include "PlayerStateManager.h"
#include "Engine/Model.h"
#include "Engine/VFX.h"

//前方宣言
class Stage;

/// <summary>
/// ゲーム中、画面上に表示されるプレイヤーオブジェクト
/// </summary>
class Player : public SolidObject
{
protected:
	///// 必要な情報 ////////////////////////////////////////
	PlayerStateManager* pState_;	//Playerの状態管理

	///// あたり判定 ////////////////////////////////////////
	RayCastData underRay_;		//プレイヤーの下に伸びるレイ
	Stage*		pStage_;		//ステージクラスのポインタ
	int			hGroundModel_;	//ステージのモデル番号を入れる変数
	float		acceleration_;	//重力の加速度
	EmitterData data;
	int hFireEffectEmit;


public:
	//コンストラクタ
	Player(GameObject* _parent, string _modelFileName);

	//継承{初期化・更新・描画・開放}
	void ChildInitialize() override;
	void ChildUpdate() override;
	void ChildRelease() override;
	void ChildDraw() override;

	///// 必要な関数 //////////////////////////////////////// 

	/// <summary>
	/// プレイヤーが判定するステージのモデル番号を取得
	/// </summary>
	/// <returns>ステージのモデル番号</returns>
	int GetPlayerOnGround() { return hGroundModel_; }

	/// <summary>
	/// 状態を取得
	/// </summary>
	/// <returns>状態</returns>
	PlayerStateManager* GetState(){return pState_;};

	/// <summary>
	/// 下に伸びるレイキャスト情報を取得
	/// </summary>
	/// <returns>レイキャスト情報</returns>
	RayCastData GetUnderRay() { return underRay_; }

	/// <summary>
	/// ステージとの接触判定処理を行う
	/// </summary>
	void StageRayCast();

	/// 重力をセット
	/// </summary>
	/// <param name="acceleration">セットしたい重力の値</param>
	void SetAcceleration(const float& acceleration) { acceleration_ = acceleration; }
};
