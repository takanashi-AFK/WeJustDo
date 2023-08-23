#include "StageSelectScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
StageSelectScene::StageSelectScene(GameObject* parent)
	: GameObject(parent, "StageSelectScene"),hPict_{-1,-1,-1,-1},hPict_2(-1),count(0),posX(-0.8 ,0 ,0)
{
}

//������
void StageSelectScene::Initialize()
{
	for(int i = 0; i < 4; i++)
	{
		/*switch (i)
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		*/

		hPict_[i] = Image::Load("Stage01.png");
		transform_.scale_ = { 0.4,0.4,0.4 };
	}
	hPict_2 = Image::Load("Cursor.png");
	transform_.scale_ = { 0.4, 0.4, 0.4 };
	CursorTransform_.position_ = {0,0,0};
	
	//���̐��l�������镶����B����Ȃ��B
	pText = new Text;
	pText->Initialize();
}

//�X�V
void StageSelectScene::Update()
{
	//A/���@���������Ƃ�
	if (Input::IsKeyDown(DIK_RIGHT))
	count -= 1;

	//D/���@���������Ƃ�
	if (Input::IsKeyDown(DIK_LEFT))
	count += 1;

	switch (count)
	{
	case 0:
		posX.x = -0.8;
		if (Input::IsKeyDown(DIK_SPACE)) {
			SceneManager* sm = (SceneManager*)FindObject("SceneManager");
			sm->ChangeScene(SCENE_ID_PLAY, TID_BLACKOUT);
		}
		break;

	case 1:
		posX.x = -0.3;
		if (Input::IsKeyDown(DIK_SPACE)) {
			SceneManager* sm = (SceneManager*)FindObject("SceneManager");
			sm->ChangeScene(SCENE_ID_PLAY, TID_BLACKOUT);
		}
		break;

	case 2:
		posX.x = 0.2;
		if (Input::IsKeyDown(DIK_SPACE)) {
			SceneManager* sm = (SceneManager*)FindObject("SceneManager");
			sm->ChangeScene(SCENE_ID_PLAY, TID_BLACKOUT);
		}
		break;

	case 3:
		posX.x = 0.7;
		if (Input::IsKeyDown(DIK_SPACE)) {
			SceneManager* sm = (SceneManager*)FindObject("SceneManager");
			sm->ChangeScene(SCENE_ID_PLAY, TID_BLACKOUT);
		}
		break;

		//���̉��̓J�[�\���̈ړ����킩��₷���������
	case 4:
		count = 0;
		break;

	case -1:
		count = 3;
		break;
	}

	//�����ŃP�[�X�ɂ���Đݒ肳�ꂽ���W���L�^�A���f�����
	transform_.position_ = posX;
	Image::SetTransform(hPict_2, transform_);
}

//�`��
void StageSelectScene::Draw()
{
	for (int i = 0; i < 4; i++) {
		//transform�̌v�Z���@�y��ʍ��[(-1)�A�]��(0.2)�A�ړ���(i*0.5)�z
		transform_.position_.x = -1 + 0.2 + i * 0.5;
		Image::SetTransform(hPict_[i],transform_);
		Image::Draw(hPict_[i]);
	}


	Image::Draw(hPict_2);
	//���̒l��\�����Ă����B����Ȃ��B
	pText->Draw(30, 30, count);
}

//�J��
void StageSelectScene::Release()
{
}
