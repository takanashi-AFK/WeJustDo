#pragma once
#include "Engine/GameObject.h"

//�O���錾
class Text;

class Timer : public GameObject
{
private:
	int frame_;	//����(�t���[��)
	bool limitActive_;//�J�E���g�_�E�����s�����ǂ���
	bool countActive_;//�J�E���g�A�b�v���s�����ǂ���
	
	Text* pText_;	//�e�L�X�g
	int hTimerFlame_;	//�摜

	int drawPosX_;//�`��ʒuX
	int drawPosY_;//�`��ʒuY
	float drawSize_;//�`��T�C�Y

	bool isDraw_;	//�`��t���O
public:
	//�R���X�g���N�^
	Timer(GameObject* obj);
	
	//�p��{������,�X�V,�`��,�J��}
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Release()override;

	/// <summary>
	/// �^�C�}�[���J�n
	/// </summary>
	/// <param name="_flag">true(�J�E���g�_�E��),false(�J�E���g�A�b�v)</param>
	void Start(bool _flag);

	/// <summary>
	/// �^�C�}�[���~
	/// </summary>
	/// <param name="_flag">true(�J�E���g�_�E��),false(�J�E���g�A�b�v)</param>
	void Stop(bool _flag);
	
	/// <summary>
	/// �J�E���g�_�E�����I���������ǂ�����Ԃ��֐�
	/// </summary>
	/// <returns>�I�����Ă�����true</returns>
	bool IsFinished();

	/// <summary>
	/// �J�E���g�A�b�v���I���������ǂ�����Ԃ��֐�
	/// </summary>
	/// <param name="_s">�I������</param>
	/// <returns>�I�����Ă�����true</returns>
	bool IsFinished(int _s);


public:
	//�擾�F�^�C�}�[�̓�����
	bool isMove() { return limitActive_ || countActive_; }

	//�擾�F����(�t���[��)
	int GetTime_Frame() { return frame_; }

	//�擾�F����(�b)
	int GetTime_Seconds() { return frame_ / 60; }

	//�ݒ�F����(�t���[��)
	void SetTime_Frame(int _f) { frame_ = _f; }

	//�ݒ�F����(�b)
	void SetTime_Seconds(int _s) { frame_ = _s * 60; }

	//�ݒ�F�`��ʒu
	void SetDrawPosition(int _x, int _y) { drawPosX_ = _x; drawPosY_ = _y; }
	
	//�ݒ�F�`��ʒu(x���W)
	void SetDrawPositionX(int _x) { drawPosX_ = _x; }

	//�ݒ�F�`��ʒu(y���W)
	void SetDrawPositionY(int _y) { drawPosX_ = _y; }

	//�擾�F�`��T�C�Y
	float GetDrawSize() { return drawSize_; }

	//�ݒ�F�`��T�C�Y
	void SetDrawSize(float _size);

	//�ݒ�F�^�C�}�[��\�����邩�ǂ���
	void IsDraw(bool _flag) { isDraw_ = _flag; }

};