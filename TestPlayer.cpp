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

		//���n������
		transform_.position_.y -= (data.dist - 0.5f) ;

		//�Q�̃x�N�g��������ς��擾����
		XMVECTOR dot = XMVector3Dot(XMLoadFloat3(&underNormal),data.normal);
		
		//�x�N�g���̒������擾����
		float length1 = XMVectorGetX(XMVector3Length(XMLoadFloat3(&underNormal)));
		float length2 = XMVectorGetX(XMVector3Length(data.normal));

		//�p�x(Radian)���v�Z����
		float angle = acos(XMVectorGetX(dot) / (length1 * length2));
		
		//���W�A���p����f�B�O���[�p�ɕϊ�����
		float Deg = XMConvertToDegrees(angle);

		//�p�x���A����]������
		transform_.rotate_.z = Deg;
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
