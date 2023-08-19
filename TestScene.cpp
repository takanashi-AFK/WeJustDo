#include "TestScene.h"
#include "TestObject.h"
#include "Player.h"
#include "Engine/Camera.h"
#include "StageManager.h"
#include "Stage.h"
#include "Engine/Image.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	//Player
	ASSIGN(pPlayer_,CreateSolidObject<Player>(this, "Models/defaultModel.fbx"));

	//Stage
	ASSIGN(pStage_,CreateSolidObject<Stage>(this, "Models/Stage100.fbx"));

	ASSIGN(hPict_, Image::Load("Image/BackGround3.png"));
}

//�X�V
void TestScene::Update()
{
	//Camera
	Camera::SetPosition(pPlayer_->GetPosition().x, 4.5, -12);
	Camera::SetTarget(pPlayer_->GetPosition().x, 4.5, 0);
}

//�`��
void TestScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void TestScene::Release()
{
}
