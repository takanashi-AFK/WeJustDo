#pragma once
#include "Engine/GameObject.h"

class Button : public GameObject
{
private:
	int hReleased_;		//���f���ԍ�(������Ă��Ȃ���Ԃ̉摜)
	int hPressed_;		//���f���ԍ�(������Ă����Ԃ̉摜)

	bool pushed_;		//������Ă��邩�ǂ���
	
	XMFLOAT3 center_;	//�摜�̒��S�_
	XMFLOAT3 size_;		//�摜�̃T�C�Y

	//����p�ϐ�
	XMFLOAT3 startPos_;	//����J�n�n�_
	XMFLOAT3 endPos_;	//����I���n�_
	float totalTime_;	//����ɂ����鍇�v����
	float currentTime_;	//�����_�̓��쎞��
public:
	//�R���X�g���N�^
	Button(GameObject* _parent);
	//�p��{������,�X�V,�`��,���}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override{}
public:
	//�ݒ�F�g�p����摜
	void SetImage(std::string _released, std::string _pressed);

	//�ݒ�F�z�u����ʒu
	void SetPosition(int _x, int _y);

	//�ݒ�F������Ă��邩�ǂ���
	void Push(bool _pushed);

	//����F�}�E�X�J�[�\���̈ʒu���摜�͈͓����ǂ���
	bool MouseInArea(XMFLOAT3 _mousePos);

	/// <summary>
	/// �ړ������鏈��
	/// </summary>
	/// <param name="_toX">�ړ���̍��Wx</param>
	/// <param name="_toY">�ړ���̍��Wy</param>
	/// <param name="_second">�ړ�����(�b)</param>
	void SetMovePosition(int _toX, int _toY, float _second);

	//�擾�F���쒆���ǂ���
	bool IsMoving();

	/// <summary>
	/// �����I�Ɉړ����I��������
	/// </summary>
	void ForceMoveEnd();
};

