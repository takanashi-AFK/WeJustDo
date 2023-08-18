#include "TestScene.h"
#include "TestObject.h"
#include "Player.h"

#include "StageManager.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	//�X�e�[�W���쐬
	StageManager::CleateStage(this);

	

	Player* pPlayer = CreateSolidObject<Player>(this, "Models/defaultModel.fbx");
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
