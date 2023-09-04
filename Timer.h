#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

class Timer : public GameObject
{
private:
	int frame;
	bool active;
	int drawX;
	int drawY;
	int hPict_[4];
	int hPict2_;

	Text* num;
	Transform pictPos;
public:
	Timer(GameObject* obj);
	~Timer();
	//Timer�̃C�j�V�����C�Y
	void Initialize()override;

	//�^�C�}�[���X�^�[�g���Ă�����ݒ莞�ԃJ�E���g�_�E������
	void Update()override;

	//�c�莞�Ԃ�\�����܂�
	void Draw()override;

	void Release()override;

	//�������Ԃ��y�b�z�œ��͂��܂��B
	void SetLimit(float seconds);

	//�^�C�}�[�J�n
	void Start();

	//�^�C�}�[�ꎞ��~
	void Stop();

	//�I�������
	bool IsFinished();

	//�摜�\��
	void CountDown();
};