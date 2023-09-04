#include "PlayScene.h"

//�C���N���[�h
#include "Player.h"
#include "Timer.h"
#include "FuelGauge.h"
#include "Engine/Image.h"
#include "Engine/Camera.h"
#include "AudioManager.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene"),hPict_(-1)
{
}

//������
void PlayScene::Initialize()
{
	//�w�i�𐶐�
	ASSIGN(hPict_, Image::Load("Image/BackGround4.png"));{}

	//�X�e�[�W�𐶐�
	CreateSolidObject<Stage>(this,"Models/stage100.fbx");{}

	//�v���C���[�𐶐�
	CreateSolidObject<Player>(this,"Models/ziro2.fbx");{}
	pTime = Instantiate<Timer>(this);
	FuelGauge* fg = Instantiate<FuelGauge>(this);

	pTime->Initialize();

	hPict2_[0] = Image::Load("Image/Count0.png");
	hPict2_[1] = Image::Load("Image/Count1.png");
	hPict2_[2] = Image::Load("Image/Count2.png");
	hPict2_[3] = Image::Load("Image/Count3.png");

	//BGM���Đ�
	AudioManager::Initialize();
	AudioManager::Play_PlayMusic();
}

//�X�V
void PlayScene::Update()
{
	pTime->Start();

	time = pTime->GetTime();
	
	//if (time >= 600) {
	//	SceneManager* sm = (SceneManager*)FindObject("SceneManager");
	//	sm->ChangeScene(SCENE_ID_RESULT,TID_WHITEOUT);
	//}
	
}

//�`��
void PlayScene::Draw()
{
	//�w�i�摜��`��
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	if (time == 1)
	{
		Image::SetTransform(hPict2_[3], transform_);
		Image::Draw(hPict2_[3]);
	}
	if (time == 2)
	{
		Image::SetTransform(hPict2_[2], transform_);
		Image::Draw(hPict2_[2]);
	}
	if (time == 3)
	{
		Image::SetTransform(hPict2_[1], transform_);
		Image::Draw(hPict2_[1]);
	}
	if (time == 4)
	{
		Image::SetTransform(hPict2_[0], transform_);
		Image::Draw(hPict2_[0]);

	}
}

//�J��
void PlayScene::Release()
{
}
