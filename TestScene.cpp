#include "TestScene.h"
#include "TestObject.h"
#include "Player.h"
#include"Engine/Input.h"

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
	StageManager::CreateStage(this, "MapTest1.csv");

	

	Player* pPlayer = CreateSolidObject<Player>(this, "Models/defaultModel.fbx");
}

//�X�V
void TestScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {

		SceneManager* toResult = (SceneManager*)FindObject("SceneManager");
		toResult->ChangeScene(SCENE_ID_RESULT, TID_BLACKOUT);//���ƂŃ^�C�g���ɂ�

	}
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
	StageManager::StageTableRelease();
}
