#include "ResultScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"


ResultScene::ResultScene(GameObject* parent)
	:GameObject(parent, "ResultScene"), hPict_(-1)
{
}

void ResultScene::Initialize()
{
	hPict_ = Image::Load("Image/ResultBooksCard.png");
	card_.scale_ = { 0.6f,0.7f,0.6f };
	card_.position_.x = 0.5;
	bgPict_ = Image::Load("Image/ResultSceneBook.png");

	bg_.scale_ = { 1,1,1 };

	pText = new Text;
	pText->Initialize();
}

void ResultScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_TEST, TID_BLACKOUT);//‚ ‚Æ‚Åƒ^ƒCƒgƒ‹‚É‚·‚é
	}
	
	if (Input::IsKeyDown(DIK_UP))
	{
		bg_.position_.y += 0.25;
	}
	if (Input::IsKeyDown(DIK_DOWN))
	{
		bg_.position_.y -= 0.25;
	}
	if (Input::IsKeyDown(DIK_LEFT))
	{
		bg_.position_.x -= 0.25;
	}
	if (Input::IsKeyDown(DIK_RIGHT))
	{
		bg_.position_.x += 0.25;
	}
	if (Input::IsKeyDown(DIK_I))
	{
		bg_.position_.x = 0;
	}
	

	if (Input::IsKeyDown(DIK_M))
	{
		bg_.scale_.x += 0.1;
		bg_.scale_.y += 0.1;
	}
	if (Input::IsKeyDown(DIK_N))
	{
		bg_.scale_.x -= 0.1;
		bg_.scale_.y -= 0.1;
	}
}

void ResultScene::Draw()
{

	Image::SetTransform(bgPict_, bg_);
	Image::Draw(bgPict_);

	Image::SetTransform(hPict_, card_);
	Image::Draw(hPict_);
}


