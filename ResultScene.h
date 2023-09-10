#pragma once
#include "Engine/GameObject.h"
#include "Engine/Global.h"

//�O���錾
class Text;

/// <summary>
/// �Q�[���I����A���ʂ�\������V�[���I�u�W�F�N�g
/// </summary>
class ResultScene : public GameObject
{
private:
	int hPict_;	//�摜�ԍ�

	int frameCount_;

	int iTimeScore_ = 123;
	int iFirewoodScore_ = 456;
	int iTotalScore_ = 789;

	Text* tTimeScore_;
	Text* tFirewoodScore_;
	Text* tTotalScore_;



public:
	//�R���X�g���N�^
	ResultScene(GameObject* parent);
	
	//�p��{�������E�X�V�E�`��E�J��}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override{}
};

