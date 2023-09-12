#include "TestScene.h"

//�C���N���[�h
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Timer.h"
#include "StartCount.h"
#include "ItemCounter.h"
#include "Stage.h"
#include "Player.h"
#include "DebugObject.h"
#include "AudioManager.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"), isGameNow_(false)
{
}

//������
void TestScene::Initialize()
{
	//Scene�ɕK�v�Ȃ���
	{
	//Image-BackGround
		ASSIGN(hPict_, Image::Load("Image/BackGround3.png"));
	//Object-Stage
		ASSIGN(pStage_, Instantiate<Stage>(this));
	//Object-Player
		ASSIGN(pPlayer_, CreateSolidObject<Player>(this, "Models/ziro_move.fbx"));
		{
			pPlayer_->SetIsMove(false);
			pPlayer_->SetSpeed(0.1f);
			pPlayer_->SetFirewoodNum(20*5);
		}
	//UI-ItemCount
		ASSIGN(pItemCounter_, Instantiate<ItemCounter>(this));
	//UI-TimeCount
		ASSIGN(pTimer_, Instantiate<Timer>(this)); 
		{
			pTimer_->SetTime_Seconds(60);
			pTimer_->IsDraw(true);
		}
	//Object-StartCount
		ASSIGN(pStartCount_, Instantiate<StartCount>(this));
	//UI-JetpackGauge
	}
	//Object-DebugObject
		//CreateSolidObject<DebugObject>(this,"Models/defaultModel.fbx");

}

//�X�V
void TestScene::Update()
{//Scene�̗���
	if (false)return;
//Start
	//�Q�[�����J�n����
	isGameNow_ = true;

	//�X�^�[�g�J�E���g�����s����(3..2..1..�݂�����)
	if (pStartCount_->IsFinished()) {/*�X�^�[�g�J�E���g���o������������*/
		pPlayer_->SetIsMove(true);//Player�𓮍�\�ɂ���
		pTimer_->Start(true);//�^�C�}�[���J�n����
		AudioManager::Play_PlayMusic();//Audio-PlaySceneMusic
	}

//Play
	//�������ԂɂȂ�܂Ń^�C�}�[�𓮂���
	if (pTimer_->IsFinished()) {/*�������ԂɂȂ�����*/
		//�Q�[�����I������
		isGameNow_ = false;
	}
	if (false) {/*Player��Dead��ԂɂȂ莀�S���o������������*/
		//�Q�[�����I������
		isGameNow_ = false;
	}

	//debug
	Transform *p = pPlayer_->GetTransformAddress();
	if (p->position_.x >= 285)
	{
		Global::gTime =  pTimer_->GetTime_Seconds();
		pTimer_->Stop(true);
		isGameNow_ = false;
	}

//End
	if (isGameNow_ == false) {/*�Q�[�����I��������*/
		//PlayScene->ResultScene �ɃV�[���J�ڂ��s��
		SceneManager* pScM = (SceneManager*)FindObject("SceneManager");
		pScM->ChangeScene(SCENE_ID_RESULT, TID_WHITEOUT);
	}
	
}

//�`��
void TestScene::Draw()
{
	if (false)return;
//Scene�̕`�悷�����

	//�w�i�摜
	Transform t_backGround; t_backGround.scale_ = { 1.5f,1.5f,1.0f };
	Image::SetRect(hPict_, 0+pPlayer_->GetPosition().x, 0, 1024, 512);
	Image::SetTransform(hPict_, t_backGround);
	Image::Draw(hPict_);
}

//�J��
void TestScene::Release()
{
//Scene�J��������� ����
}
