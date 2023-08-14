#include "TestScene.h"
#include "TestObject.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	SolidObject* p1 = CreateSolidObject<TestObject>(this, "defaultModel.fbx");
	SolidObject* p2 = CreateSolidObject<TestObject>(this, "defaultModel.fbx");

	dynamic_cast<TestObject*>(p1)->IsMove(false);

	/*
	* �����I�u�W�F�N�g���ȏ�쐬���悤�Ƃ���Ǝ��񂶂Ⴄ...
	* Instantiate�ł͂ł��Ă������Ƃ��ł��Ȃ��Ȃ��Ă�?
	*/
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
