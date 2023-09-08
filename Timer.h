#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

class Timer : public GameObject
{
private:
	int frame;
	int flimit;
	bool active;
	bool limitActive;
	int drawX;
	int drawY;

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
	void TimeLimitStart();

	//�^�C�}�[�ꎞ��~
	void Stop();
	void TimeLimitStop();

	//�I�������
	bool IsFinished();
	bool IsLimitEnd();

	int GetTime() { return frame/60; };
};