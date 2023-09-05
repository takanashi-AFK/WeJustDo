#include "PlayScene.h"

//�C���N���[�h
#include "Player.h"
#include "Stage.h"
#include "Engine/Image.h"
#include "Engine/Camera.h"
#include "AudioManager.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene"),hPict_(-1)
{
}

//������
void PlayScene::Initialize()
{
	//�w�i�𐶐�
	ASSIGN(hPict_, Image::Load("Image/BackGround4.png"));{

	}

	//�X�e�[�W�𐶐�

	//�v���C���[�𐶐�
	CreateSolidObject<Player>(this, "DebugCollision/BoxCollider.fbx");{
	
	}
	//Instantiate<TestObj>(this);
	//BGM���Đ�

	AudioManager::Play_PlayMusic();
	

}

//�X�V
void PlayScene::Update()
{
	//static float time; time++;
	//if (time >= 600) {
	//	SceneManager* sm = (SceneManager*)FindObject("SceneManager");
	//	sm->ChangeScene(SCENE_ID_RESULT,TID_WHITEOUT);
	//}
}

//�`��
void PlayScene::Draw()
{
	//�w�i�摜��`��
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void PlayScene::Release()
{
}
