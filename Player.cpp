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
#include "StartCount.h"
#include "FuelGauge.h"


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
		InitGetEffect();

		pJet = new PolyLine(0.4, 10);
		pJet->Load("Effects/Fire.png");
	}

	//�Q�[�W�̏�����
	pGauge_ = Instantiate<FuelGauge>(this);

	//�O�t���[���̈ړ��ʏ�����
	currentPos_.position_ = { 0, 0, 0 };



	//�J�����̏�����
	Camera::SetPosition(transform_.position_.x + 5, transform_.position_.y + 3, -13.0f);
	Camera::SetTarget(transform_.position_.x + 5, transform_.position_.y + 3, 0.0f);
}
//�X�V
void Player::ChildUpdate()
{
	static float camX = 0;
	//�������J����
	{
		static float camMoveY = defCamY;	//�n�ʂ̉��������Ȃ��M���M���̃��C��
		static float camMoveZ = defCamZ;

		//�J�������WZ�̌v�Z
		camMoveZ = CalcCamPositionZ(transform_);

		//�J�������WY�̌v�Z
		camMoveY = CalcCamPositionY(transform_);

		//�J�����ړ�
		Camera::SetPosition(transform_.position_.x + 5, camMoveY, camMoveZ);
		Camera::SetTarget(transform_.position_.x + 5, camMoveY - 0.5f, 0.0f);
	}
	
	
	StartCount pSt = (StartCount*)FindObject("StartCount");
	if (pSt.IsFinished())
	{
	if (Input::IsKeyDown(DIK_RETURN))
	{
		SetAcceleration(0);
		SetIsMove(false);
		bombEffectData.position = XMFLOAT3(transform_.position_.x, transform_.position_.y, transform_.position_.z -2);
		int a = VFX::Start(bombEffectData);
		AudioManager::Play_BombSound();
		SceneManager* pScM = (SceneManager*)FindObject("SceneManager");
		pScM->ChangeScene(SCENE_ID_RESULT, TID_WHITEOUT);
	}
	}

	//Gauge
	pGauge_->SetFuel(Global::gFireWood / 5, maxfireWood_);


	//�S�[��������...
	if (isGoal()) {
		//movie��ԂɈڍs����
		pState_->ChangeState(pState_->pMovie_, this);
	}

	//false�Ȃ瓮�쏈�����s�킸return
	if (!isMove_)return;

	//camX+= 0.05f;

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
		AudioManager::Play_BombSound(); 
		bombEffectData.position = XMFLOAT3(transform_.position_.x + 5, transform_.position_.y , 0.0f);
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
	//StageRayCast();

	RayNeo();
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
	ASSIGN(hGroundModel_, dynamic_cast<Stage*>(FindObject("Stage"))->GetStageModelHandle(m_Ground));

	//�����
	{
		//UpRight
		RayCastData upDataRight; {
			//���C�̊J�n�n�_��ݒ�
			upDataRight.start = transform_.position_;
			upDataRight.start.x += ((PLAYER_MODEL_SIZE.x / 2) - 0.1f);

			//���C�̔��˕�����ݒ�
			XMStoreFloat3(&upDataRight.dir, XMVectorSet(0, 1, 0, 0));

			//���C�𔭎�
			Model::RayCast(hGroundModel_, &upDataRight);
		}
		if (upDataRight.dist <= (PLAYER_MODEL_SIZE.y / 2)) {
			//�߂荞�ݕ��߂�����
			XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - std::abs(upDataRight.dist),0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - length);

		}

		//Up+eft
		RayCastData upDataLeft; {
			//���C�̊J�n�n�_��ݒ�
			upDataLeft.start = transform_.position_;
			upDataLeft.start.x -= ((PLAYER_MODEL_SIZE.x / 2) - 0.1f);

			//���C�̔��˕�����ݒ�
			XMStoreFloat3(&upDataLeft.dir, XMVectorSet(0, 1, 0, 0));

			//���C�𔭎�
			Model::RayCast(hGroundModel_, &upDataLeft);
		}
		if (upDataLeft.dist <= (PLAYER_MODEL_SIZE.y / 2)) {
			//�߂荞�ݕ��߂�����
			XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - std::abs(upDataLeft.dist),0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - length);

		}
	}

	//StandingState,RunningState�Ƃ��̂ݍs������State���ŏ������s��
	//������
	{
		//downRight
		RayCastData downDataRight; {
			//���C�̊J�n�n�_��ݒ�
			downDataRight.start = transform_.position_;
			downDataRight.start.x += ((PLAYER_MODEL_SIZE.x / 2) - 0.1f);

			//���C�̔��˕�����ݒ�
			XMStoreFloat3(&downDataRight.dir, XMVectorSet(0, -1, 0, 0));

			//���C�𔭎�
			Model::RayCast(hGroundModel_, &downDataRight);
		}
		if (downDataRight.dist < (PLAYER_MODEL_SIZE.y / 2)) {
			//��ԑJ�ځF->Standing
			pState_->ChangeState(pState_->pStanding_, this);
		}
		else
			IsAddGravity(true);

	}

	//�������̓����蔻��
	{
		//LeftTop
		RayCastData leftDataTop; {
			//���C�̊J�n�n�_��ݒ�
			leftDataTop.start = transform_.position_;
			leftDataTop.start.y += ((PLAYER_MODEL_SIZE.y / 2) - 0.1f);

			//���C�̔��˕�����ݒ�
			XMStoreFloat3(&leftDataTop.dir, XMVectorSet(-1, 0, 0, 0));

			//���C�𔭎�
			Model::RayCast(hGroundModel_, &leftDataTop);
		}
		if (leftDataTop.dist <= (PLAYER_MODEL_SIZE.x / 2)) {
			//�߂荞�ݕ��߂�����
			XMVECTOR length = { (PLAYER_MODEL_SIZE.x / 2) - std::abs(leftDataTop.dist),0,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) + length);
		}

		//LeftBottom
		RayCastData leftDataBottom; {
			//���C�̊J�n�n�_��ݒ�
			leftDataBottom.start = transform_.position_;
			leftDataBottom.start.y -= ((PLAYER_MODEL_SIZE.y / 2) - 0.1f);

			//���C�̔��˕�����ݒ�
			XMStoreFloat3(&leftDataBottom.dir, XMVectorSet(-1, 0, 0, 0));

			//���C�𔭎�
			Model::RayCast(hGroundModel_, &leftDataBottom);
		}
		if (leftDataBottom.dist <= (PLAYER_MODEL_SIZE.x / 2)) {
			//�߂荞�ݕ��߂�����
			XMVECTOR length = { (PLAYER_MODEL_SIZE.x / 2) - std::abs(leftDataBottom.dist),0,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) + length);
		}
	}

	//�E�����̂����蔻��
	{
		//RightTop
		RayCastData rightDataTop; {
			//���C�̊J�n�n�_��ݒ�
			rightDataTop.start = transform_.position_;
			rightDataTop.start.y += ((PLAYER_MODEL_SIZE.y / 2) - 0.1f);

			//���C�̔��˕�����ݒ�
			XMStoreFloat3(&rightDataTop.dir, XMVectorSet(1, 0, 0, 0));

			//���C�𔭎�
			Model::RayCast(hGroundModel_, &rightDataTop);
		}
		if (rightDataTop.dist <= (PLAYER_MODEL_SIZE.x / 2)) {
			//�߂荞�ݕ��߂�����
			XMVECTOR length = { (PLAYER_MODEL_SIZE.x / 2) - std::abs(rightDataTop.dist),0,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - length);
		}

		//RightBottom
		RayCastData rightDataBottom; {
			//���C�̊J�n�n�_��ݒ�
			rightDataBottom.start = transform_.position_;
			rightDataBottom.start.y -= ((PLAYER_MODEL_SIZE.y / 2) - 0.1f);

			//���C�̔��˕�����ݒ�
			XMStoreFloat3(&rightDataBottom.dir, XMVectorSet(1, 0, 0, 0));

			//���C�𔭎�
			Model::RayCast(hGroundModel_, &rightDataBottom);
		}
		if (rightDataBottom.dist <= (PLAYER_MODEL_SIZE.x / 2)) {
			//�߂荞�ݕ��߂�����
			XMVECTOR length = { (PLAYER_MODEL_SIZE.x / 2) - std::abs(rightDataBottom.dist),0,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - length);
		}
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


void Player::OnWoodPickup(Stage* pS)
{
	//�v���C���[�̈ʒu���Por�Q�Ȃ�...
	if (pS->AtItem(this, 1) || pS->AtItem(this,2)) {

		//�d��1�{(*5)�擾����
		Global::gFireWood += 5;

		//�G�t�F�N�g
		PlusOneEffectData.position = (XMFLOAT3(transform_.position_.x - 0.5, transform_.position_.y + 0.5, 0));
		ItemGetEffectData.position = transform_.position_;
		VFX::Start(PlusOneEffectData);
		VFX::Start(ItemGetEffectData);

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
	bombEffectData.textureFileName = "Image/bomb.png";
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

void Player::InitGetEffect()
{
	ItemGetEffectData.textureFileName = "Effects/kira.png";
	ItemGetEffectData.position = XMFLOAT3(transform_.position_.x, transform_.position_.y - 0.2, 0);
	ItemGetEffectData.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	ItemGetEffectData.delay = 0;
	ItemGetEffectData.number = 1;
	ItemGetEffectData.lifeTime = 40;
	ItemGetEffectData.speed = 0.01f;
	ItemGetEffectData.speedRnd = 0.0;
	ItemGetEffectData.size = XMFLOAT2(1, 0.5);
	ItemGetEffectData.scale = XMFLOAT2(1.01, 1.01);
	ItemGetEffectData.color = XMFLOAT4(1, 1, 1, 1);
	ItemGetEffectData.deltaColor = XMFLOAT4(0, 0, 0, -0.1);
}

float Player::CalcCamPositionY(Transform _plPos)
{
	float result = 0.0f;
	//Player �Ə��̕��ς��Ƃ�B�ŁA���ς��A�f�t�H���g�ݒ�l�ȏ�Ȃ瓮����
	if ((_plPos.position_.y + stageBottom / 2) >= defCamY)
	{
		//Player �Ə��̕��ς��J�����̍ő卂�x�ȏ�Ȃ��
		if (_plPos.position_.y + stageBottom / 2 >= maxCamY)
		{
			//�J�������x�͍ő��
			return (maxCamY) - 2;//�Ȃ���2�������Ȃ��ƃK�N�K�N����B
		}
		else
		{
			//�����łȂ����Player�Ə��̕��ϒl��������
			result = ((_plPos.position_.y + stageBottom) / 2 ) + 2;//�Ȃ���2�𑫂��Ȃ��ƃK�N�K�N����B
			return(result);
		}
	}
	else{//���ς��f�t�H���g�ʒu�����������������̓f�t�H���g�l��Ԃ�
		return (defCamY);
	}
}

float Player::CalcCamPositionZ(Transform _plPos)
{
	float result = 0.0f;
	//Player�̍��W���J�����̃f�t�H���gY���W�ȏゾ�������A���̕��J��������������
	if (_plPos.position_.y >= defCamY)
	{
		result = (camZBottom - _plPos.position_.y) + defCamZ;
		return (result);

	}
	else//�f�t�H���gY���W�����Ȃ�f�t�H���gY���W�����̂܂܎g��
	{
		result = defCamZ;
		return (result);
	}
}

void Player::RayNeo()
{
	ASSIGN(hGroundModel_, dynamic_cast<Stage*>(FindObject("Stage"))->GetStageModelHandle(m_Ground));

	//�����
	{
		RayCastData upDataL; {
			//�������Ă��邩�m�F
			upDataL.start = XMFLOAT3(transform_.position_.x - (PLAYER_MODEL_SIZE.x / 2), 
									 transform_.position_.y + (PLAYER_MODEL_SIZE.y / 2), 
									 transform_.position_.z);
			XMStoreFloat3(&upDataL.dir, XMVectorSet(0, 1, 0, 0));
			Model::RayCast(hGroundModel_, &upDataL);
		}
		RayCastData upDataR; {
			//�������Ă��邩�m�F
			upDataR.start = XMFLOAT3(transform_.position_.x + (PLAYER_MODEL_SIZE.x / 2), 
									 transform_.position_.y + (PLAYER_MODEL_SIZE.y / 2),
									 transform_.position_.z);
			XMStoreFloat3(&upDataR.dir, XMVectorSet(0, 1, 0, 0));
			Model::RayCast(hGroundModel_, &upDataR);
		}
		//���C�̒�����1.0�ȉ���������...
		if (upDataR.dist < (PLAYER_MODEL_SIZE.y / 2)&& upDataL.dist < (PLAYER_MODEL_SIZE.y / 2)) {
			//�߂荞�ݕ��A�ʒu��߂�
			XMVECTOR length = { 0, (PLAYER_MODEL_SIZE.y / 2) + ((upDataR.dist + upDataL.dist)/2),0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(0, 1, 0, 0) - length));
			SetAcceleration(2);
		}
	}

	//StandingState,RunningState�Ƃ��̂ݍs������State���ŏ������s��
	//�������̂����蔻��
	{
		RayCastData downDataL; {
			//�������Ă��邩�m�F
			downDataL.start = XMFLOAT3(transform_.position_.x,
								       transform_.position_.y ,
									   transform_.position_.z);
			XMStoreFloat3(&downDataL.dir, XMVectorSet(0, -1, 0, 0));
			Model::RayCast(hGroundModel_, &downDataL);
			downData_ = downDataL;
		}
		if (downDataL.dist < (PLAYER_MODEL_SIZE.y / 2) ) {
			//��Ԃ�"Standing"�ɕύX
			pState_->ChangeState(pState_->pStanding_, this);
		}
		else
			isAddGravity_ = true;
	}
	
	//�������̓����蔻��
	{

		RayCastData leftDataTop; {
			leftDataTop.start = XMFLOAT3(transform_.position_.x - (PLAYER_MODEL_SIZE.x / 2), 
										 transform_.position_.y + (PLAYER_MODEL_SIZE.x / 2), 
										 transform_.position_.z);
			XMStoreFloat3(&leftDataTop.dir, XMVectorSet(-1, 0, 0, 0));
			Model::RayCast(hGroundModel_, &leftDataTop);
		}
		RayCastData leftDataBottom; {
			leftDataBottom.start = XMFLOAT3(transform_.position_.x - (PLAYER_MODEL_SIZE.x / 2), 
											transform_.position_.y - (PLAYER_MODEL_SIZE.x / 2),
											transform_.position_.z);
			XMStoreFloat3(&leftDataBottom.dir, XMVectorSet(-1, 0, 0, 0));
			Model::RayCast(hGroundModel_, &leftDataBottom);
		}
		if (leftDataBottom.dist < (PLAYER_MODEL_SIZE.x / 2)&& leftDataTop.dist < (PLAYER_MODEL_SIZE.x / 2)) {
			//�߂荞�ݕ��A�ʒu��߂�
			XMVECTOR length = { (((-leftDataBottom.dist + -leftDataTop.dist)/2 - (PLAYER_MODEL_SIZE.x / 2))-0.1),0,0};
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(-1, 0, 0, 0) - length));
		}
	}

		//�E�����̂����蔻��
	{
		RayCastData rightDataTop; {
			//�������Ă��邩���m�F
			rightDataTop.start = XMFLOAT3(transform_.position_.x + (PLAYER_MODEL_SIZE.x / 2),
										  transform_.position_.y + (PLAYER_MODEL_SIZE.x / 2),
										  transform_.position_.z);					//���ˈʒu�̎w��
			XMStoreFloat3(&rightDataTop.dir, XMVectorSet(1, 0, 0, 0));	//���˕����̎w��
			Model::RayCast(hGroundModel_, &rightDataTop);				//���C�𔭎�
		}
		RayCastData rightDataBottom; {
			//�������Ă��邩���m�F
			rightDataBottom.start = XMFLOAT3(transform_.position_.x + (PLAYER_MODEL_SIZE.x / 2),
											 transform_.position_.y - (PLAYER_MODEL_SIZE.x / 2), 
											 transform_.position_.z);				//���ˈʒu�̎w��
			XMStoreFloat3(&rightDataBottom.dir, XMVectorSet(1, 0, 0, 0));	//���˕����̎w��
			Model::RayCast(hGroundModel_, &rightDataBottom);				//���C�𔭎�
		}
		//���C�̒�����1.0�ȉ���������...
		if (rightDataBottom.dist < (PLAYER_MODEL_SIZE.x / 2)&& rightDataTop.dist < (PLAYER_MODEL_SIZE.x / 2)) {
			//�߂荞�ݕ��A�ʒu��߂�
			//�߂�����������Ƒ��₷���߂�+0.1����
			//0.1�ȏ�ɂȂ�ƁA�p�ɃX�i�b�v����悤�ɂȂ��Ă��܂�
			XMVECTOR length = { ((rightDataBottom.dist +rightDataTop.dist)/2 + (PLAYER_MODEL_SIZE.x / 2)+0.1),0,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(1, 0, 0, 0) - length));
		}
	}
}
