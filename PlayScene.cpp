#include "PlayScene.h"

//インクルード
#include "Player.h"
#include "Timer.h"
#include "FuelGauge.h"
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
	pTime = Instantiate<Timer>(this);
	FuelGauge* fg = Instantiate<FuelGauge>(this);

	pTime->Initialize();
	pCount = Instantiate<CountDown>(this);
	pCount->Draw();



	//BGMを再生
	AudioManager::Initialize();
	AudioManager::Play_PlayMusic();
}

//更新
void PlayScene::Update()
{
	pTime->Start();

	time = pTime->GetTime();
	
	//if (time >= 600) {
	//	SceneManager* sm = (SceneManager*)FindObject("SceneManager");
	//	sm->ChangeScene(SCENE_ID_RESULT,TID_WHITEOUT);
	//}
	
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
