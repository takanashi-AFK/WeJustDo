#pragma once

#include "Stage.h"
#include "Engine/GameObject.h"

class Timer;

/// <summary>
/// ゲームプレイ画面を表示するシーンオブジェクト
/// </summary>
class PlayScene : public GameObject
{
private:
	int hPict_;	//画像番号
	Timer* pTime;
	float timeLimit ;
	bool fin = false;

public:
	//コンストラクタ
	PlayScene(GameObject * parent);

	//継承{初期化・更新・描画・開放}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};
