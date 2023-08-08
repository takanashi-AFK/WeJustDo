#pragma once
#include "PlayerState.h"
#include <vector>
class PlayerStateManager : public PlayerState
{
private:
	//状態
	enum eState {
		eState_Standing, // 立ち状態
		eState_Reading,  // 読み状態
		eState_Running,	 // 走り状態
		eState_Jumping,  // ジャンプ状態
		eState_Falling,	 // 落下状態
		eState_Dying,	 // 死亡状態
		eState_Max,
	};
	std::vector<PlayerState*> StatePool_;
	PlayerState* nowState_;
public:
	PlayerStateManager();
	void Update(Player* player) override;
	void Enter(Player* player) override;

	//各種状態
	static StandingState* playerStanding;		//待ち状態
	static
};

