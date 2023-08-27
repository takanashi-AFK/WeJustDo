#include "PlayScene.h"

//�C���N���[�h
#include "Player.h"
#include "Stage.h"
#include "Engine/Image.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene"),hPict_(-1)
{
}

//������
void PlayScene::Initialize()
{
	//�w�i�𐶐�
	ASSIGN(hPict_, Image::Load("Image/BackGround4.png"));{

	}

	//�X�e�[�W�𐶐�
	CreateSolidObject<Stage>(this,"Models/stage100.fbx");{

	}

	//�v���C���[�𐶐�
	CreateSolidObject<Player>(this,"Models/ziro2.fbx");{

	}

}

//�X�V
void PlayScene::Update()
{
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
