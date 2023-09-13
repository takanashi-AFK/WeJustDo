#include "TitleScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Direct3D.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene")
{
}

void TitleScene::Initialize()
{
	//�摜�̃��[�h
	std::string filename[ImageNum] = {
		"Buttons/CommonButtonBack.png",
		"Buttons/CommonButtonBackDisable.png",
		"Buttons/FoodButtonGive.png",
		"Buttons/FoodButtonGiveDisable.png"
	};
	for (int i = 0; i < ImageNum; i++) {
		hPict_[i] = Image::Load(filename[i]);
	}
}

void TitleScene::Update()
{
	if (Input::IsKey(DIK_A)) {
		Image::SetAlpha(hPict_[FoodButtonGive], 0);
		Image::SetAlpha(hPict_[CommonButtonBack], 0);
	}
	else{
		Image::SetAlpha(hPict_[FoodButtonGive], 255);
		Image::SetAlpha(hPict_[CommonButtonBack], 255);
	}
		
}

void TitleScene::Draw()
{
	//�`��FCommonButtonBack(������)
	{
		Transform t_ButtonBack;
		t_ButtonBack.position_.y = 0.3f;
		t_ButtonBack.scale_ = { 0.5f,0.5f,1.0f };
		//������Ă�����
		Image::SetTransform(hPict_[CommonButtonBackDisable], t_ButtonBack);
		Image::Draw(hPict_[CommonButtonBackDisable]);

		//������Ă��Ȃ����
		Image::SetTransform(hPict_[CommonButtonBack], t_ButtonBack);
		Image::Draw(hPict_[CommonButtonBack]);
	}

	//�`��FCommonButtonBack(�߂�)
	{
		Transform t_ButtonGive;
		t_ButtonGive.position_.y = -0.3f;
		t_ButtonGive.scale_ = { 0.5f,0.5f,1.0f };
		//������Ă�����
		Image::SetTransform(hPict_[FoodButtonGiveDisable], t_ButtonGive);
		Image::Draw(hPict_[FoodButtonGiveDisable]);

		//������Ă��Ȃ����
		Image::SetTransform(hPict_[FoodButtonGive], t_ButtonGive);
		Image::Draw(hPict_[FoodButtonGive]);
	}
}

void TitleScene::Release()
{
}
