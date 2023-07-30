#pragma once
#include "Engine/GameObject.h"
#include <string>

class Stage;

/// <summary>
/// ���삷��3D�L�����N�^�[�I�u�W�F�N�g�̊��N���X
/// Player
/// </summary>
class Character : public GameObject
{
protected:
	///// -�L�����N�^�[�̕ێ�������- ////////////////////
	int hModel_;				//���f���ԍ�
	std::string modelFilePath_;	//���f���t�@�C���̃p�X
	XMVECTOR normal_;			//�L�����N�^�[���牺�����ɐL�т�@��
	Stage* pStage_;				//�X�e�[�W�̏��
	int hStageModel_;			//�X�e�[�W�̃��f���ԍ�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	Character(GameObject* _parent,std::string _modelFilePath);

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �J��
	/// </summary>
	void Release() override;

	/// <summary>
	/// �p����p��Update
	/// </summary>
	virtual void ChildUpdate() {};

	/// <summary>
	/// �p����p�̏�����
	/// </summary>
	virtual void ChildInitialize() {};

	/// <summary>
	/// �p����p�̕`��
	/// </summary>
	virtual void ChildDraw() {};

	/// <summary>
	/// �p����p�̊J��
	/// </summary>
	virtual void ChildRelease() {};

	/// <summary>
	/// �n�`���ɍ��킹���p���ɒ���
	/// </summary>
	virtual void TerrainAlign();

	/// <summary>
	/// �L�����N�^�[�̖@����ݒ�
	/// </summary>
	/// <param name="nor">�@�����</param>
	void SetNormal(const XMVECTOR& _n) { normal_ = _n; }

	/// <summary>
	/// �L�����N�^�[�̖@�����擾
	/// </summary>
	/// <returns>�L�����N�^�[�̖@��</returns>
	XMVECTOR GetNormal() { return normal_; }

	/// <summary>
	/// ���f���ԍ����擾
	/// </summary>
	/// <returns>���f���ԍ�</returns>
	int GetModelHandle() { return hModel_; }

};

