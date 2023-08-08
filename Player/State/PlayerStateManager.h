#pragma once
#include "PlayerState.h"
#include <vector>
class PlayerStateManager : public PlayerState
{
private:
	//ó‘Ô
	enum eState {
		eState_Standing, // —§‚¿ó‘Ô
		eState_Reading,  // “Ç‚İó‘Ô
		eState_Running,	 // ‘–‚èó‘Ô
		eState_Jumping,  // ƒWƒƒƒ“ƒvó‘Ô
		eState_Falling,	 // —‰ºó‘Ô
		eState_Dying,	 // €–Só‘Ô
		eState_Max,
	};
	std::vector<PlayerState*> StatePool_;
	PlayerState* nowState_;
public:
	PlayerStateManager();
	void Update(Player* player) override;
	void Enter(Player* player) override;

	//Šeíó‘Ô
	static StandingState* playerStanding;		//‘Ò‚¿ó‘Ô
	static
};

