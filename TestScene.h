#pragma once
#include "Engine/GameObject.h"

class Player;
class Stage;
//�e�X�g�V�[�����Ǘ�����N���X
class TestScene : public GameObject
{
	Player* pPlayer_;
	Stage* pStage_;
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