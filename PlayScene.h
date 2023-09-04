#pragma once

#include "Stage.h"
#include "Engine/GameObject.h"

class Timer;

/// <summary>
/// �Q�[���v���C��ʂ�\������V�[���I�u�W�F�N�g
/// </summary>
class PlayScene : public GameObject
{
private:
	int hPict_;	//�摜�ԍ�
	Timer* pTime;
	float timeLimit ;
	bool fin = false;

public:
	//�R���X�g���N�^
	PlayScene(GameObject * parent);

	//�p��{�������E�X�V�E�`��E�J��}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};
