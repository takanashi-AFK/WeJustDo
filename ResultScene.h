#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
class ResultScene : public GameObject
{
private:
	int hPict_;
	int bgPict_;
	Text* pText;
	Transform card_;
	Transform bg_;
public:
	ResultScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
};
