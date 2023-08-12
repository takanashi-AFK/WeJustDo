#pragma once
#include "Engine/GameObject.h"
class SplashScene : public GameObject
{
private:
	int hPict_;
public:
	SplashScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
};

