#include "TitleScene.h"
#include "Engine/Image.h"
#include "SkySphere.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "AudioManager.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene")
{
}

void TitleScene::Initialize()
{
	Instantiate<SkySphere>(this);
	AudioManager::Initialize();
	AudioManager::Play_TitleMusic();
}

void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		AudioManager::PlayConfirmSound();
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_TEST, TID_WHITEOUT);
	}

	//debug-SceneMove
	SceneManager* sm = (SceneManager*)FindObject("SceneManager");
	if (Input::IsKeyDown(DIK_1))sm->ChangeScene(SCENE_ID_TITLE);
	if (Input::IsKeyDown(DIK_2))sm->ChangeScene(SCENE_ID_PLAY);
	if (Input::IsKeyDown(DIK_3))sm->ChangeScene(SCENE_ID_RESULT);
	if (Input::IsKeyDown(DIK_4))sm->ChangeScene(SCENE_ID_TEST);

}

void TitleScene::Draw()
{
}

void TitleScene::Release()
{
	AudioManager::Release();
}
