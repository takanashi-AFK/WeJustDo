#include "ResultScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "StageManager.h"


ResultScene::ResultScene(GameObject* parent)
	:GameObject(parent, "ResultScene"), hPict_(-1), pTotal_(nullptr),  pTime_(nullptr), pFirewood_(nullptr)
{
}

void ResultScene::Initialize()
{
	StageManager::DeleteStage();
	hPict_ = Image::Load("Image/ResultBooksCard.png");
	card_.scale_ = { 0.6f,0.7f,0.6f };
	card_.position_.x = 0;
	bgPict_ = Image::Load("Image/ResultSceneBook.png");

	bg_.scale_ = { 1,1,1 };

	pTotal_ = new Text;
	pTotal_->Initialize();

	pTime_ = new Text;
	pTime_->Initialize();

	pFirewood_ = new Text;
	pFirewood_->Initialize();

}

void ResultScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_TITLE, TID_BLACKOUT);//‚ ‚Æ‚Åƒ^ƒCƒgƒ‹‚É‚·‚é
	}
	
}

void ResultScene::Draw()
{
	Image::SetTransform(bgPict_, bg_);
	Image::Draw(bgPict_);

	Image::SetTransform(hPict_, card_);
	Image::Draw(hPict_);

	pFirewood_->Draw(540, 325, firewoodScore);
	pTotal_->Draw(540, 375, totalScore);
	pTime_->Draw(540, 425, timeScore);
}


