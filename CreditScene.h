#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// ゲームプレイ画面を表示するシーンオブジェクト
/// </summary>
class CreditScene : public GameObject
{
private:
	int hPict_;	//画像番号
public:
	//コンストラクタ
	CreditScene(GameObject* parent);

	//継承{初期化・更新・描画・開放}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};
