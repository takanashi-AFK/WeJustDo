#pragma once
#include "Engine/GameObject.h"

class StartCount;
class Timer;
class ItemCounter;
class Stage;
class Player;

//�e�X�g�V�[�����Ǘ�����N���X
class TestScene : public GameObject
{
	bool isGameNow_;

	//�K�v�ȃI�u�W�F�N�g
	StartCount* pStartCount_;//Object-StartCount
	ItemCounter* pItemCounter_;//UI-ItemCount
	Timer* pTimer_;//UI-TimeCount
	//UI-JetpackGauge
	Player* pPlayer_;//Object-Player
	Stage* pStage_;//Object-Stage
	int hPict_;//Image-BackGround
	//Audio-PlaySceneMusic

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TestScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SceneReset();
};