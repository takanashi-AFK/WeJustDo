#include "TestScene.h"
#include "TestObject.h"
#include "Player.h"
#include"Engine/Input.h"

#include "StageManager.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	//ステージを作成
	StageManager::CreateStage(this, "MapTest1.csv");

	

	Player* pPlayer = CreateSolidObject<Player>(this, "Models/defaultModel.fbx");
}

//更新
void TestScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {

		SceneManager* toResult = (SceneManager*)FindObject("SceneManager");
		toResult->ChangeScene(SCENE_ID_RESULT, TID_BLACKOUT);//あとでタイトルにす

	}
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
	StageManager::StageTableRelease();
}
