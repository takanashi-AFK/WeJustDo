#pragma once
#include "GameObject.h"

/// <summary>
/// ���̓I�ȃI�u�W�F�N�g�̊��N���X
/// </summary>
class SolidObject :public GameObject
{
protected:
	//���ʂ�����		///////////////////

	int hModel_;                     //���f���ԍ�
	std::string modelFileName_;      //�t�@�C���l�[���p�X
public:
	// �R���X�g���N�^
	SolidObject(GameObject* _parent, string _modelFileName, string name);

	// �f�X�g���N�^
	~SolidObject();

	// {�������E�X�V�E�`��E�J��}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	// {�������E�X�V�E�`��E�J��}<�p����p>
	virtual void ChildInitialize() {};
	virtual void ChildUpdate() {};
	virtual void ChildDraw() {};
	virtual void ChildRelease() {};

	/// <summary>
	/// ���f���ԍ����擾����
	/// </summary>
	/// <returns>���f���ԍ�</returns>
	int GetModelHandle() { return hModel_; }
};

//���̓I�ȃI�u�W�F�N�g�̐���
template <class T>
T* CreateSolidObject(GameObject* _parent, string _modelFileName)
{
	T* newObject = new T(_parent,_modelFileName);
	if (_parent != nullptr)
	{
		_parent->PushBackChild(newObject);
	}
	newObject->Initialize();
	return newObject;
}