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
	pText = new Text;
	Camera::SetTarget(XMFLOAT3(0, 1, 0));
	Instantiate<SkySphere>(this);
	pText->Initialize("JiyuuFont.png", 32, 64, 92);
}

void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_SELECT,TID_BLACKOUT);
	}
}

void TitleScene::Draw()
{
	pText->Draw(30, 30, "09182736405AaBbCcDdEeFfGg");
}

void TitleScene::Release()
{
}
