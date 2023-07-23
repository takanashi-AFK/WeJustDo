#pragma once
#include "Engine/GameObject.h"
class TestStage	: public GameObject
{
private:
	int hModel_;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親オブジェクト</param>
	TestStage(GameObject* parent);

	//GameObject継承メソッド
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

