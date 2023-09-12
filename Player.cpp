#include "Player.h"

//�C���N���[�h
#include "Engine/Input.h"
#include "Stage.h"
#include "Engine/Transition.h"
#include "Engine/Image.h"
#include "Engine/Debug.h"
#include "Engine/Camera.h"
#include "AudioManager.h"
#include "Engine/Audio.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
Player::Player(GameObject* _parent, string _modelFileName)
	:SolidObject(_parent,_modelFileName,"Player")
	,hDebugBox_(-1),pJet(nullptr),pState_(nullptr),hGroundModel_(0)
	,acceleration_(0),isAddGravity_(false),isMove_(false),speed_(0)
	,RandEffectData_(),DeadEffectData(),PlusOneEffectData()
{
	//�v���C���[�̏�Ԃ��u������ԁv�ŏ�����
	ASSIGN(pState_,new PlayerStateManager);
}

//������
void Player::ChildInitialize()
{
	//��Ԃ̏�����
	ASSIGN(pState_->playerState_, pState_->pStanding_);
	
	//���f���̃��[�h-debug�p
	ASSIGN(hDebugBox_, Model::Load("Models/defaultModel.fbx"));

	//�ʒu�̏�����
	SetPositionY(1.0f);
	SetRotateY(90);

	//������Ԃ̊J�n����
	pState_->Enter(this);

	//�e�G�t�F�N�g�̏�����
	{
		InitDeadEffect();
		InitRandEffect();
		InitPlusOneEffect();
		InitBombEffect();
		//pDead = new PolyLine(1,50);
		//pDead->Load("Effects/Tex.png");

		pJet = new PolyLine(0.4, 10);
		pJet->Load("Effects/Fire.png");
	}
	
	//�J�����̏�����
	Camera::SetPosition(transform_.position_.x + 5, transform_.position_.y + 3, -13.0f);
	Camera::SetTarget(transform_.position_.x + 5, transform_.position_.y + 3, 0.0f);

}

//�X�V
void Player::ChildUpdate()
{
	//�������J����
	{
		static float camMove = 4.5f;
		if (!(transform_.position_.y > 9))
		{
			if (camMove > 4.5f)
				camMove -= 0.3f;
			else camMove = 4.5f;
		}
		else
		{
			if (camMove < 14)
				camMove += 0.3f;
			else
				camMove = 14.0f;
		}
		Camera::SetPosition(transform_.position_.x + 5, camMove, -13.0f);
		Camera::SetTarget(transform_.position_.x + 5, camMove - 0.5f, 0.0f);
	}
	
	//�����Ȃ��J����
	{
		/*
		if (transform_.position_.y >= -1 && transform_.position_.y <= 15) {
			Camera::SetPosition(transform_.position_.x + 5, transform_.position_.y + 3, -13.0f);
			Camera::SetTarget(transform_.position_.x + 5, transform_.position_.y + 3, 0.0f);
		}
		else if (transform_.position_.y > 15) {
			Camera::SetPosition(transform_.position_.x + 5, Camera::GetPosition().y, -13.0f);
			Camera::SetTarget(transform_.position_.x + 5, Camera::GetTarget().y, 0.0f);
		}
		else if (transform_.position_.y <= -3 && transform_.position_.y >= -5)
		{
			Camera::SetPosition(Camera::GetPosition().x, Camera::GetPosition().y, Camera::GetPosition().z);
			Camera::SetTarget(Camera::GetTarget());
		}*/
	}

	//false�Ȃ瓮�쏈�����s�킸return
	if (!isMove_)return;

	//�W�F�b�g���̃G�t�F�N�g�ʒu�𒲐�
	{
		pJet->AddPosition(XMFLOAT3(
			transform_.position_.x - (PLAYER_MODEL_SIZE.x / 4),	//x
			transform_.position_.y - (PLAYER_MODEL_SIZE.x / 4),	//y
			transform_.position_.z));							//z
	}

	if (Input::IsKeyDown(DIK_RETURN))
	{
		SetIsMove(false);
		bombEffectData.position = XMFLOAT3(transform_.position_.x, transform_.position_.y, transform_.position_.z -2);
		int a = VFX::Start(bombEffectData);
		SceneManager* pScM = (SceneManager*)FindObject("SceneManager");
		pScM->ChangeScene(SCENE_ID_RESULT, TID_WHITEOUT);
	}

	//�d�͂�������
	AddGravity(&transform_);

	//�n�`(Stage)�Ƃ̔��莞�̏���
	TerrainInteraction();

	//��Ԃ��Ƃ̍X�V(��StageRayCast()����ɏ�������ƃo�O��)
	pState_->Update(this);

	//�X�e�[�W�Ƃ̓����蔻��
	StageRayCast();

}

//�J��
void Player::ChildRelease()
{
	SAFE_DELETE(pState_);
	pJet->Release();
}

//�`��
void Player::ChildDraw()
{
	//debug-UnlitBoxDraw
	{
		/*Direct3D::SetShader(Direct3D::SHADER_UNLIT);
		Transform t_Box; t_Box.position_ = transform_.position_; t_Box.position_.y + 0.5f;
		Model::SetTransform(hBox_, t_Box);Model::Draw(hBox_);*/
	}
	
}

void Player::StageRayCast()
{
	//�X�e�[�W�̃��f���ԍ����擾
	ASSIGN(hGroundModel_, dynamic_cast<Stage*>(FindObject("Stage"))->GetStageModelHandle(m_Ground));

	//�������̓����蔻��
	{
		RayCastData leftData; {
			leftData.start = transform_.position_;
			XMStoreFloat3(&leftData.dir, XMVectorSet(-1, 0, 0, 0));
			Model::RayCast(hGroundModel_, &leftData);
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
			Model::RayCast(hGroundModel_, &downData);
			downData_ = downData;
		}
		if (downData.dist < (PLAYER_MODEL_SIZE.y / 2)) {
			//��Ԃ�"Standing"�ɕύX
			pState_->ChangeState(pState_->pStanding_, this);
		}
		else
			isAddGravity_ = true;
	}
}

void Player::AddGravity(Transform* _transform)
{
	//�����Ȃ��Ȃ�return
	if (!isAddGravity_)return;

	//�d�͂�������
	_transform->position_ = Transform::Float3Add(_transform->position_, VectorToFloat3((XMVectorSet(0, -1, 0, 0) / 10) * acceleration_));
	acceleration_ += GRAVITY_ADDITION;
}

void Player::InitDeadEffect()
{
	//�G�t�F�N�g����ݒ�
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
	DeadEffectData.size = XMFLOAT2(1,10);
	DeadEffectData.sizeRnd = XMFLOAT2(0.4, 0.4);
	DeadEffectData.scale = XMFLOAT2(1.01, 1.01);
	DeadEffectData.color = XMFLOAT4(0, 0, 1, 1);
	DeadEffectData.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);
}

void Player::InitBombEffect()
{
	bombEffectData.textureFileName = "Effects/cloudA.png";
	bombEffectData.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	bombEffectData.delay = 0;
	bombEffectData.number = 1;
	bombEffectData.lifeTime = 25;
	bombEffectData.speed = 0.05f;
	bombEffectData.speedRnd = 0.0;
	bombEffectData.size = XMFLOAT2(5,5);
	bombEffectData.scale = XMFLOAT2(1.01, 1.01);
	bombEffectData.color = XMFLOAT4(1, 0, 0, 1);

}

void Player::InitRandEffect()
{	
	//�G�t�F�N�g����ݒ�
	RandEffectData_.textureFileName = "Effects/RandSmoke2.png";
	RandEffectData_.position = XMFLOAT3(transform_.position_.x, transform_.position_.y - 0.2,0);
	RandEffectData_.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	RandEffectData_.delay = 0;
	RandEffectData_.number = 1;
	RandEffectData_.lifeTime = 40;
	RandEffectData_.speed = 0.01f;
	RandEffectData_.speedRnd = 0.0;
	RandEffectData_.size = XMFLOAT2(1,0.5);
	RandEffectData_.scale = XMFLOAT2(1.01, 1.01);
	RandEffectData_.color = XMFLOAT4(1,1,1,1);
	RandEffectData_.deltaColor = XMFLOAT4(0, 0, 0, -0.1);
}

void Player::InitPlusOneEffect()
{
	PlusOneEffectData.textureFileName = "Effects/PlusOneR.png";
	PlusOneEffectData.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	PlusOneEffectData.delay = 0;
	PlusOneEffectData.number = 1;
	PlusOneEffectData.lifeTime = 25;
	PlusOneEffectData.speed = 0.05f;
	PlusOneEffectData.speedRnd = 0.0;
	PlusOneEffectData.size = XMFLOAT2(0.75, 0.75);
	PlusOneEffectData.scale = XMFLOAT2(1.01, 1.01);
	PlusOneEffectData.color = XMFLOAT4(1, 1, 1, 1);
}


void Player::OnWoodPickup(Stage* pS)
{
	//�v���C���[�̈ʒu���Por�Q�Ȃ�...
	if (pS->AtItem(this, 1) || pS->AtItem(this,2)) {

		//�d��1�{(*5)�擾����
		Global::gFireWood += 5;

		//�G�t�F�N�g
		PlusOneEffectData.position = (XMFLOAT3(transform_.position_.x - 0.5, transform_.position_.y + 0.5, 0));
		VFX::Start(PlusOneEffectData);

		AudioManager::Play_WoodSound();

		//���̏ꏊ�̐d�������ċ�C�ɕϊ�
		pS->SetItem(round(transform_.position_.x), round(transform_.position_.y), 0);
	}
}

const float GOAL_POINT = 285.0f;

bool Player::isGoal()
{
	return transform_.position_.x >= GOAL_POINT;
}

void Player::TerrainInteraction()
{
	//�X�e�[�W�����擾
	Stage* pS = (Stage*)(FindObject("Stage"));

	//�d���擾����
	OnWoodPickup(pS);

	//���ꂪ�D�̎�
	if (pS->AtItem(this, 2))
	{
		//�����܂��s���Ȃ�(������)
	}
	else SetSpeed(0.1f);
}

void Player::PolyDraw()
{
	//�W�F�b�g��Ԃ̎��A�|�����C����`��(�W�F�b�g����effect)
	if (pState_->playerState_ == pState_->pJet_)pJet->Draw();
}

void Player::SetDrawTransform()
{
	//�V�F�[�_�[��ݒ�
	Direct3D::SetShader(Direct3D::SHADER_3D);
	
	//�`��ʒu���C��(ziro_move.fbx�̑����̍��W��{0,0,0}�ׂ̈��炷�K�v������)
	Transform t_Draw; {
		t_Draw = transform_;
		t_Draw.position_.y -= 0.5f;
		t_Draw.scale_ = { 0.1f,0.1f,0.1f };
	}
	Model::SetTransform(hModel_, t_Draw);
}
