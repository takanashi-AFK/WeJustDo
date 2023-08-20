#pragma once
#include "Engine/GameObject.h"
class ResultScene : public GameObject
{
	int hPict_;
public:
	ResultScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

