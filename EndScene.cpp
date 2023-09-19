
#include "EndScene.h"

//�C���N���[�h
#include "Engine/Image.h"	//�`�[�����S�摜�\���̈�
#include "Engine/SceneManager.h"//�V�[���J�ڂ̈�
#include "Engine/Input.h"
#include "AudioManager.h"


//�R���X�g���N�^
EndScene::EndScene(GameObject* parent)
	:GameObject(parent, "EndScene"), hPict_(-1)
{
}

//������
void EndScene::Initialize()
{
	scroll = -7.9f;
	//�摜�����[�h
	ASSIGN(hPict_, Image::Load("Image/523_20230919225415.png"));
	assert(hPict_ >= 0);
	transform_.scale_ = { 0.8f,0.8f,0.8f };
	transform_.position_.x = -0.1f;
	transform_.position_.y = scroll;

	pText = new Text;
	pText->Initialize();

	AudioManager::Play_TitleMusic();
}

//�X�V
void EndScene::Update()
{
	static int time = 0;
	static int changeTime = 3;
	static int FPS = 60;
	//�摜�̕�������ɗ����Ă���
	if (scroll <= 7.3f)
	{
		scroll += 0.005f;

		if (Input::IsKey(DIK_SPACE))//Space�������Ɖ���
		{
			scroll += 0.05f;
		}
	}

	//�X�N���[�����I�������
	if (scroll >= 7.3f)
	{
		time++;
		//�R�b��������V�[���J��
		if (time / FPS >= changeTime) {
			//�V�[���J�ڂ��s��
			SceneManager* sm = (SceneManager*)FindObject("SceneManager");
			sm->ChangeScene(SCENE_ID_TITLE, TID_BLACKOUT, 1);
		}
	}
	//�X�N���[��������
	transform_.position_.y = scroll;
}

//�`��
void EndScene::Draw()
{
	//�摜��`��
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}