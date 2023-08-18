#include "TestScene.h"
#include "TestObject.h"
#include "Player.h"

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
	StageManager::CleateStage(this);

	

	Player* pPlayer = CreateSolidObject<Player>(this, "Models/defaultModel.fbx");
}

//更新
void TestScene::Update()
{
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
