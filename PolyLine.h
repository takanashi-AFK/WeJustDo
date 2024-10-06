#pragma once
#include <list>
#include "Engine/Direct3D.h"
#include "Engine/Texture.h"
#include <DirectXMath.h>
#include <string>
using namespace DirectX;
using namespace std;

//�R���X�^���g�o�b�t�@�[
struct CONSTANT_BUFFER1
{
	XMMATRIX	matWVP;
	XMFLOAT4	color;
};

//���_���
struct VERTEX1
{
	XMFLOAT3 position;
	XMFLOAT3 uv;
};


class PolyLine
{
	 float WIDTH_;		//����
	int LENGTH_;		//����



	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	Texture* pTexture_;	//�摜


	list<XMFLOAT3> positions_;	//�ߋ�length_�񕪂̈ʒu

public:
	//�R���X�g���N�^
	PolyLine();

	/// <summary>
	/// �������̃R���X�g���N�^
	/// </summary>
	/// <param name="_width">��</param>
	/// <param name="_length">����</param>
	PolyLine(float _width, float _length);


	//���݂̈ʒu���L��������
	//�����Fpos	���݂̈ʒu
	void AddPosition(XMFLOAT3 pos);

	//���[�h
	//�����FfileName	�摜�t�@�C����
	//�ߒl�F����/���s
	HRESULT Load(std::string fileName);

	//�`��
	void Draw();

	//���
	void Release();

};