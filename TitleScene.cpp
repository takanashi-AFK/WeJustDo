#include "TitleScene.h"
#include "TestObject.h"
#include "Player.h"
#include "Engine/Input.h"
#include "StageManager.h"
#include "Engine/Image.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_(-1)
{
}

//初期化
void TitleScene::Initialize()
{
	hPict_ = Image::Load("Image/TitleScene.png");
}

//更新
void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_TEST, TID_BLACKOUT);
	}
}

//描画
void TitleScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void TitleScene::Release()
{
}
