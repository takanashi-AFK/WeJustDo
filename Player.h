#pragma once
#include "Engine/SolidObject.h"

//�C���N���[�h
#include "PlayerStateManager.h"
#include "Engine/Model.h"
#include "PolyLine.h"
#include "Engine/VFX.h"

//�O���錾
class Stage;

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
	XMFLOAT3 RayStartPos;
	XMFLOAT3 downLandingPoint;
	XMFLOAT3 upLandingPoint;
	XMFLOAT3 rightLandingPoint;
	XMFLOAT3 leftLandingPoint;
	XMFLOAT3 PolyJetEmitPos;
	
	PolyLine* pJet;
	
	//ziro2
	int hBox_;
	int firewoodNum_;
protected:
///// �K�v�ȏ�� ////////////////////////////////////////
	PlayerStateManager*	pState_;	//Player�̏�ԊǗ�
	RayCastData	downData_;			//�v���C���[�̉��ɐL�т郌�C
	Stage* pStage_;					//�X�e�[�W�N���X�̃|�C���^
	int	hGroundModel_;				//�X�e�[�W�̃��f���ԍ�������ϐ�
	float acceleration_;			//�d�͂̉����x
	bool isAddGravity_;				//�d�͂������邩�ۂ�
	bool isJumpNow_;				//�W�����v�����ۂ�
	bool isMove_;					//�����Ă�������
	bool isJetNow_;
	float speed_;					//�ړ����x
public:
	EmitterData  RandEffectData_;
	EmitterData  DeadEffectData;
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

	/// <summary>
	/// �v���C���[�ƒn�`�̑��ݍ�p���L�q����֐�
	/// </summary>
	void TerrainInteraction();

	//�ݒ�F�v���C���[�̑��x
	void SetSpeed(float _s) { speed_ = _s; }

	//�擾�F�v���C���[�̑��x
	float GetSpeed() { return speed_; }
};
