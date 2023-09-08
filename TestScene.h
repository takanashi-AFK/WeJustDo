#pragma once
#include "Engine/GameObject.h"

//�O���錾
class Text;

//�e�X�g�V�[�����Ǘ�����N���X
class TestScene : public GameObject
{
	int flame_;
	Text* pText_;
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

	//flame_�̃Q�b�^�[�E�Z�b�^�[
	int GetFlame() { return flame_; }
	void SetFlame(int _f) { flame_ = _f; }
	void SetSeconds(int _s) { flame_ = _s * 60; }
};