#include "TestScene.h"
#include "TestStage.h"
#include "TestPlayer.h"
#include "Character.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	Instantiate<TestStage>(this);
	Instantiate<TestPlayer>(this);
	//Instantiate<Character>(this);

	/*Camera::SetPosition(0, 3, -10);
	Camera::SetTarget(0,3.5f,0);*/
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
