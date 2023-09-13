#pragma once
#include "Engine/SolidObject.h"

//インクルード
#include "PlayerStateManager.h"
#include "Engine/Model.h"
#include "PolyLine.h"
#include "Engine/VFX.h"

//前方宣言
class Stage;
class FuelGauge;

//定数宣言
namespace {
	//重力の加算値
	static const float GRAVITY_ADDITION = 0.06f;

	//Playerのモデルの大きさ
	static const XMFLOAT3 PLAYER_MODEL_SIZE = { 1.0f,1.0f,1.0f };
}

/// <summary>
/// ゲーム中、画面上に表示されるプレイヤーオブジェクト
/// </summary>
class Player : public SolidObject
{
///// 必要な情報 ////////////////////////////////////////
private:
	int hDebugBox_;	//モデル番号(DebugBox)
	PolyLine* pJet;//ジェットエフェクトのポリラインデータ
	Transform currentPos_;	//プレイヤーの前フレームの位置
protected:
	PlayerStateManager*	pState_;	//Playerの状態管理
	RayCastData	downData_;			//プレイヤーの下に伸びるレイ
	Stage* pStage_;					//ステージクラスのポインタ
	FuelGauge* pGauge_;				//ゲージクラスのポインタ
	Transform cameraTrans_;			//カメラの座標
	int	hGroundModel_;				//ステージのモデル番号を入れる変数
	float acceleration_;			//重力の加速度
	bool isAddGravity_;				//重力を加えるか否か
	bool isMove_;					//動いていいいか
	float speed_;					//移動速度

	const float defCamY = 4.5f;		//カメラYのデフォルト値【〇m】
	const float defCamZ = -13.0f;	//カメラZのデフォルト値【〇m】
	const float maxCamY = 8.5f;		//カメラY座標の最大値【〇m】
	const float stageBottom = 1;	//ステージの底【〇m】（この値が大きいとカメラがだいぶ近くなります。）
	const float camZBottom = 4.5f;	//カメラZを【〇m】必ず足す　カメラを引きすぎてステージの底が見えないようにします。
	const int maxfireWood_ = 100;	//薪の燃やせる数（100％）
public:
	EmitterData  RandEffectData_;	//エフェクトデータ(着地時)
	EmitterData  DeadEffectData;	//エフェクトデータ(死亡時)
	EmitterData PlusOneEffectData;	//エフェクトデータ(薪(アイテム)取得時)
	EmitterData  ItemGetEffectData;
	EmitterData bombEffectData;
/////////////////////////////////////////////////////////

public:
	//コンストラクタ
	Player(GameObject* _parent, string _modelFileName);

	//継承{初期化・更新・描画・effect描画・SolidObject描画・開放}
	void ChildInitialize() override;
	void ChildUpdate() override;
	void ChildDraw() override;
	void PolyDraw() override;
	void SetDrawTransform() override;
	void ChildRelease() override;

	/// <summary>
	/// ステージとの接触判定処理を行う
	/// </summary>
	void StageRayCast();

	/// <summary>
	/// 重力を加える
	/// </summary>
	void AddGravity(Transform* _transform);

	/// <summary>
	/// 動いていいかどうかを返す
	/// </summary>
	/// <returns>動いて良ければtrue</returns>
	bool IsMove() { return isMove_; }

	/// <summary>
	/// 死んでいるかどうかを返す
	/// </summary>
	/// <returns>死んでいればtrue</returns>
	bool isDead() { return pState_->playerState_ == pState_->pDead_; }

	/// <summary>
	/// ゴール到達地点に到達しているかどうかを返す
	/// </summary>
	/// <returns>ゴール地点に到達していればtrue</returns>
	bool isGoal();

	/// <summary>
	/// プレイヤーと地形の相互作用を記述する関数
	/// </summary>
	void TerrainInteraction();

	/// <summary>
	/// 薪(アイテム)取得時に起きる処理を行う
	/// </summary>
	void OnWoodPickup(Stage* ps);

public:
// ゲッター・セッター //////////////////////////////
	
	//取得：プレイヤーが乗っているステージのモデル番号
	int GetPlayerOnGround() { return hGroundModel_; }

	//取得：プレイヤーの状態
	PlayerStateManager* GetState() { return pState_; };

	//設定：重力加速度
	void SetAcceleration(const float& acceleration) { acceleration_ = acceleration; }
	
	//取得：重力加速度
	float GetAccelaration() { return acceleration_; }

	//設定：重力を加えるかどうか(加えるならtrue)
	void IsAddGravity(bool _flag) { isAddGravity_ = _flag; }

	//設定：動いていいかどうか(動いていいならtrue)
	void SetIsMove(bool _flag) { isMove_ = _flag; }

	//取得：下に伸びるレイキャスト情報
	RayCastData GetDownData() { return downData_; }

	//設定：プレイヤーの速度
	void SetSpeed(float _s) { speed_ = _s; }

	//取得：プレイヤーの速度
	float GetSpeed() { return speed_; }

	//設定：薪(アイテムの所持数)
	void SetFirewoodNum(int _n) { Global::gFireWood = _n; }

// effect ///////////////////////////////////

	/// <summary>
	/// 死亡時エフェクトの初期化
	/// </summary>
	void InitDeadEffect();

	void InitBombEffect();

	/// <summary>
	/// 着地時エフェクトの初期化
	/// </summary>
	void InitRandEffect();

	/// <summary>
	/// 薪(アイテム)取得時+1の初期化
	/// </summary>
	void InitPlusOneEffect();

	/// <summary>
	/// アイテム取得時キラキラのエフェクト
	/// </summary>
	void InitGetEffect();

	//取得：死亡時エフェクトデータ
	EmitterData GetDeadEData() { return DeadEffectData; }
	
	//取得：着地時エフェクトデータ
	EmitterData GetRandEData() { return RandEffectData_; }

	//取得：JetFireのポリラインデータ
	PolyLine GetJettPData() { return *pJet; }

	/// <summary>
	/// カメラのY座標を計算します
	/// </summary>
	/// <param name="_plPos">プレイヤーのTransform</param>
	/// /// <param name="_stageBottom">地面の底面</param>
	/// <returns>positionのY座標に代入してください</returns>
	float CalcCamPositionY(Transform _plPos);

	float CalcCamPositionZ(Transform _plPos);
};
