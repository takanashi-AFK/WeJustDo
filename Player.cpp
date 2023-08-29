#include "Player.h"

//�C���N���[�h
#include "Engine/Input.h"
#include "Stage.h"
#include "Engine/Transition.h"
#include "Engine/Camera.h"
//�萔�錾
namespace {
	//�d�͂̉��Z�l
	static const float GRAVITY_ADDITION = 0.03f;

	//Player�̃��f���̑傫��
	static const XMFLOAT3 PLAYER_MODEL_SIZE = { 1.0f,1.0f,1.0f };
}

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

	//������Ԃ̊J�n����
	pState_->Enter(this);
	transform_.scale_ = { 0.1f,0.1f, 0.1f };
	transform_.rotate_.y = 90;

	pLine = new PolyLine;
	pLine->Load("Effects/Fire.png");



	data.textureFileName = "Effects/cloudA.png";
	data.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	data.delay = 5;
	data.number = 1;
	data.direction = XMFLOAT3(-1, 0, 0);
	data.directionRnd = XMFLOAT3(0, 0, 0);
	data.rotate = XMFLOAT3(45, 0, 0);
	data.speed = 0.01f;
	data.speedRnd = 0.0;
	data.size = XMFLOAT2(0.3, 0.3);
	data.sizeRnd = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(1.01, 1.01);
	data.color = XMFLOAT4(1, 1, 0, 1);
	data.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);
}

//�X�V
void Player::ChildUpdate()
{

	PolyEmitPos = XMFLOAT3(transform_.position_.x - (PLAYER_MODEL_SIZE.x /4), transform_.position_.y + (PLAYER_MODEL_SIZE.x / 4), transform_.position_.z);
	if (!Transition::IsActive()) {
		{//debug-PlayerMove
			if (Input::IsKey(DIK_W))transform_.position_.y += 0.1;
			if (Input::IsKey(DIK_A)) { transform_.position_.x -= 0.1; transform_.rotate_.y = -90; PolyEmitPos.x = PolyEmitPos.x + 0.5; }
			if (Input::IsKey(DIK_S))transform_.position_.y -= 0.1;
			if (Input::IsKey(DIK_D)){transform_.position_.x += 0.1; transform_.rotate_.y = 90; }
			if (Input::IsKey(DIK_RIGHT))transform_.rotate_.y -= 1;
			if (Input::IsKey(DIK_LEFT))transform_.rotate_.y += 1;
		}
	}

	Camera::SetPosition(transform_.position_.x + 5, 3.5f, -15.0f);
	Camera::SetTarget(transform_.position_.x + 5, 5.5f, 0.0f);



	
	//�|�����C���Ɍ��݂̈ʒu��`����
	pLine->AddPosition(PolyEmitPos);


	//��Ԃ��Ƃ̍X�V
	//pState_->Update(this);
	
	//�X�e�[�W�Ƃ̂����蔻��
	StageRayCast();
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

}

void Player::PolyDraw()
{
	if (Input::IsKey(DIK_LSHIFT))
	{
		//�|�����C����`��
		pLine->Draw();
	}
}

void Player::StageRayCast()
{
	//�X�e�[�W�̃��f���ԍ����擾
	ASSIGN(hGroundModel_,dynamic_cast<SolidObject*>((Stage*)FindObject("Stage"))->GetModelHandle());

	//�������̓����蔻��
	{
		//RayCastData leftData; {
		//	//�������Ă��邩�m�F
		//	leftData.start = transform_.position_;
		//	leftData.start.x = transform_.position_.x + (float)(PLAYER_MODEL_SIZE.x / 2);
		//	XMStoreFloat3(&leftData.dir, XMVectorSet(-1, 0, 0, 0));
		//	Model::RayCast(hGroundModel_, &leftData);
		//}
		////���C�̒�����1.0�ȉ���������...
		//if (leftData.dist <= 1.0f) {
		//	//�߂荞�ݕ��A�ʒu��߂�
		//	XMVECTOR length = { -leftData.dist,0,0 };
		//	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(-1, 0, 0, 0) - length));
		//}
	}

	//�E�����̂����蔻��
	{
		//RayCastData rightData; {
		//	//�������Ă��邩���m�F
		//	rightData.start = transform_.position_;					//���ˈʒu�̎w��
		//	rightData.start.x = transform_.position_.x - (PLAYER_MODEL_SIZE.x / 2);
		//	XMStoreFloat3(&rightData.dir, XMVectorSet(1, 0, 0, 0));	//���˕����̎w��
		//	Model::RayCast(hGroundModel_, &rightData);				//���C�𔭎�
		//}
		////���C�̒�����1.0�ȉ���������...
		//if (rightData.dist <= 1.0f) {
		//	//�߂荞�ݕ��A�ʒu��߂�
		//	XMVECTOR length = { rightData.dist,0,0 };
		//	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(1, 0, 0, 0) - length));
		//}
	}

	//������̂����蔻��
	{
		//RayCastData upData; {
		//	//�������Ă��邩�m�F
		//	upData.start = transform_.position_;
		//	upData.start.y = transform_.position_.y + (float)(PLAYER_MODEL_SIZE.y / 2);
		//	XMStoreFloat3(&upData.dir, XMVectorSet(0, 1, 0, 0));
		//	Model::RayCast(hGroundModel_,&upData);
		//}
		////���C�̒�����1.0�ȉ���������...
		//if (upData.dist <= 1.0f) {
		//	//�߂荞�ݕ��A�ʒu��߂�
		//	XMVECTOR length = {0, upData.dist,0 };
		//	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(0, 1, 0, 0) - length));
		//}
	}

	//�������̂����蔻��
	{
		//RayCastData downData; {
		//	//�������Ă��邩�m�F
		//	downData.start = transform_.position_;
		//	downData.start.y = transform_.position_.y -(PLAYER_MODEL_SIZE.y / 2.0f);
		//	XMStoreFloat3(&downData.dir, XMVectorSet(0, -1, 0, 0));
		//	Model::RayCast(hGroundModel_,&downData);
		//}
		//if (downData.dist <= 1.0f) {
		//	//�߂荞�ݕ��A�ʒu��߂�
		//	XMVECTOR length = { 0,-downData.dist,0 };
		//	XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(0, -1, 0, 0) - length));
		//}

		//transform_.position_.y -= 0.1;


		////���C�̒��������Z�̎�(���n�_�ƃv���C���[�̑����̈ʒu�̋����̒�����n�ȏ�̎�)
		//if (downData.dist > 1.0f) {
		//	//�d�͂��������ɉ�����
		//	transform_.position_.y -= 0.03;
		//}
		//else {
		//	//�d�͂��������ɁA���n�_�ƃv���C���[�̑����̈ʒu�����킹��
		//	transform_.position_.y = transform_.position_.y - (downData.dist + (PLAYER_MODEL_SIZE.y /2.0f));
		//}
	}
}
