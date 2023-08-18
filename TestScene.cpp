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
	SolidObject* p1 = CreateSolidObject<TestObject>(this, "Models/kusaBlock.fbx");
	{
		dynamic_cast<TestObject*>(p1)->IsMove(false);
		p1->SetPositionX(-2.0f);
	}

	///// setting Object2 ///////////////////////////////////////////////////////
	for (int i = 0; i < 250; i++) {
		SolidObject* p2 = CreateSolidObject<TestObject>(this, "Models/rengaBlock.fbx");
		p2->SetPositionX(i);
	}
	

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
