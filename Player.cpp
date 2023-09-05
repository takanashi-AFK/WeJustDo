#include "Player.h"

//�C���N���[�h
#include "Engine/Input.h"
#include "Stage.h"
#include "Engine/Transition.h"
#include "Engine/Image.h"
#include "Engine/Debug.h"
#include "Engine/Camera.h"
#include "AudioManager.h"

//�R���X�g���N�^
Player::Player(GameObject* _parent, string _modelFileName)
	:SolidObject(_parent,_modelFileName,"Player"),
	pState_(nullptr), underRay_(),pStage_(),hGroundModel_(0),acceleration_(0)
{
	//�v���C���[�̏�Ԃ��u������ԁv�ŏ�����
	ASSIGN(pState_,new PlayerStateManager);
}

//������
void Player::ChildInitialize()
{
	//��Ԃ̏�����
	ASSIGN(pState_->playerState_, pState_->pStanding_);
	
	//���f���̃��[�h
	ASSIGN(Marker, Model::Load("Models/debugMarker.fbx"));
	ASSIGN(ziro, Model::Load("Models/ziro_move.fbx"));

	Model::SetAnimFrame(ziro, 0, 44, 1);

	//�ʒu�̏�����
	transform_.position_.y = 2;

	//������Ԃ̊J�n����
	pState_->Enter(this);

	isMove_ = true;

	pJet = new PolyLine(0.1,10);
	pJet->Load("Effects/Fire.png");

	InitDeadEffect();
	InitRandEffect();

	//pDead = new PolyLine(1,50);
	//pDead->Load("Effects/Tex.png");
	pJet = new PolyLine(0.1, 10);
	pJet->Load("Effects/Fire.png");

	//jump���̏������s��
	if (isJumpNow_) {transform_.position_.y += 0.1f;
	}

	//�d�͂�������
	AddGravity(&transform_);

	//�X�e�[�W�Ƃ̂����蔻��
	StageRayCast();

	//��Ԃ��Ƃ̍X�V
	pState_->Update(this);
}

void Player::ChildUpdate()
{
}

//�J��
void Player::ChildRelease()
{
	SAFE_DELETE(pState_);
	//�|�����C�����
	pJet->Release();
}

//�`��
void Player::ChildDraw()
{
	//���C�̃X�^�[�g�ʒu��`��
	Transform t;
	t.position_ = RayStartPos;
	t.position_.z -= 0.5f;
	Model::SetTransform(Marker, t);
	Model::Draw(Marker);

	//���n�_��`��
	Transform d;
	d.position_ = downLandingPoint;
	Model::SetTransform(Marker, d);
	Model::Draw(Marker);

	Transform up;
	up.position_ = upLandingPoint;
	Model::SetTransform(Marker, up);
	Model::Draw(Marker);

	Transform rg;
	rg.position_ = rightLandingPoint;
	Model::SetTransform(Marker, rg);
	Model::Draw(Marker);

	Transform lf;
	lf.position_ = leftLandingPoint;
	Model::SetTransform(Marker, lf);
	Model::Draw(Marker);

	Transform z;
	z.position_ = transform_.position_;
	z.position_.y -= 0.5;
	z.scale_ = { 0.1f,0.1f,0.1f };
	Model::SetTransform(ziro, z);
	Model::Draw(ziro);

	Direct3D::SetShader(Direct3D::SHADER_UNLIT);
}

void Player::PolyDraw()
{
	if (isJetNow_ == true)
	{
		//�|�����C����`��
		pJet->Draw();
	}
}

void Player::StageRayCast()
{
	//�X�e�[�W�̃��f���ԍ����擾
	ASSIGN(hGroundModel_,dynamic_cast<SolidObject*>((Stage*)FindObject("Stage"))->GetModelHandle());

	//�������̓����蔻��
	{
		RayCastData leftData; {
			leftData.start = transform_.position_;
			RayStartPos = leftData.start;
			XMStoreFloat3(&leftData.dir, XMVectorSet(-1, 0, 0, 0));
			Model::RayCast(hGroundModel_, &leftData);
			leftLandingPoint = leftData.pos;
		}
		if (leftData.dist < (PLAYER_MODEL_SIZE.x / 2)) {
			//�߂荞�ݕ��A�ʒu��߂�
			XMVECTOR length = { -leftData.dist - (PLAYER_MODEL_SIZE.x / 2),0,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(-1, 0, 0, 0) - length));
		}
	}

	//�E�����̂����蔻��
	{
		RayCastData rightData; {
			//�������Ă��邩���m�F
			rightData.start = transform_.position_;					//���ˈʒu�̎w��
			XMStoreFloat3(&rightData.dir, XMVectorSet(1, 0, 0, 0));	//���˕����̎w��
			Model::RayCast(hGroundModel_, &rightData);				//���C�𔭎�
			rightLandingPoint = rightData.pos;
		}
		//���C�̒�����1.0�ȉ���������...
		if (rightData.dist < (PLAYER_MODEL_SIZE.x / 2)) {
			//�߂荞�ݕ��A�ʒu��߂�
			XMVECTOR length = { rightData.dist + (PLAYER_MODEL_SIZE.x / 2),0,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(1, 0, 0, 0) - length));
		}
	}

	//������̂����蔻��
	{
		RayCastData upData; {
			//�������Ă��邩�m�F
			upData.start = transform_.position_;
			XMStoreFloat3(&upData.dir, XMVectorSet(0, 1, 0, 0));
			Model::RayCast(hGroundModel_, &upData);
			upLandingPoint = upData.pos;
		}
		//���C�̒�����1.0�ȉ���������...
		if (upData.dist < (PLAYER_MODEL_SIZE.y / 2)) {
			//�߂荞�ݕ��A�ʒu��߂�
			XMVECTOR length = { 0, (PLAYER_MODEL_SIZE.y / 2) + upData.dist,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(0, 1, 0, 0) - length));
			SetAcceleration(2);
		}
	}

	//StandingState,RunningState�Ƃ��̂ݍs������State���ŏ������s��
	//�������̂����蔻��
	{
		RayCastData downData; {
			//�������Ă��邩�m�F
			downData.start = transform_.position_;
			XMStoreFloat3(&downData.dir, XMVectorSet(0, -1, 0, 0));
			Model::RayCast(hGroundModel_,&downData);
			downLandingPoint = downData.pos;
		}
		if (downData.dist < (PLAYER_MODEL_SIZE.y / 2)) {
			//��Ԃ�"Standing"�ɕύX
			pState_->ChangeState(pState_->pStanding_, this);
		}
	}
}

void Player::AddGravity(Transform* _transform)
{
	if (!isAddGravity_)return;

	//�d�͂�������
	_transform->position_ = Transform::Float3Add(_transform->position_, VectorToFloat3((XMVectorSet(0, -1, 0, 0) / 10) * acceleration_));
	acceleration_ += GRAVITY_ADDITION;
}

void Player::InitDeadEffect()
{
	DeadEffectData.textureFileName = "Effects/cloudA.png";
	DeadEffectData.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	DeadEffectData.delay = 0;
	DeadEffectData.number = 1;
	DeadEffectData.lifeTime = 60;
	DeadEffectData.gravity = -0.002f;
	DeadEffectData.direction = XMFLOAT3(0, 1, 0);
	DeadEffectData.directionRnd = XMFLOAT3(0, 0, 0);
	DeadEffectData.speed = 0.01f;
	DeadEffectData.speedRnd = 0.0;
	DeadEffectData.size = XMFLOAT2(1, 10);
	DeadEffectData.sizeRnd = XMFLOAT2(0.4, 0.4);
	DeadEffectData.scale = XMFLOAT2(1.01, 1.01);
	DeadEffectData.color = XMFLOAT4(0, 0, 1, 1);
	DeadEffectData.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);
}

void Player::InitRandEffect()
{
	RandEffectData_.textureFileName = "Effects/RandSmoke2.png";
	RandEffectData_.position = XMFLOAT3(transform_.position_.x, transform_.position_.y - 0.2, 0);
	RandEffectData_.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	RandEffectData_.delay = 0;
	RandEffectData_.number = 1;
	RandEffectData_.lifeTime = 40;
	RandEffectData_.speed = 0.01f;
	RandEffectData_.speedRnd = 0.0;
	RandEffectData_.size = XMFLOAT2(1, 0.5);
	RandEffectData_.scale = XMFLOAT2(1.01, 1.01);
	RandEffectData_.color = XMFLOAT4(1, 1, 1, 1);
	RandEffectData_.deltaColor = XMFLOAT4(0, 0, 0, -0.1);
}

EmitterData Player::GetDeadEData()
{
	return DeadEffectData;
}

EmitterData Player::GetRandEData()
{
	return RandEffectData_;
}

PolyLine Player::GetJettPData()
{
	return *pJet;
}

void Player::SetIsJetNow(bool _jet)
{
	isJetNow_ = _jet;
}

void Player::AllStageRayCast()
{
	//�X�e�[�W�̃��f���ԍ����X�g���擾
	vector<int> stageList = dynamic_cast<Stage*>((Stage*)FindObject("Stage"))->GetAllStageModelHandle();

	//���ׂẴ��f���Ƃ����蔻����s��
	for (vector<int>::iterator it = stageList.begin(); it != stageList.end(); ++it) {

		//�������̓����蔻��
		{
			RayCastData leftData; {
				leftData.start = transform_.position_;
				RayStartPos = leftData.start;
				XMStoreFloat3(&leftData.dir, XMVectorSet(-1, 0, 0, 0));
				Model::RayCast(*it, &leftData);
				leftLandingPoint = leftData.pos;
			}
			if (leftData.dist < (PLAYER_MODEL_SIZE.x / 2)) {
				//�߂荞�ݕ��A�ʒu��߂�
				XMVECTOR length = { -leftData.dist - (PLAYER_MODEL_SIZE.x / 2),0,0 };
				XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(-1, 0, 0, 0) - length));
			}
		}

		//StandingState,RunningState�Ƃ��̂ݍs������State���ŏ������s��
		//�������̂����蔻��
		{
			RayCastData downData; {
				//�������Ă��邩�m�F
				downData.start = transform_.position_;
				XMStoreFloat3(&downData.dir, XMVectorSet(0, -1, 0, 0));
				Model::RayCast(hGroundModel_, &downData);
				downLandingPoint = downData.pos;
			}
			if (downData.dist < (PLAYER_MODEL_SIZE.y / 2)) {
				//��Ԃ�"Standing"�ɕύX
				pState_->ChangeState(pState_->pStanding_, this);

				//jump��Ԃ��I��
				isJumpNow_ = false;
			}
			else
				isAddGravity_ = true;

		}
	}
}
