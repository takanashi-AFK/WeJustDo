#include "TestScene.h"
#include "TestStage.h"
#include "TestPlayer.h"
#include "Character.h"
#include "Engine/Camera.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Instantiate<TestStage>(this);
	Instantiate<TestPlayer>(this);
	//Instantiate<Character>(this);

	/*Camera::SetPosition(0, 3, -10);
	Camera::SetTarget(0,3.5f,0);*/
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
