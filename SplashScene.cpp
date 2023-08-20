#include "SplashScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

SplashScene::SplashScene(GameObject* parent)
	:GameObject(parent,"SplashScene"),hPict_(-1)
{
}

void SplashScene::Initialize()
{
	hPict_ = Image::Load("Image/Splash.png");
}

void SplashScene::Update()
{
	static float time = 0;
	static float changeTime = 0.7f;
	time++;

	//debug-SceneMove
	SceneManager* sm = (SceneManager*)FindObject("SceneManager");
	if (Input::IsKeyDown(DIK_1))sm->ChangeScene(SCENE_ID_TITLE);
	if (Input::IsKeyDown(DIK_2))sm->ChangeScene(SCENE_ID_PLAY);
	if (Input::IsKeyDown(DIK_3))sm->ChangeScene(SCENE_ID_RESULT);
	if (Input::IsKeyDown(DIK_4))sm->ChangeScene(SCENE_ID_TEST);


	if (time/60 >= changeTime) {
		sm->ChangeScene(SCENE_ID_TITLE,TID_BLACKOUT);
	}
}

void SplashScene::Draw()
{
	Image::SetTransform(hPict_,transform_);
	Image::Draw(hPict_);
}


