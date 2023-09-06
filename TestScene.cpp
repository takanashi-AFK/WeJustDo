#include "TestScene.h"
#include "Stage.h"
#include "Player.h"
#include "DebugObject.h"

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
	//CreateSolidObject<Player>(this, "Models/ziro_move.fbx");

	//DebugObject Create
	CreateSolidObject<DebugObject>(this, "Models/defaultModel.fbx");

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
