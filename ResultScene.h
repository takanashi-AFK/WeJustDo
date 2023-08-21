#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
class ResultScene : public GameObject
{
	int hPict_;
	int frameCount_;
	

	int iTimeScore_=123;
	int iFirewoodScore_=456;
	int iTotalScore_=789;

	Text* tTimeScore_;
	Text* tFirewoodScore_;
	Text* tTotalScore_;
	
public:
	ResultScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

