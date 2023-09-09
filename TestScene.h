#pragma once
#include "Engine/GameObject.h"

class StartCount;
class Timer;

//�e�X�g�V�[�����Ǘ�����N���X
class TestScene : public GameObject
{
	bool isGameNow_;

	//�K�v�ȃI�u�W�F�N�g
	StartCount* pStartCount_;//Object-StartCount
	//UI-ItemCount
	Timer* pTimer_;//UI-TimeCount
	//UI-JetpackGauge
	//Object-Player
	//Object-Stage
	//Image-BackGround
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
};