#include "ResultScene.h"

//インクルード
#include "Engine/Image.h"
#include "AudioManager.h"
#include "Engine/Text.h"

//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	:GameObject(parent,"ResultScene"),hPict_(-1)
{
}

//初期化
void ResultScene::Initialize()
{
	//画像のロード
	ASSIGN(hPict_, Image::Load("Image/ResultImage.png"));assert(hPict_ <= 0);



	//Text変数の初期化
	{
		tTimeScore_ = new Text;tTimeScore_->Initialize();
		tFirewoodScore_ = new Text;tFirewoodScore_->Initialize();
		tTotalScore_ = new Text;tTotalScore_->Initialize();
	}
}

//更新
void ResultScene::Update()
{
	frameCount_++;

}

//描画
void ResultScene::Draw()
{
	//画像の描画
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	//BGMを再生
	{
		if (frameCount_ >= 30) {
			if (frameCount_ == 30)
				AudioManager::PlayDonSound();

			tTimeScore_->SetScale(3.0f);
			tTimeScore_->Draw(700, 270, iTimeScore_);
		}
		if (frameCount_ >= 90) {
			if (frameCount_ == 90)
				AudioManager::PlayDonSound();

			tFirewoodScore_->SetScale(3.0f);
			tFirewoodScore_->Draw(700, 420, Global::gFireWood/5);
		}
		if (frameCount_ >= 150) {
			if (frameCount_ == 150)
				AudioManager::PlayDonSound();

			tTotalScore_->SetScale(3.0f);
			tTotalScore_->Draw(700, 570, iTotalScore_);
		}

		if (frameCount_ >= 200)
		{
			AudioManager::StopDonSound();
		}
	}
	
}
