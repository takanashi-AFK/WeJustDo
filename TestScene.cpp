#include "TestScene.h"
#include"asiba.h"
#include"yuka.h"
#include"player.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	Instantiate<asiba>(this);
	Instantiate<yuka>(this);
	Instantiate<player>(this);
}

//�X�V
void TestScene::Update()
{
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
