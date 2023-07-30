#pragma once
#include <DirectXMath.h>

using namespace DirectX;


//-----------------------------------------------------------
//�ʒu�A�����A�g�嗦�Ȃǂ��Ǘ�����N���X
//-----------------------------------------------------------
class Transform
{
public:
	XMMATRIX matTranslate_;	//�ړ��s��
	XMMATRIX matRotate_;	//��]�s��F�ʏ�
	XMMATRIX matScale_;		//�g��s��
	XMFLOAT3 position_;		//�ʒu
	XMFLOAT3 rotate_;		//����
	XMFLOAT3 scale_;		//�g�嗦
	
	bool useExistingMatRotate_;	//�ʏ�̉�]�s����g�����ǂ���
	XMMATRIX freeMatRotate_;

	Transform * pParent_;	//�e�I�u�W�F�N�g�̏��

	//�R���X�g���N�^
	Transform();

	//�f�X�g���N�^
	~Transform();

	//�e�s��̌v�Z
	//�����F�Ȃ�
	//�ߒl�F�Ȃ�
	void Calclation();

	//���[���h�s����擾
	//�����F�Ȃ�
	//�ߒl�F���̎��_�ł̃��[���h�s��
	XMMATRIX GetWorldMatrix();

	/// <summary>
	/// �e�̃��[���h�s����擾
	/// </summary>
	/// <returns>�e�̃��[���h�s��</returns>
	XMMATRIX GetParentWorldMatrix();

	static XMFLOAT3 Float3Add(XMFLOAT3 a, XMFLOAT3 b) {
		return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	
};

