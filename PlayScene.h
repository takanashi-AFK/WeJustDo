#pragma once

#include "Stage.h"
#include "Engine/GameObject.h"

//�O���錾
class CountDown;
class Timer;

/// <summary>
/// �Q�[���v���C��ʂ�\������V�[���I�u�W�F�N�g
/// </summary>
class PlayScene : public GameObject
{
private:
	int hPict_;	//�摜�ԍ�
	int time;
	int hPict2_[4];
	bool flg =false;

	CountDown* pCount;
	Timer* pTimer;

public:
	//�R���X�g���N�^
	PlayScene(GameObject * parent);

	//�p��{�������E�X�V�E�`��E�J��}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	bool IsFinished() { return flg; };
};
