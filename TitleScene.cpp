#include "TitleScene.h"
#include "Engine/Image.h"
#include "SkySphere.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene")
{
}

void TitleScene::Initialize()
{
	Instantiate<SkySphere>(this);

	

}

void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_TEST, TID_BLACKOUT);
	}
}

void TitleScene::Draw()
{
	
}

void TitleScene::Release()
{
}
