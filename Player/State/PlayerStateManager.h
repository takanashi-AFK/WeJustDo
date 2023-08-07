#pragma once
#include "PlayerState.h"
#include <vector>
class PlayerStateManager : public PlayerState
{
private:
	//���
	enum eState {
		eState_Standing, // �������
		
		eState_Max,
	};
	std::vector<PlayerState*> StatePool_;
	PlayerState* nowState_;
public:
	PlayerStateManager();
	void Update(Player* player) override;
	void Enter(Player* player) override;
};

