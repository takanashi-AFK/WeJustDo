#pragma once
#include "Engine/GameObject.h"
class SkySphere :public GameObject
{
	int hModel_;
	int hPict_;
public:
	SkySphere(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
};

