#include "TestScene.h"
#include "Stage.h"
#include "Player.h"

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
}

//�J��
void TestScene::Release()
{
}
