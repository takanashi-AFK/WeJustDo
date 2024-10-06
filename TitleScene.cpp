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
	ASSIGN(hPict2_, Image::Load("Image/PleseToSpaceKey.png"));
	ASSIGN(hCreditUi_, Image::Load("Image/CreditUI.png")); 

	//�J�����̏�����
	Camera::SetPosition(0, 0, -5);Camera::SetTarget(0, 0, 0);

	
	AudioManager::Play_TitleMusic();
}

//�X�V
void TitleScene::Update()
{
	
	int s = 1;
	if (increasing_) {
		opacity_+=s;
		if (opacity_ >= 255)increasing_ = false; 
	}
	else {
		opacity_-=s;
		if (opacity_ <= 0)increasing_ = true;
	}
	

	//�X�y�[�X�L�[�̓��͎�...
	if (Input::IsKeyDown(DIK_SPACE)) {
		//�V�[���J�ڂ��s��
		AudioManager::Play_ConfirmSound();
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_TEST, TID_WHITEOUT,1);
	}
	
	//press C to Credit
	if (Input::IsKeyDown(DIK_C)) {
		//�V�[���J�ڂ��s��
		AudioManager::Play_ConfirmSound();
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_END, TID_WHITEOUT,1);
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
	Transform t_Title; 
	t_Title.scale_ = { 0.8f,0.8f,1.0f };
	t_Title.position_.y = 0.1f;
	Image::SetTransform(hPict_, t_Title);
	Image::Draw(hPict_);

	Transform t_Space;
	t_Space.position_.y = -0.8f;
	Image::SetAlpha(hPict2_, opacity_);
	Image::SetTransform(hPict2_, t_Space);
	Image::Draw(hPict2_);
	
	Transform t_CreditUI;
	t_CreditUI.position_ = { 0.7,0.7,0 };
	t_CreditUI.scale_ = { 0.3,0.3,0.3 };
	Image::SetTransform(hCreditUi_, t_CreditUI);
	Image::Draw(hCreditUi_);	

	//�V�F�[�_�[�����Z�b�g
	Direct3D::SetShader(Direct3D::SHADER_3D);
}
