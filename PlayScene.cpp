#include "PlayScene.h"

//�C���N���[�h
#include "Player.h"
#include "Timer.h"
#include "FuelGauge.h"
#include "CountDown.h"


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

	FuelGauge* fg = Instantiate<FuelGauge>(this);

	pCount = Instantiate<CountDown>(this);
	pTimer = Instantiate<Timer>(this);

	//�����Ő������Ԃ����߂�y�Z.�Z�b�z
	pTimer->SetLimit(12.0f);

	//BGM���Đ�
	AudioManager::Initialize();
	AudioManager::Play_PlayMusic();
}

//�X�V
void PlayScene::Update()
{
	if (pCount->IsFinished())
	{
		pTimer->TimeLimitStart();
	} 
	pTimer->Update();

	if (pTimer->IsLimitEnd()) {
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_RESULT,TID_WHITEOUT);
	}
}

//�`��
void PlayScene::Draw()
{
	//�w�i�摜��`��
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void PlayScene::Release()
{
}
