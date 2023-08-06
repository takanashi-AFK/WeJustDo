#pragma once
#include "Engine/GameObject.h"
class TestPlayer: public GameObject
{
private:
	int hModel_;
	bool isJumping;
	float moveY;
	float Deg;
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

