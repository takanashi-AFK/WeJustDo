#include "TestScene.h"

//インクルード
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Timer.h"
#include "StartCount.h"
#include "ItemCounter.h"
#include "Stage.h"
#include "Player.h"
#include "DebugObject.h"
#include "AudioManager.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"), isGameNow_(false)
{
}

//初期化
void TestScene::Initialize()
{
	//Sceneに必要なもの
	{
	//Image-BackGround
		ASSIGN(hPict_, Image::Load("Image/BackGround3.png"));
	//Object-Stage
		ASSIGN(pStage_, Instantiate<Stage>(this));
	//Object-Player
		ASSIGN(pPlayer_, CreateSolidObject<Player>(this, "Models/ziro_move.fbx"));
		{
			pPlayer_->SetIsMove(false);
			pPlayer_->SetSpeed(0.1f);
			pPlayer_->SetFirewoodNum(20*5);
		}
	//UI-ItemCount
		ASSIGN(pItemCounter_, Instantiate<ItemCounter>(this));
	//UI-TimeCount
		ASSIGN(pTimer_, Instantiate<Timer>(this)); 
		{
			pTimer_->SetTime_Seconds(60);
			pTimer_->IsDraw(true);
		}
	//Object-StartCount
		ASSIGN(pStartCount_, Instantiate<StartCount>(this));
	//UI-JetpackGauge
	}
	//Object-DebugObject
		//CreateSolidObject<DebugObject>(this,"Models/defaultModel.fbx");

}

//更新
void TestScene::Update()
{//Sceneの流れ
	if (false)return;
//Start
	//ゲームを開始する
	isGameNow_ = true;

	//スタートカウントを実行する(3..2..1..みたいな)
	if (pStartCount_->IsFinished()) {/*スタートカウント演出を処理したら*/
		pPlayer_->SetIsMove(true);//Playerを動作可能にする
		pTimer_->Start(true);//タイマーを開始する
		AudioManager::Play_PlayMusic();//Audio-PlaySceneMusic
	}

//Play
	//制限時間になるまでタイマーを動かす
	if (pTimer_->IsFinished()) {/*制限時間になったら*/
		//ゲームを終了する
		isGameNow_ = false;
	}
	if (false) {/*PlayerがDead状態になり死亡演出を処理したら*/
		//ゲームを終了する
		isGameNow_ = false;
	}

	//debug
	Transform *p = pPlayer_->GetTransformAddress();
	if (p->position_.x >= 285)
	{
		Global::gTime =  pTimer_->GetTime_Seconds();
		pTimer_->Stop(true);
		isGameNow_ = false;
	}

//End
	if (isGameNow_ == false) {/*ゲームが終了したら*/
		//PlayScene->ResultScene にシーン遷移を行う
		SceneManager* pScM = (SceneManager*)FindObject("SceneManager");
		pScM->ChangeScene(SCENE_ID_RESULT, TID_WHITEOUT);
	}
	
}

//描画
void TestScene::Draw()
{
	if (false)return;
//Sceneの描画するもの

	//背景画像
	Transform t_backGround; t_backGround.scale_ = { 1.5f,1.5f,1.0f };
	Image::SetRect(hPict_, 0+pPlayer_->GetPosition().x, 0, 1024, 512);
	Image::SetTransform(hPict_, t_backGround);
	Image::Draw(hPict_);
}

//開放
void TestScene::Release()
{
//Scene開放するもの 無し
}
