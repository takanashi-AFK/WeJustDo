#pragma once
#include "Engine/GameObject.h"
class TestPlayer: public GameObject
{
private:
	int hModel_;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	TestPlayer(GameObject* parent);

	//GameObject�p�����\�b�h
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

};

