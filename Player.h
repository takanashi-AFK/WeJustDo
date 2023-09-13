#pragma once
#include "Engine/SolidObject.h"

//�C���N���[�h
#include "PlayerStateManager.h"
#include "Engine/Model.h"
#include "PolyLine.h"
#include "Engine/VFX.h"

//�O���錾
class Stage;
class FuelGauge;

//�萔�錾
namespace {
	//�d�͂̉��Z�l
	static const float GRAVITY_ADDITION = 0.06f;

	//Player�̃��f���̑傫��
	static const XMFLOAT3 PLAYER_MODEL_SIZE = { 1.0f,1.0f,1.0f };
}

/// <summary>
/// �Q�[�����A��ʏ�ɕ\�������v���C���[�I�u�W�F�N�g
/// </summary>
class Player : public SolidObject
{
///// �K�v�ȏ�� ////////////////////////////////////////
private:
	int hDebugBox_;	//���f���ԍ�(DebugBox)
	PolyLine* pJet;//�W�F�b�g�G�t�F�N�g�̃|�����C���f�[�^
	Transform currentPos_;	//�v���C���[�̑O�t���[���̈ʒu
protected:
	PlayerStateManager*	pState_;	//Player�̏�ԊǗ�
	RayCastData	downData_;			//�v���C���[�̉��ɐL�т郌�C
	Stage* pStage_;					//�X�e�[�W�N���X�̃|�C���^
	FuelGauge* pGauge_;				//�Q�[�W�N���X�̃|�C���^
	Transform cameraTrans_;			//�J�����̍��W
	int	hGroundModel_;				//�X�e�[�W�̃��f���ԍ�������ϐ�
	float acceleration_;			//�d�͂̉����x
	bool isAddGravity_;				//�d�͂������邩�ۂ�
	bool isMove_;					//�����Ă�������
	float speed_;					//�ړ����x

	const float defCamY = 4.5f;		//�J����Y�̃f�t�H���g�l�y�Zm�z
	const float defCamZ = -13.0f;	//�J����Z�̃f�t�H���g�l�y�Zm�z
	const float maxCamY = 8.5f;		//�J����Y���W�̍ő�l�y�Zm�z
	const float stageBottom = 1;	//�X�e�[�W�̒�y�Zm�z�i���̒l���傫���ƃJ�����������ԋ߂��Ȃ�܂��B�j
	const float camZBottom = 4.5f;	//�J����Z���y�Zm�z�K�������@�J���������������ăX�e�[�W�̒ꂪ�����Ȃ��悤�ɂ��܂��B
	const int maxfireWood_ = 100;	//�d�̔R�₹�鐔�i100���j
public:
	EmitterData  RandEffectData_;	//�G�t�F�N�g�f�[�^(���n��)
	EmitterData  DeadEffectData;	//�G�t�F�N�g�f�[�^(���S��)
	EmitterData PlusOneEffectData;	//�G�t�F�N�g�f�[�^(�d(�A�C�e��)�擾��)
	EmitterData  ItemGetEffectData;
	EmitterData bombEffectData;
/////////////////////////////////////////////////////////

public:
	//�R���X�g���N�^
	Player(GameObject* _parent, string _modelFileName);

	//�p��{�������E�X�V�E�`��Eeffect�`��ESolidObject�`��E�J��}
	void ChildInitialize() override;
	void ChildUpdate() override;
	void ChildDraw() override;
	void PolyDraw() override;
	void SetDrawTransform() override;
	void ChildRelease() override;

	/// <summary>
	/// �X�e�[�W�Ƃ̐ڐG���菈�����s��
	/// </summary>
	void StageRayCast();

	/// <summary>
	/// �d�͂�������
	/// </summary>
	void AddGravity(Transform* _transform);

	/// <summary>
	/// �����Ă������ǂ�����Ԃ�
	/// </summary>
	/// <returns>�����ėǂ����true</returns>
	bool IsMove() { return isMove_; }

	/// <summary>
	/// ����ł��邩�ǂ�����Ԃ�
	/// </summary>
	/// <returns>����ł����true</returns>
	bool isDead() { return pState_->playerState_ == pState_->pDead_; }

	/// <summary>
	/// �S�[�����B�n�_�ɓ��B���Ă��邩�ǂ�����Ԃ�
	/// </summary>
	/// <returns>�S�[���n�_�ɓ��B���Ă����true</returns>
	bool isGoal();

	/// <summary>
	/// �v���C���[�ƒn�`�̑��ݍ�p���L�q����֐�
	/// </summary>
	void TerrainInteraction();

	/// <summary>
	/// �d(�A�C�e��)�擾���ɋN���鏈�����s��
	/// </summary>
	void OnWoodPickup(Stage* ps);

public:
// �Q�b�^�[�E�Z�b�^�[ //////////////////////////////
	
	//�擾�F�v���C���[������Ă���X�e�[�W�̃��f���ԍ�
	int GetPlayerOnGround() { return hGroundModel_; }

	//�擾�F�v���C���[�̏��
	PlayerStateManager* GetState() { return pState_; };

	//�ݒ�F�d�͉����x
	void SetAcceleration(const float& acceleration) { acceleration_ = acceleration; }
	
	//�擾�F�d�͉����x
	float GetAccelaration() { return acceleration_; }

	//�ݒ�F�d�͂������邩�ǂ���(������Ȃ�true)
	void IsAddGravity(bool _flag) { isAddGravity_ = _flag; }

	//�ݒ�F�����Ă������ǂ���(�����Ă����Ȃ�true)
	void SetIsMove(bool _flag) { isMove_ = _flag; }

	//�擾�F���ɐL�т郌�C�L���X�g���
	RayCastData GetDownData() { return downData_; }

	//�ݒ�F�v���C���[�̑��x
	void SetSpeed(float _s) { speed_ = _s; }

	//�擾�F�v���C���[�̑��x
	float GetSpeed() { return speed_; }

	//�ݒ�F�d(�A�C�e���̏�����)
	void SetFirewoodNum(int _n) { Global::gFireWood = _n; }

// effect ///////////////////////////////////

	/// <summary>
	/// ���S���G�t�F�N�g�̏�����
	/// </summary>
	void InitDeadEffect();

	void InitBombEffect();

	/// <summary>
	/// ���n���G�t�F�N�g�̏�����
	/// </summary>
	void InitRandEffect();

	/// <summary>
	/// �d(�A�C�e��)�擾��+1�̏�����
	/// </summary>
	void InitPlusOneEffect();

	/// <summary>
	/// �A�C�e���擾���L���L���̃G�t�F�N�g
	/// </summary>
	void InitGetEffect();

	//�擾�F���S���G�t�F�N�g�f�[�^
	EmitterData GetDeadEData() { return DeadEffectData; }
	
	//�擾�F���n���G�t�F�N�g�f�[�^
	EmitterData GetRandEData() { return RandEffectData_; }

	//�擾�FJetFire�̃|�����C���f�[�^
	PolyLine GetJettPData() { return *pJet; }

	/// <summary>
	/// �J������Y���W���v�Z���܂�
	/// </summary>
	/// <param name="_plPos">�v���C���[��Transform</param>
	/// /// <param name="_stageBottom">�n�ʂ̒��</param>
	/// <returns>position��Y���W�ɑ�����Ă�������</returns>
	float CalcCamPositionY(Transform _plPos);

	float CalcCamPositionZ(Transform _plPos);
};
