#include "TestScene.h"
#include "TestObject.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	CreateSolidObject<TestObject>(this, "defaultModel.fbx");
	//CreateSolidObject<TestObject>(this,"defaultModel.fbx");
	/*
	* 同じオブジェクトを二つ以上作成しようとすると死んじゃう...
	* Instantiateではできていたことができなくなってる?
	*/
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
