#include "TitleScene.h"

//�C���N���[�h
#include "Engine/Image.h"	//�摜�̕\���̈�
#include "Engine/Model.h"	//���f���̕\���̈�
#include "Engine/SceneManager.h"	//�V�[���J�ڂ̈�
#include "Engine/Input.h"	//�V�[���J�ڂ̈�
#include "Engine/Camera.h"	//�J�����̈ʒu�X�V�̈�
#include "AudioManager.h"	//BGM�𗬂���

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene"),hPict_(-1),hModel_(-1)
{
}

//������
void TitleScene::Initialize()
{
	//���f���̃��[�h
	ASSIGN(hModel_, Model::Load("Models/SkySphere/BackGroundModel.fbx")); assert(hModel_ <= 0);
	
	//�摜�̃��[�h
	ASSIGN(hPict_, Image::Load("Image/TitleImage2.png")); assert(hPict_ <= 0);

	//�J�����̏�����
	Camera::SetPosition(0, 0, -5);Camera::SetTarget(0, 0, 0);

	//BGM���Đ�
	AudioManager::Initialize();
	AudioManager::Play_TitleMusic();
}

//�X�V
void TitleScene::Update()
{
	//�X�y�[�X�L�[�̓��͎�...
	if (Input::IsKeyDown(DIK_SPACE)) {
		//�V�[���J�ڂ��s��
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_PLAY, TID_WHITEOUT);
	}

	//SkySphere���f������]������
	transform_.rotate_.y += 0.05f;
}

//�`��
void TitleScene::Draw()
{
	//�e�����V�F�[�_�[��K�p
	Direct3D::SetShader(Direct3D::SHADER_NOSHADE);

	//���f����`��
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	
	//�摜��`��
	Transform t;
	Image::SetTransform(hPict_, t);
	Image::Draw(hPict_);

	//�V�F�[�_�[�����Z�b�g
	Direct3D::SetShader(Direct3D::SHADER_3D);
}
