#pragma once
#include "Engine/GameObject.h"

//テストシーンを管理するクラス
class TestScene : public GameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親オブジェクト</param>
	TestScene(GameObject* parent);

	//GameObject継承メソッド
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};