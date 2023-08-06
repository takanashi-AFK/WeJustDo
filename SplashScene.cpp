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
	hPict_ = Image::Load("SplashImage.png");
}

void SplashScene::Update()
{
	static float time = 0;
	static float changeTime = 0.7f;
	time++;

	if (time/60 >= changeTime) {
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_TITLE, TID_BLACKOUT);
	}
}

void SplashScene::Draw()
{
	Image::SetTransform(hPict_,transform_);
	Image::Draw(hPict_);
}