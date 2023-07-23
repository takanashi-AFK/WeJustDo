#pragma once
#include "Engine/GameObject.h"
class TestPlayer: public GameObject
{
private:
	int hModel_;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親オブジェクト</param>
	TestPlayer(GameObject* parent);

	//GameObject継承メソッド
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

};

