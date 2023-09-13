#pragma once
#include "Engine/GameObject.h"

enum {
	CommonButtonBack,
	CommonButtonBackDisable,
	FoodButtonGive,
	FoodButtonGiveDisable,
	ImageNum
};

class Button : public GameObject
{
	int hPict_[ImageNum];
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Button(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

