#include "ResultScene.h"

//�C���N���[�h
#include "Engine/Image.h"

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
}

//�X�V
void ResultScene::Update()
{
}

//�`��
void ResultScene::Draw()
{
	//�摜�̕`��
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}
