#pragma once
#include "Engine/Gameobject.h"
#include <vector>

enum ModelName {
	m_Ground,
	m_Block,
	m_Firewood,
};

class Player;

/// <summary>
/// �v���C���A�Q�[����ʏ�ɕ\�������X�e�[�W�I�u�W�F�N�g
/// </summary>
class Stage : public GameObject
{
private:
	vector<int> StageModelList_;
	vector<vector<int>> ItemPlacement_;

	int hFirewood_;
	int iP_Height_;
	int iP_Width_;
public:
	//�R���X�g���N�^
	Stage(GameObject* parent);
	
	//�p��{�X�V�E�`��}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	/// <summary>
	/// �X�e�[�W�ɓo�^����Ă��邷�ׂẴ��f�����擾����
	/// </summary>
	/// <returns>�o�^�X�e�[�W�ԍ����X�g</returns>
	vector<int> GetAllStageModelHandle() { return StageModelList_; }

	/// <summary>
	/// �X�e�[�W�Ƀ��f����o�^����
	/// </summary>
	/// <param name="_hModel">�o�^���郂�f���ԍ�</param>
	void SetStageModel(int _hModel) { StageModelList_.push_back(_hModel); }

	/// <summary>
	/// �X�e�[�W�ɓo�^����Ă������̃��f���ԍ����擾����
	/// </summary>
	/// <param name="_hModel">���f��</param>
	/// <returns>���f���ԍ�</returns>
	int GetStageModelHandle(int _hModel) { return StageModelList_[_hModel]; }

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
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="_hItem"></param>
	void SetItem(int x, int y, int _hItem);
	void SetItem(float x, float y, int _hItem);




};

