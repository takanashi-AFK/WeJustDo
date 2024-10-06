#pragma once
#include "Engine/Global.h"

//前方宣言
class Player;

/// <summary>
/// プレイヤーの状態基底クラス
/// </summary>
class PlayerState
{
public:
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="_p">Playerのポインタ</param>
	virtual void Update(Player* _p){}

	/// <summary>
	/// 入力によって状態を変化する
	/// </summary>
	/// <param name="player">Playerのポインタ</param>
	virtual void HandleInput(Player* _p) {};

	/// <summary>
	/// 状態変化したときに一度だけ呼ばれる関数
	/// </summary>
	/// <param name="player">Playerのポインタ</param>
	virtual void Enter(Player* _p) {};

	/// <summary>
	/// 状態変更
	/// </summary>
	/// <param name="_currentState">現在の状態</param>
	/// <param name="_nextState">変化したい状態</param>
	void ChangeState(PlayerState* _currentState, PlayerState* _nextState);


};

