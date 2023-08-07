#pragma once

//前方宣言
class Player;

class PlayerState
{
public:
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="_player"></param>
	virtual void Update(Player* _player) = 0;

	/// <summary>
	/// 状態遷移時に一度だけ呼び出される
	/// </summary>
	/// <param name="_player">プレイヤー情報</param>
	virtual void Enter(Player* _player) {};
};

