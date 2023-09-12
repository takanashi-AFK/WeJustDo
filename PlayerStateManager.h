#pragma once
#include "PlayerState.h"

//インクルード
#include "StandingState.h"
#include "RunningState.h"
#include "JumpingState.h"
#include "MovieState.h"
#include "DeadState.h"
#include "JetState.h"

//前方宣言
class Player;
class StandingState;
class RunningState;
class JumpingState;
class MovieState;
class DeadState;
class JetState;

/// <summary>
/// プレイヤーの各状態の遷移を管理するクラス
/// </summary>
class PlayerStateManager : public PlayerState
{
public:
	PlayerState* playerState_;
	PlayerState* prevState_;

	StandingState* pStanding_;
	RunningState* pRunning_;
	JumpingState* pJumping_;
	MovieState* pMovie_;
	DeadState* pDead_;
	JetState* pJet_;

	bool isProhibited_;				//Stateを変更可能かどうか
public:
	//コンストラクタ
	PlayerStateManager();
	~PlayerStateManager();

	//更新
	virtual void Update(Player* _p) override;

	/// <summary>
	/// 入力処理
	/// </summary>
	/// <param name="player">プレイヤーのポインタ</param>
	virtual void HandleInput(Player* player)override;

	/// <summary>
	/// 開始時に一度呼ばれる
	/// </summary>
	/// <param name="player">プレイヤーのポインタ</param>
	virtual void Enter(Player* player)override;

	/// <summary>
	/// Stateの変更を禁ずる
	/// </summary>
	void StateChangeProhibited() { isProhibited_ = true; }

	/// <summary>
	/// 状態を変更する
	/// </summary>
	/// <param name="change">変更後の状態</param>
	/// <param name="player">変更するプレイヤーのポインタ</param>
	/// <param name="flag">true=enterを行う</param>
	void ChangeState(PlayerState* change, Player* player, bool flag);

	void ChangeState(PlayerState* change, Player* player);
};