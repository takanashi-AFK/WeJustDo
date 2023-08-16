#pragma once
#include "Engine/GameObject.h"

//テストシーンを管理するクラス
class player : public GameObject
{

	int hModel_;
	bool isJumping;
	float moveY;
	float Deg;
	int flame;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	player(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	int GetModelHandle() { return hModel_; }

};