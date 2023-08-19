#include "TestScene.h"
#include "TestObject.h"
#include "Player.h"
#include "Engine/Camera.h"
#include "StageManager.h"
#include "Stage.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	//Player
	ASSIGN(pPlayer_,CreateSolidObject<Player>(this, "Models/defaultModel.fbx"));

	//Stage
	ASSIGN(pStage_,CreateSolidObject<Stage>(this, "Models/Stage100.fbx"));
}

//更新
void TestScene::Update()
{
	//Camera
	Camera::SetPosition(pPlayer_->GetPosition().x, 5.5, -12);
	Camera::SetTarget(pPlayer_->GetPosition().x, 4.5, 0);
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
