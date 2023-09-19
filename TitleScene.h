#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// タイトルイメージを表示するシーンオブジェクト
/// </summary>
class TitleScene : public GameObject
{
	bool increasing_;
	int opacity_;
private:
	int hPict_;	//画像番号
	int hPict2_;//画像番号２
	int hPict3_;//クレジットのPless CのUI
	int hModel_;//モデル番号
public:
	//コンストラクタ
	TitleScene(GameObject* parent);

	//継承{初期化・更新・描画・開放}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override{}
};

