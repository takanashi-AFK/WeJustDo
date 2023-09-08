#include "PlayScene.h"

//インクルード
#include "Player.h"
#include "Timer.h"
#include "FuelGauge.h"
#include "CountDown.h"


#include "Engine/Image.h"
#include "Engine/Camera.h"
#include "AudioManager.h"
#include "Engine/SceneManager.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene"),hPict_(-1)
{
}

//初期化
void PlayScene::Initialize()
{
	//背景を生成
	ASSIGN(hPict_, Image::Load("Image/BackGround4.png"));{}

	//ステージを生成
	CreateSolidObject<Stage>(this,"Models/stage100.fbx");{}

	//プレイヤーを生成
	CreateSolidObject<Player>(this,"Models/ziro2.fbx");{}

	FuelGauge* fg = Instantiate<FuelGauge>(this);

	pCount = Instantiate<CountDown>(this);
	pTimer = Instantiate<Timer>(this);

	//ここで制限時間を決める【〇.〇秒】
	pTimer->SetLimit(12.0f);

	//BGMを再生
	AudioManager::Initialize();
	AudioManager::Play_PlayMusic();
}

//更新
void PlayScene::Update()
{
	if (pCount->IsFinished())
	{
		pTimer->TimeLimitStart();
	} 
	pTimer->Update();

	if (pTimer->IsLimitEnd()) {
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_RESULT,TID_WHITEOUT);
	}
}

//描画
void PlayScene::Draw()
{
	//背景画像を描画
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void PlayScene::Release()
{
}
