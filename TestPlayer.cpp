#include "TestPlayer.h"
#include "Engine/Model.h"
#include "TestStage.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

TestPlayer::TestPlayer(GameObject* parent)
	:GameObject(parent,"TestPlayer")
{
}

void TestPlayer::Initialize()
{
	hModel_ = Model::Load("Models/Player.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { 0.0f,1.8f,0.0f };
	transform_.rotate_.y = 180;

	
}

void TestPlayer::Update()
{
	Model::DebugMove(&transform_,0.05f);

	Camera::SetPosition(transform_.position_.x, 5.0f, -10.0f);
	Camera::SetTarget(transform_.position_.x,3.0f,0.0f);

	//PlayerObject���牺�����ɑ΂��ĐL�т钼����p��
	RayCastData data;
	data.start = transform_.position_;
	XMFLOAT3 underNormal = {0.0f,-1.0f,0.0f};
	data.dir = underNormal;
	Model::RayCast((*(TestStage*)FindObject("TestStage")).GetModelHandle(), &data); //���C�𔭎�

	if (data.hit) {
		//�I�u�W�F�N�g�̉��ɃI�u�W�F�N�g�����݂���ꍇ�̏���
		transform_.position_.y -= (data.dist - 0.5f) ;

		//�v���C���[�̉��ɐL�т�@���x�N�g���ƁA�|���S���̖@���x�N�g���̓��ς��Ƃ�
		XMVECTOR dot = XMVector3Dot(XMLoadFloat3(&underNormal),-data.pNormal);
		
		//���ς̌��ʂ���p�x���擾
		float angle = acos(XMVectorGetX(dot));

		//���W�A��->�x
		float Deg = XMConvertToDegrees(angle);

		//�p�x���A����]������
		//transform_.rotate_.z = Deg;
	}
	else {
		//�I�u�W�F�N�g�̑����ɃI�u�W�F�N�g�����݂��Ȃ��ꍇ�̏���
		transform_.rotate_.z = 0;
		transform_.position_.y-= 0.1f;
	}

}

void TestPlayer::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TestPlayer::Release()
{
}
