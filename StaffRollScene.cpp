#include "StaffRollScene.h"

//�C���N���[�h
#include "Engine/Image.h"	//�`�[�����S�摜�\���̈�
#include "Engine/SceneManager.h"//�V�[���J�ڂ̈�
#include "Engine/Input.h"


//�R���X�g���N�^
StaffRollScene::StaffRollScene(GameObject* parent)
	:GameObject(parent, "StaffRollScene"), hPict_(-1)
{
}

//������
void StaffRollScene::Initialize()
{
	//�摜�����[�h
	ASSIGN(hPict_, Image::Load("Image/Staff.png"));
	assert(hPict_ >= 0);
	transform_.scale_ = { 0.8f,0.8f,0.8f };
	transform_.position_.x = -0.1f;
	transform_.position_.y = scroll;

	pText = new Text;
	pText->Initialize();
}

//�X�V
void StaffRollScene::Update()
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
		if(time/FPS >= changeTime){
			//�V�[���J�ڂ��s��
			SceneManager* sm = (SceneManager*)FindObject("SceneManager");
			sm->ChangeScene(SCENE_ID_TITLE, TID_BLACKOUT, 1);
		}
	}
	//�X�N���[��������
	transform_.position_.y = scroll;
}

//�`��
void StaffRollScene::Draw()
{
	//�摜��`��
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}