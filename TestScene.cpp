#include "TestScene.h"
#include "TestObject.h"
#include "Player.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	///// setting Object1 ///////////////////////////////////////////////////////
	SolidObject* p1 = CreateSolidObject<TestObject>(this, "defaultModel.fbx");
	{
		dynamic_cast<TestObject*>(p1)->IsMove(false);
		p1->SetPositionX(-2.0f);
	}

	///// setting Object2 ///////////////////////////////////////////////////////
	SolidObject* p2 = CreateSolidObject<TestObject>(this, "defaultModel.fbx");
	{

	}

	Player* pPlayer = CreateSolidObject<Player>(this, "defaultModel.fbx");

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
