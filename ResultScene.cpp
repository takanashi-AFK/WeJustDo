#include "ResultScene.h"

//�C���N���[�h
#include "Engine/Image.h"
#include "AudioManager.h"
#include "Engine/Text.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//�R���X�g���N�^
ResultScene::ResultScene(GameObject* parent)
	:GameObject(parent,"ResultScene"),hPict_(-1)
{
}

//������
void ResultScene::Initialize()
{
	//�摜�̃��[�h
	ASSIGN(hPict_, Image::Load("Image/ResultImage.png"));assert(hPict_ <= 0);



	//Text�ϐ��̏�����
	{
		tTimeScore_ = new Text; tTimeScore_->Initialize("Fonts/Oyamayoumou_number.png",64,68,15);

		tFirewoodScore_ = new Text;tFirewoodScore_->Initialize("Fonts/Oyamayoumou_number.png", 64, 68, 15);
		tTotalScore_ = new Text;tTotalScore_->Initialize("Fonts/Oyamayoumou_number.png", 64, 68, 15);
	}
}

//�X�V
void ResultScene::Update()
{
	frameCount_++;

	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSm = (SceneManager*)FindObject("SceneManager");
		pSm->ChangeScene(SCENE_ID_SPLASH, TID_BLACKOUT);
	}

}

//�`��
void ResultScene::Draw()
{
	//�摜�̕`��
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	//BGM���Đ�
	{
		if (frameCount_ >= 30) {
			if (frameCount_ == 30)
				AudioManager::Play_DonSound();

			tTimeScore_->SetScale(1.5f);
			tTimeScore_->Draw(700, 270, Global::gTime);
		}
		if (frameCount_ >= 90) {
			if (frameCount_ == 90)
				AudioManager::Play_DonSound();

			tFirewoodScore_->SetScale(1.5f);
			tFirewoodScore_->Draw(700, 420, Global::gFireWood/5);
		}
		if (frameCount_ >= 150) {
			if (frameCount_ == 150)
				AudioManager::Play_DonSound();

			tTotalScore_->SetScale(2.0f);
			tTotalScore_->Draw(550, 570, (Global::gTime*Global::gFireWood*3.08)+ Global::gFireWood/5);
		}

		if (frameCount_ >= 200)
		{
			AudioManager::Stop_DonSound();
		}
	}
	
}
