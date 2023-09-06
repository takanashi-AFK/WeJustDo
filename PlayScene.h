#pragma once

#include "Stage.h"
#include "CountDown.h"
#include "Engine/GameObject.h"


/// <summary>
/// ゲームプレイ画面を表示するシーンオブジェクト
/// </summary>
class PlayScene : public GameObject
{
private:
	int hPict_;	//画像番号
	int time;
	int hPict2_[4];
	bool flg =false;
	CountDown* pCount;

public:
	//コンストラクタ
	PlayScene(GameObject * parent);

	//継承{初期化・更新・描画・開放}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	bool IsFinished() { return flg; };
};
