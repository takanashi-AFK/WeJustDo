#pragma once
#include "Engine/GameObject.h"

class StartCount;
class Timer;
class ItemCounter;
class Stage;
class Player;

//テストシーンを管理するクラス
class TestScene : public GameObject
{
	bool isGameNow_;

	//必要なオブジェクト
	StartCount* pStartCount_;//Object-StartCount
	ItemCounter* pItemCounter_;//UI-ItemCount
	Timer* pTimer_;//UI-TimeCount
	//UI-JetpackGauge
	Player* pPlayer_;//Object-Player
	Stage* pStage_;//Object-Stage
	int hPict_;//Image-BackGround
	//Audio-PlaySceneMusic

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

	void SceneReset();
};