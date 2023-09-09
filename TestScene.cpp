#include "TestScene.h"

//�C���N���[�h
#include "Engine/SceneManager.h"
#include "Timer.h"
#include "StartCount.h"

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
	//Object-StartCount
		ASSIGN(pStartCount_, Instantiate<StartCount>(this));
		{

		}
	//UI-ItemCount

	//UI-TimeCount
		ASSIGN(pTimer_, Instantiate<Timer>(this)); 
		{
			pTimer_->SetTime_Seconds(120);
			pTimer_->IsDraw(true);
		}
	//UI-JetpackGauge

	//Object-Player

	//Object-Stage

	//Image-BackGround

	//Audio-PlaySceneMusic

	}
}

//�X�V
void TestScene::Update()
{//Scene�̗���

//Start
	//�Q�[�����J�n����
	isGameNow_ = true;

	//�X�^�[�g�J�E���g�����s����(3..2..1..�݂�����)
	if (pStartCount_->IsFinished()) {/*�X�^�[�g�J�E���g���o������������*/
		//Player�𓮍�\�ɂ���
		pTimer_->Start(true);//�^�C�}�[���J�n����
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
//Scene�̕`�悷����� ����
}

//�J��
void TestScene::Release()
{
//Scene�J��������� ����
}
