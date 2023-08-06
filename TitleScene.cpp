#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "SkySphere.h"
#include "Engine/Camera.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene")
{
}

void TitleScene::Initialize()
{
	Camera::SetTarget(XMFLOAT3(0, 1, 0));
	Instantiate<SkySphere>(this);
}

void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_PLAY,TID_BLACKOUT);
	}
}

void TitleScene::Draw()
{
}

void TitleScene::Release()
{
}
