#include "SplashScene.h"

//�C���N���[�h
#include "Engine/Image.h"	//�`�[�����S�摜�\���̈�
#include "Engine/SceneManager.h"//�V�[���J�ڂ̈�

//�t���[�����[�g/60fps
const float FPS = 60.0f;

//�R���X�g���N�^
SplashScene::SplashScene(GameObject* parent)
	:GameObject(parent,"SplashScene"),hPict_(-1)
{
}

//������
void SplashScene::Initialize()
{
	//�摜�����[�h
	ASSIGN(hPict_,Image::Load("Image/Splash.png"));
	assert(hPict_ >= 0);
}

//�X�V
void SplashScene::Update()
{
	//�K�v�ȕϐ��̐錾�E������
	static float time = 0;
	static float changeTime = 0.7f;

	//0.7�b�o�߂�������...
	if (time/FPS >= changeTime) {
		//�V�[���J�ڂ��s��
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_TITLE,TID_BLACKOUT);
	}
	time++;//���Ԃ�i�߂�
}

//�`��
void SplashScene::Draw()
{
	//�摜��`��
	Image::SetTransform(hPict_,transform_);
	Image::Draw(hPict_);
}


