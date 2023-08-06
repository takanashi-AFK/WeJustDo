#pragma once
#include "Engine/GameObject.h"
class backGround : public GameObject
{
	int hPict_;
public:
	backGround(GameObject* parent);
	void Initialize() override;
	void Draw() override;
};

