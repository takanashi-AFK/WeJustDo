#pragma once
#include "Engine/GameObject.h"
class TitleScene : public GameObject
{
private:
	int hPict_;
public:
	TitleScene(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

