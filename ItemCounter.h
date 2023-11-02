#pragma once
#include "Engine/GameObject.h"

//前夫宣言
class Text;

class ItemCounter : public GameObject
{
	int hPict_;
	Text* pText_;
public:
	//コンストラクタ
	ItemCounter(GameObject* parent);

	//継承{初期化,更新,描画,開放}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

};

