#include "TestScene.h"
#include "TestObject.h"
#include "Player.h"
#include "Engine/Camera.h"
#include "StageManager.h"
#include "Stage.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	//Player
	ASSIGN(pPlayer_,CreateSolidObject<Player>(this, "Models/ziro2.fbx"));
	{
		pPlayer_->SetScale(0.15f, 0.15f, 0.15f);
		//pPlayer_->SetScale(0.5f, 0.5f, 0.5f);
		pPlayer_->SetRotateY(90);
	}
	//Stage
	ASSIGN(pStage_,CreateSolidObject<Stage>(this, "Models/Stage100.fbx"));

	ASSIGN(hPict_, Image::Load("Image/BackGround4.png"));
}

//更新
void TestScene::Update()
{
	//debug-Camera-Command
	/*
	static float a = 5.4;
	if (Input::IsKey(DIK_Q))a+= 0.1;
	if (Input::IsKey(DIK_A))a-= 0.1;
	static float b = 4.0;
	if (Input::IsKey(DIK_E))b+= 0.1;
	if (Input::IsKey(DIK_D))b-= 0.1;
	static float c = 6.8;
	if (Input::IsKey(DIK_Z))c += 0.1;
	if (Input::IsKey(DIK_C))c -= 0.1;
	static float d = 7.3;
	if (Input::IsKey(DIK_W))d += 0.1;
	if (Input::IsKey(DIK_S))d -= 0.1;
	*/

	//Camera
	Camera::SetPosition(pPlayer_->GetPosition().x, 5.4f, -12.7);
	Camera::SetTarget(pPlayer_->GetPosition().x, 4.0f, 7.3f);

	if (pPlayer_->GetPosition().y <= -20.0f) {
		SceneManager* sM=(SceneManager*)FindObject("SceneManager");
		sM->ChangeScene(SCENE_ID_RESULT, TID_WHITEOUT);
	}

	//debug-SceneMove
	SceneManager* sm = (SceneManager*)FindObject("SceneManager");
	if (Input::IsKeyDown(DIK_1))sm->ChangeScene(SCENE_ID_TITLE);
	if (Input::IsKeyDown(DIK_2))sm->ChangeScene(SCENE_ID_PLAY);
	if (Input::IsKeyDown(DIK_3))sm->ChangeScene(SCENE_ID_RESULT);
	if (Input::IsKeyDown(DIK_4))sm->ChangeScene(SCENE_ID_TEST);
}
//描画
void TestScene::Draw()
{
	//BackGround3
	//Image::SetRect(hPict_, 0 - ((0 - pPlayer_->GetPosition().x) * 10), 512, 2048, 512);
	//transform_.scale_ = { 1.5,1.5,1 };
	Image::SetRect(hPict_, 0 - ((0 - pPlayer_->GetPosition().x) * 10), 720, 2048, 720);
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void TestScene::Release()
{
}
