#pragma once
#include "Engine/GameObject.h"

//前方宣言
class Text;

//テストシーンを管理するクラス
class TestScene : public GameObject
{
	int flame_;
	Text* pText_;
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

	//flame_のゲッター・セッター
	int GetFlame() { return flame_; }
	void SetFlame(int _f) { flame_ = _f; }
	void SetSeconds(int _s) { flame_ = _s * 60; }
};