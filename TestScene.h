#pragma once
#include "Engine/GameObject.h"
#include "Engine/VFX.h"

class Player;
class Stage;
//�e�X�g�V�[�����Ǘ�����N���X
class TestScene : public GameObject
{
	int hPict_;
	Player* pPlayer_;
	Stage* pStage_;

	int hEmit;
	EmitterData data;
	
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