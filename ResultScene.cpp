#include "ResultScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

ResultScene::ResultScene(GameObject* parent)
	:GameObject(parent,"ResultScene")
{
}

void ResultScene::Initialize()
{
	ASSIGN(hPict_, Image::Load("Image/ResultImage.png"));
	assert(hPict_ <= 0);
}

void ResultScene::Update()
{
	//debug-SceneMove
	SceneManager* sm = (SceneManager*)FindObject("SceneManager");
	if (Input::IsKeyDown(DIK_1))sm->ChangeScene(SCENE_ID_TITLE);
	if (Input::IsKeyDown(DIK_2))sm->ChangeScene(SCENE_ID_PLAY);
	if (Input::IsKeyDown(DIK_3))sm->ChangeScene(SCENE_ID_RESULT);
	if (Input::IsKeyDown(DIK_4))sm->ChangeScene(SCENE_ID_TEST);

}

void ResultScene::Draw()
{
	//transform_.scale_ = { 0.8,0.8,1 };
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void ResultScene::Release()
{
}
