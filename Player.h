#pragma once
#include "Engine/SolidObject.h"

//インクルード
#include "PlayerStateManager.h"
#include "Engine/Model.h"
#include "PolyLine.h"
#include "Engine/VFX.h"

//前方宣言
class Stage;

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
private:
	//debug
	int Marker;
	int DeadEffHandle;
	XMFLOAT3 RayStartPos;
	XMFLOAT3 downLandingPoint;
	XMFLOAT3 upLandingPoint;
	XMFLOAT3 rightLandingPoint;
	XMFLOAT3 leftLandingPoint;
	XMFLOAT3 PolyJetEmitPos;
	
	PolyLine* pJet;
	
	//ziro2
	int hBox_;
	int firewoodNum_;
protected:
///// 必要な情報 ////////////////////////////////////////
	PlayerStateManager*	pState_;	//Playerの状態管理
	RayCastData	downData_;			//プレイヤーの下に伸びるレイ
	Stage* pStage_;					//ステージクラスのポインタ
	int	hGroundModel_;				//ステージのモデル番号を入れる変数
	float acceleration_;			//重力の加速度
	bool isAddGravity_;				//重力を加えるか否か
	bool isJumpNow_;				//ジャンプ中か否か
	bool isMove_;					//動いていいいか
	bool isJetNow_;
	float speed_;					//移動速度
public:
	EmitterData  RandEffectData_;
	EmitterData  DeadEffectData;
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

	/// <summary>
	/// 動いていいかどうかを返す
	/// </summary>
	/// <returns>動いて良ければtrue</returns>
	bool IsMove() { return isMove_; }

	/// <summary>
	/// 動いていいかどうかを設定する
	/// </summary>
	/// <param name="_flag">判定</param>
	void SetIsMove(bool _flag) { isMove_ = _flag; }

	/// <summary>
	/// 死亡時エフェクトの初期化
	/// </summary>
	void InitDeadEffect();

	/// <summary>
	/// 着地時エフェクトの初期化
	/// </summary>
	void InitRandEffect();



	/// <summary>
	/// 死亡時エフェクトデータを返す
	/// </summary>
	/// <returns>死亡時エフェクトデータを返す</returns>
	EmitterData GetDeadEData();
	
	/// <summary>
	/// 着地時エフェクトデータを返す
	/// </summary>
	/// <returns>着地時エフェクトデータ</returns>
	EmitterData GetRandEData();

	/// <summary>
	/// ジェットのpolylineデータを返す
	/// </summary>
	/// <returns>ジェットのpolylineデータ</returns>
	PolyLine GetJettPData();
	
	void SetIsJetNow( bool _jet);

	/// <summary>
	/// 下に伸びるレイキャスト情報を取得
	/// </summary>
	/// <returns>レイキャスト情報</returns>
	RayCastData GetDownData() { return downData_; }

	void GetFirewood();

	int GetFirewoodNum() { return firewoodNum_; }
	void SetFirewoodNum(int _n) { firewoodNum_ = _n; }

	/// <summary>
	/// プレイヤーと地形の相互作用を記述する関数
	/// </summary>
	void TerrainInteraction();

	//設定：プレイヤーの速度
	void SetSpeed(float _s) { speed_ = _s; }

	//取得：プレイヤーの速度
	float GetSpeed() { return speed_; }
};
