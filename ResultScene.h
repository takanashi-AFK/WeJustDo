#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
class ResultScene : public GameObject
{
private:
	int hPict_;
	int bgPict_;

	int totalScore=123;
	int firewoodScore=456;
	int timeScore=789;


	Text* pTotal_;
	Text* pFirewood_;
	Text* pTime_;


	Transform card_;
	Transform bg_;
public:
	ResultScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
};
