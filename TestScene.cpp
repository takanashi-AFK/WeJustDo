#include "TestScene.h"
#include "Stage.h"

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
