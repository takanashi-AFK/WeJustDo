#include "TestScene.h"
#include "Stage.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	//Stage Create
	Instantiate<Stage>(this);
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
