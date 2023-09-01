#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// �Q�[���v���C��ʂ�\������V�[���I�u�W�F�N�g
/// </summary>
class PlayScene : public GameObject
{
private:
	int hPict_;	//�摜�ԍ�
	bool isCount;

public:
	//�R���X�g���N�^
	PlayScene(GameObject * parent);

	//�p��{�������E�X�V�E�`��E�J��}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	bool CountFinish() { return (isCount); };

};