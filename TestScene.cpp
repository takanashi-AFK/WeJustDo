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
	SolidObject* p1 = CreateSolidObject<TestObject>(this, "defaultModel.fbx");
	SolidObject* p2 = CreateSolidObject<TestObject>(this, "defaultModel.fbx");

	dynamic_cast<TestObject*>(p1)->IsMove(false);

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
