#include "TestScene.h"

//�C���N���[�h
#include "Engine/SceneManager.h"

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

	//UI-ItemCount

	//UI-TimeCount

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

	//�^�C�}�[���J�n 
	//�X�^�[�g�J�E���g�����s����(3..2..1..�݂�����)
	if (true) {/*�X�^�[�g�J�E���g���o������������*/
		//Player�𓮍�\�ɂ���
	}

//Play
	//�������ԂɂȂ�܂Ń^�C�}�[�𓮂���
	if (true) {/*�������ԂɂȂ�����*/
		//�Q�[�����I������
		isGameNow_ = false;
	}
	if (true) {/*Player��Dead��ԂɂȂ莀�S���o������������*/
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
