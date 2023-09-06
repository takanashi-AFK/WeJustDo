#include "sceneManager.h"

//�V�[���I�u�W�F�N�g
#include "../SplashScene.h"
#include "../TitleScene.h"
#include "../StageSelectScene.h"
#include "../PlayScene.h"
#include "../ResultScene.h"
#include "../TestScene.h"

#include "Model.h"
#include "Image.h"
#include "Audio.h"


//�R���X�g���N�^
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{
}

//������
void SceneManager::Initialize()
{
	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}

//�X�V
void SceneManager::Update()
{
	//�g�����W�V�������s���A�V�[���ؑւ̃^�C�~���O�ŃV�[����ύX����
	if (Transition::IsChangePoint())nextSceneID_ = tmpID_;

	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_)
	{
		//���̃V�[���̃I�u�W�F�N�g��S�폜
		KillAllChildren();

		//���[�h�����f�[�^��S�폜
		Audio::Release();
		Model::AllRelease();
		Image::AllRelease();

		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST: Instantiate<TestScene>(this); break;
		case SCENE_ID_SPLASH: Instantiate<SplashScene>(this); break;
		case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
		case SCENE_ID_SELECT: Instantiate<StageSelectScene>(this); break;
		case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
		case SCENE_ID_RESULT: Instantiate<ResultScene>(this); break;
		}

		Audio::Initialize();
		currentSceneID_ = nextSceneID_;
	}
}

//�`��
void SceneManager::Draw()
{
}

//�J��
void SceneManager::Release()
{
}

//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
void SceneManager::ChangeScene(SCENE_ID next, TRANSITION_ID _type,float _time)
{
	//�g�����W�V���������쒆�̓V�[���J�ڂ��s��Ȃ�
	if (!Transition::IsActive()) {
		//�g�����W�V�������g��Ȃ��ꍇ�A�V�[��ID���Z�b�g
		if (!Transition::SetTransition(_type))nextSceneID_ = next;
		
		//���Ԃ��Z�b�g
		Transition::SetTime(_time);

		//�g�����W�V�������J�n���A�V�[��ID���Z�b�g
		Transition::Start();tmpID_ = next;
	}
}
void SceneManager::ChangeScene(SCENE_ID next, TRANSITION_ID _type){ChangeScene(next, _type, 2);}
void SceneManager::ChangeScene(SCENE_ID next){ChangeScene(next, TID_NONE);}


