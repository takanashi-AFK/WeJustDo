#include "EndScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

EndScene::EndScene(GameObject* parent)
	:GameObject(parent,"EndScene")
{
}

void EndScene::Initialize()
{
}

void EndScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_TITLE);
	}
}

void EndScene::Draw()
{
}

void EndScene::Release()
{
}
