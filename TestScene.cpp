#include "TestScene.h"

//インクルード
#include "Engine/SceneManager.h"

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
	//Object-StartCount

	//UI-ItemCount

	//UI-TimeCount

	//UI-JetpackGauge

	//Object-Player

	//Object-Stage

	//Image-BackGround

	//Audio-PlaySceneMusic

	}
}

//更新
void TestScene::Update()
{//Sceneの流れ

//Start
	//ゲームを開始する
	isGameNow_ = true;

	//タイマーを開始 
	//スタートカウントを実行する(3..2..1..みたいな)
	if (true) {/*スタートカウント演出を処理したら*/
		//Playerを動作可能にする
	}

//Play
	//制限時間になるまでタイマーを動かす
	if (true) {/*制限時間になったら*/
		//ゲームを終了する
		isGameNow_ = false;
	}
	if (true) {/*PlayerがDead状態になり死亡演出を処理したら*/
		//ゲームを終了する
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
//Sceneの描画するもの 無し
}

//開放
void TestScene::Release()
{
//Scene開放するもの 無し
}
