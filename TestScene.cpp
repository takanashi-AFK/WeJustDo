#include "TestScene.h"
#include "Stage.h"
#include "Player.h"
#include "Engine/Image.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	//�w�i�𐶐�
	ASSIGN(hPict_, Image::Load("Image/BackGround4.png")); {

	}
	//Stage Create
	Instantiate<Stage>(this);

	//Player Create
	CreateSolidObject<Player>(this, "Models/ziro_move.fbx");
}

//�X�V
void TestScene::Update()
{
}
//�`��
void TestScene::Draw()
{
	//�w�i�摜��`��
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void TestScene::Release()
{
}
