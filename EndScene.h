#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

/// <summary>
/// チームロゴを表示するシーンオブジェクト
/// </summary>
class EndScene : public GameObject
{
private:
	int hPict_;	//画像番号
	float scroll;
	int posi;

	Text* pText;

public:
	//コンストラクタ
	EndScene(GameObject* parent);

	//継承{初期化・更新・描画・開放}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {}
};
