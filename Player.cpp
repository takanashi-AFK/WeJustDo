#include "Player.h"

//�C���N���[�h
#include "Engine/Input.h"
#include "Stage.h"
#include "Engine/Transition.h"
#include "Engine/Debug.h"
#include "Engine/Camera.h"

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
	ASSIGN(ziro, Model::Load("Models/ziro2.fbx"));

	//�ʒu�̏�����
	transform_.position_.y = 2;

	//������Ԃ̊J�n����
	pState_->Enter(this);

	isMove_ = true;

	transform_.rotate_.y = 90;

	pLine = new PolyLine;
	pLine->Load("Effects/Fire.png");
}

//�X�V
void Player::ChildUpdate()
{

	PolyEmitPos = XMFLOAT3(transform_.position_.x - (PLAYER_MODEL_SIZE.x / 4), transform_.position_.y + (PLAYER_MODEL_SIZE.x / 4), transform_.position_.z);
	if (isMove_) {
		{//debug-PlayerMove
			if (Input::IsKey(DIK_UP))transform_.position_.y += 0.1;
			if (Input::IsKey(DIK_LEFT))transform_.position_.x -= 0.1;
			if (Input::IsKey(DIK_DOWN))transform_.position_.y -= 0.1;
			if (Input::IsKey(DIK_RIGHT))transform_.position_.x += 0.1;
		}
	}

	//jump��Ԃɂ���
	if (Input::IsKey(DIK_SPACE)) {isJumpNow_ = true;
	}

	//jump���̏������s��
	if (isJumpNow_) {transform_.position_.y += 0.1f;
	}

	Camera::SetPosition(transform_.position_.x + 5, 3.5f, -15.0f);
	Camera::SetTarget(transform_.position_.x + 5, 5.5f, 0.0f);

	//�d�͂�������
	AddGravity(&transform_);

	//�X�e�[�W�Ƃ̂����蔻��
	StageRayCast();


	//�|�����C���Ɍ��݂̈ʒu��`����
	pLine->AddPosition(PolyEmitPos);


	//��Ԃ��Ƃ̍X�V
	pState_->Update(this);
}

//�J��
void Player::ChildRelease()
{
	SAFE_DELETE(pState_);
	//�|�����C�����
	pLine->Release();
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
	z.rotate_.y = 90.0f;
	z.scale_ = { 0.1f,0.1f,0.1f };
	Model::SetTransform(ziro, z);
	Model::Draw(ziro);

	Direct3D::SetShader(Direct3D::SHADER_UNLIT);
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
			XMVECTOR length = { -leftData.dist -(PLAYER_MODEL_SIZE.x/2),0,0};
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
			Model::RayCast(hGroundModel_,&upData);
			upLandingPoint = upData.pos;
		}
		//���C�̒�����1.0�ȉ���������...
		if (upData.dist < (PLAYER_MODEL_SIZE.y / 2)) {
			//�߂荞�ݕ��A�ʒu��߂�
			XMVECTOR length = {0, (PLAYER_MODEL_SIZE.y / 2) + upData.dist,0 };
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

			//jump��Ԃ��I��
			isJumpNow_ = false;
		}
		else
			isAddGravity_ = true;

	}
}

void Player::AddGravity(Transform* _transform)
{
	if (!isAddGravity_)return;

	//�d�͂�������
	_transform->position_ = Transform::Float3Add(_transform->position_, VectorToFloat3((XMVectorSet(0, -1, 0, 0) / 10) * acceleration_));
	acceleration_ += GRAVITY_ADDITION;
}

void Player::PolyDraw()
{
	if (Input::IsKey(DIK_LSHIFT))
	{
		//�|�����C����`��
		pLine->Draw();
	}
}