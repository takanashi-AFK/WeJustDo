#pragma once
#include "Engine/GameObject.h"
class PlayerObject : public GameObject
{
private:
	int hModel_;
public:
	PlayerObject(GameObject* parent);
	
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void SavePosition(Transform &transform);
};

