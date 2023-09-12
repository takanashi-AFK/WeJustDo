#pragma once
#include "Engine/Gameobject.h"

//�C���N���[�h
#include <vector>

//���f���ԍ�
enum ModelName {
	m_Ground,
	m_Block,
	m_Firewood,
};

//�O���錾
class Player;

/// <summary>
/// �v���C���A�Q�[����ʏ�ɕ\�������X�e�[�W�I�u�W�F�N�g
/// </summary>
class Stage : public GameObject
{
private:
// �X�e�[�W��� //////////////////////////////////
	vector<int> StageModelList_;
	vector<vector<int>> ItemPlacement_;
	int iP_Height_;
	int iP_Width_;

// �A�C�e����� //////////////////////////////////

	int hFirewood_;	//���f���ԍ�(�X�e�[�W���Ƃ͈قȂ郂�m�̈�)

public:
	//�R���X�g���N�^
	Stage(GameObject* parent);
	
	//�p��{������.�X�V,�`��,�J��}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;


	/// <summary>
	/// Object�̈ʒu�Ɠ���̃A�C�e���̈ʒu���d�Ȃ��Ă�����
	/// </summary>
	/// <param name="_obj">�I�u�W�F�N�g�̃|�C���^</param>
	/// <param name="_hItem">�A�C�e��</param>
	/// <returns>�d�Ȃ��Ă�����true</returns>
	bool AtItem(GameObject* _obj, int _hItem);

	/// <summary>
	/// ����̈ʒu�̃A�C�e����ݒ肷��
	/// </summary>
	/// <param name="x">���Wx</param>
	/// <param name="y">���Wy</param>
	/// <param name="_hItem">�A�C�e���ԍ�</param>
	void SetItem(int x, int y, int _hItem);

public:
// �Q�b�^�[�E�Z�b�^�[ ///////////////////////////////////

	//�擾�F�X�e�[�W���Ƃ��ēo�^����Ă��邷�ׂẴ��f���ԍ�
	vector<int> GetAllStageModelHandle() { return StageModelList_; }

	//�ǉ��F�X�e�[�W���Ƀ��f���ԍ���������
	void AddStageModel(int _hModel) { StageModelList_.push_back(_hModel); }

	//�擾�F�X�e�[�W���Ƃ��ēo�^����Ă������̃��f���ԍ�
	int GetStageModelHandle(int _hModel) { return StageModelList_[_hModel]; }
};

