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
	static const float GRAVITY_ADDITION = 0.03f;

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
	RayCastData downData;

	PolyLine* pJet;
	
	//ziro2
	int ziro;

protected:
	///// 必要な情報 ////////////////////////////////////////
	PlayerStateManager* pState_;	//Playerの状態管理

	///// あたり判定 ////////////////////////////////////////
	RayCastData underRay_;		//プレイヤーの下に伸びるレイ
	Stage* pStage_;		//ステージクラスのポインタ
	int			hGroundModel_;	//ステージのモデル番号を入れる変数
	float		acceleration_;	//重力の加速度
	bool		isAddGravity_;	//重力を加えるか否か
	bool		isJumpNow_;		//ジャンプ中か否か
	bool		isMove_;		//動いていいいか
	bool		isJetNow_ = false;
public:
	
	EmitterData  RandEffectData_;
	
	EmitterData  DeadEffectData;
	
	//コンストラクタ
	Player(GameObject* _parent, string _modelFileName);

	//継承{初期化・更新・描画・開放}
	void ChildInitialize() override;
	void ChildUpdate() override;
	void ChildRelease() override;
	void ChildDraw() override;

	void PolyDraw() override;

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
	PlayerStateManager* GetState() { return pState_; };

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

	/// <summary>
	/// 重力を加えるかどうかを設定
	/// </summary>
	/// <param name="_flag">加えるならtrue</param>
	void IsAddGravity(bool _flag) { isAddGravity_ = _flag; }

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

	float GetAccelaration() { return acceleration_; }


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
	
	void   SetIsJetNow( bool _jet);

	RayCastData GetDownData() { return downData; }
};
