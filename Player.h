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
private:
	//debug
	int Marker;
	int DeadEffHandle;
	int nowFireWood;
	int maxFireWood;
	XMFLOAT3 RayStartPos;
	XMFLOAT3 downLandingPoint;
	XMFLOAT3 upLandingPoint;
	XMFLOAT3 rightLandingPoint;
	XMFLOAT3 leftLandingPoint;
	XMFLOAT3 PolyJetEmitPos;
	
	PolyLine* pJet;
	FuelGauge* pGauge;
	
	//ziro2
	int hBox_;
	int firewoodNum_;
protected:
	///// �K�v�ȏ�� ////////////////////////////////////////
	PlayerStateManager* pState_;	//Player�̏�ԊǗ�

	///// �����蔻�� ////////////////////////////////////////
	RayCastData downData_;	//�v���C���[�̉��ɐL�т郌�C
	Stage* pStage_;		//�X�e�[�W�N���X�̃|�C���^
	int			hGroundModel_;	//�X�e�[�W�̃��f���ԍ�������ϐ�
	float		acceleration_;	//�d�͂̉����x
	bool		isAddGravity_;	//�d�͂������邩�ۂ�
	bool		isJumpNow_;		//�W�����v�����ۂ�
	bool		isMove_;		//�����Ă�������
	bool		isJetNow_ = false;
public:
	
	EmitterData  RandEffectData_;
	
	EmitterData  DeadEffectData;
	
	//�R���X�g���N�^
	Player(GameObject* _parent, string _modelFileName);

	//�p��{�������E�X�V�E�`��E�J��}
	void ChildInitialize() override;
	void ChildUpdate() override;
	void ChildRelease() override;
	void ChildDraw() override;

	void PolyDraw() override;
	void SetDrawTransform() override;
	///// �K�v�Ȋ֐� //////////////////////////////////////// 

	/// <summary>
	/// �v���C���[�����肷��X�e�[�W�̃��f���ԍ����擾
	/// </summary>
	/// <returns>�X�e�[�W�̃��f���ԍ�</returns>
	int GetPlayerOnGround() { return hGroundModel_; }

	/// <summary>
	/// ��Ԃ��擾
	/// </summary>
	/// <returns>���</returns>
	PlayerStateManager* GetState() { return pState_; };


	/// <summary>
	/// �X�e�[�W�Ƃ̐ڐG���菈�����s��
	/// </summary>
	void StageRayCast();

	/// �d�͂��Z�b�g
	/// </summary>
	/// <param name="acceleration">�Z�b�g�������d�͂̒l</param>
	void SetAcceleration(const float& acceleration) { acceleration_ = acceleration; }

	/// <summary>
	/// �d�͂������邩�ǂ�����ݒ�
	/// </summary>
	/// <param name="_flag">������Ȃ�true</param>
	void IsAddGravity(bool _flag) { isAddGravity_ = _flag; }

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
	/// �����Ă������ǂ�����ݒ肷��
	/// </summary>
	/// <param name="_flag">����</param>
	void SetIsMove(bool _flag) { isMove_ = _flag; }

	/// <summary>
	/// ���S���G�t�F�N�g�̏�����
	/// </summary>
	void InitDeadEffect();

	/// <summary>
	/// ���n���G�t�F�N�g�̏�����
	/// </summary>
	void InitRandEffect();

	float GetAccelaration() { return acceleration_; }


	/// <summary>
	/// ���S���G�t�F�N�g�f�[�^��Ԃ�
	/// </summary>
	/// <returns>���S���G�t�F�N�g�f�[�^��Ԃ�</returns>
	EmitterData GetDeadEData();
	
	/// <summary>
	/// ���n���G�t�F�N�g�f�[�^��Ԃ�
	/// </summary>
	/// <returns>���n���G�t�F�N�g�f�[�^</returns>
	EmitterData GetRandEData();

	/// <summary>
	/// �W�F�b�g��polyline�f�[�^��Ԃ�
	/// </summary>
	/// <returns>�W�F�b�g��polyline�f�[�^</returns>
	PolyLine GetJettPData();
	
	void SetIsJetNow( bool _jet);

	/// <summary>
	/// ���ɐL�т郌�C�L���X�g�����擾
	/// </summary>
	/// <returns>���C�L���X�g���</returns>
	RayCastData GetDownData() { return downData_; }

	void GetFirewood();

	int GetFirewoodNum() { return firewoodNum_; }
	void SetFirewoodNum(int _n) { firewoodNum_ = _n; }
};
