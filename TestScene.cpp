#include "TestScene.h"
#include "Stage.h"
#include "Player.h"
#include "DebugObject.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	//Stage Create
	Instantiate<Stage>(this);

	//Player Create
	//CreateSolidObject<Player>(this, "Models/ziro_move.fbx");

	//DebugObject Create
	CreateSolidObject<DebugObject>(this, "Models/defaultModel.fbx");

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
