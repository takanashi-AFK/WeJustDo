#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene")
{
}

void TitleScene::Initialize()
{
}

void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_PLAY);
	}
}

void TitleScene::Draw()
{
}

void TitleScene::Release()
{
}
