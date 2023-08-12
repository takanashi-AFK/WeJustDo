#include "TestScene.h"
#include"asiba.h"
#include"yuka.h"
#include"player.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Instantiate<asiba>(this);
	Instantiate<yuka>(this);
	Instantiate<player>(this);
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
