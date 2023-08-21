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

	//Text•Ï”‚Ì‰Šú‰»
	
	tTimeScore_ = new Text;
	tTimeScore_->Initialize();
	tFirewoodScore_ = new Text;
	tFirewoodScore_->Initialize();
	tTotalScore_ = new Text;
	tTotalScore_->Initialize();
	
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

	tTimeScore_->Draw(780, 250, iTimeScore_);
	tFirewoodScore_->Draw(780, 350, iFirewoodScore_);
	tTotalScore_->Draw(780, 450, iTotalScore_);
}

void ResultScene::Release()
{
}
