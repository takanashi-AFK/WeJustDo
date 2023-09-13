#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

class Player;

//テストシーンを管理するクラス
class TestScene : public GameObject
{
	Player* p_;
	Text* pText_;
	int hPict_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TestScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};