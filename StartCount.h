#pragma once
#include "Engine/GameObject.h"

//�O���錾
class Timer;

class StartCount : public GameObject
{
private:
	int hPict_[4];	//�摜�ԍ�
	bool isfinished_;	//�I���������ǂ���
	Timer* pTimer_;	//�^�C�}�[

public:
	//�R���X�g���N�^
	StartCount(GameObject* obj);
	//�p��{������,�X�V,�`��,�J��}
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Release()override;

	/// <summary>
	/// �I���������ǂ�����Ԃ��֐�
	/// </summary>
	/// <returns>�I��������true</returns>
	bool IsFinished();

	/// <summary>
	/// �^�C�}�[���O�ɂ��A�ēx�J�n
	/// </summary>
	void Start();
private:
	/// <summary>
	/// �J�n�J�E���g��`�悷��
	/// </summary>
	/// <param name="time">����(�b)</param>
	void CountDraw(int time);

};