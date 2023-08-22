#include "ResultScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "AudioManager.h"

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

	frameCount_++;
}

void ResultScene::Draw()
{
	//transform_.scale_ = { 0.8,0.8,1 };
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_); 


	if (frameCount_ >= 30){
		if(frameCount_==30)
	AudioManager::PlayDonSound();
		
	tTimeScore_->SetScale(3.0f);
	tTimeScore_->Draw(700, 270, iTimeScore_);
	}
	if (frameCount_ >= 90) {
		if (frameCount_ == 90)
	AudioManager::PlayDonSound();

	tFirewoodScore_->SetScale(3.0f);
	tFirewoodScore_->Draw(700, 420, iFirewoodScore_);
	}
	if (frameCount_ >= 150) {
		if(frameCount_==150)
	AudioManager::PlayDonSound();

	tTotalScore_->SetScale(3.0f);
	tTotalScore_->Draw(700, 570, iTotalScore_);
	}

	if (frameCount_ >= 200)
	{
		AudioManager::StopDonSound();
	}
}

void ResultScene::Release()
{
	AudioManager::Release();
}
