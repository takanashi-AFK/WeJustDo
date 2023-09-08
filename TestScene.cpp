#include "TestScene.h"
#include "Stage.h"
#include "Player.h"
#include "DebugObject.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "AudioManager.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{

	pText_ = new Text;
	pText_->Initialize();

	//Stage Create
	Instantiate<Stage>(this);

	//Player Create
	//p_ = CreateSolidObject<Player>(this, "Models/ziro_move.fbx"); {
		//p->SetIsMove(false); 
	//}

	//DebugObject Create
	CreateSolidObject<DebugObject>(this, "Models/defaultModel.fbx");

	ASSIGN(hPict_, Image::Load("Image/BackGround3.png"));
}

//�X�V
void TestScene::Update()
{
	//if (p_->GetPosition().y <= -20.0f) {
	//	//�V�[���J�ڂ��s��
	//	SceneManager* sm = (SceneManager*)FindObject("SceneManager");
	//	sm->ChangeScene(SCENE_ID_RESULT, TID_WHITEOUT);
	//}
}

//�`��
void TestScene::Draw()
{
	//pText_->Draw(30, 30, p_->GetFirewoodNum()/5);
	//Image::SetRect(hPict_, );
	Transform t_bg; t_bg.scale_ = { 1.4f,1.4f,1.4f };
	Image::SetTransform(hPict_, t_bg);
	Image::Draw(hPict_);
}

//�J��
void TestScene::Release()
{
}
