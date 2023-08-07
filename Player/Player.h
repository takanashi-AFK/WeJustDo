#pragma once
#include "../Engine/GameObject.h"
#include <vector>
class PlayerStateManager;

class Player : public GameObject
{
private:
	PlayerStateManager* pState_;
public:
	Player(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

