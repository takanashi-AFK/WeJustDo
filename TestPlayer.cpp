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
		
	XMFLOAT3 playerNormal = {0.0f,-1.0f,0.0f};
	//XMVECTOR wPlayerNormal = XMVector3Transform(XMLoadFloat3(&playerNormal), GetWorldMatrix());

	data.dir = { 0.0f,-1.0f,0.0f };
	Model::RayCast((*(TestStage*)FindObject("TestStage")).GetModelHandle(), &data); //���C�𔭎�

	if (data.hit) {
		//�I�u�W�F�N�g�̉��ɃI�u�W�F�N�g�����݂���ꍇ�̏���

		//���n������
		transform_.position_.y -= (data.dist - 0.5f) ;

		//�Q�̃x�N�g��������ς��擾����
		XMVECTOR dot = XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&playerNormal)), XMVector3Normalize(data.normal));

		//�p�x(Radian)���v�Z����(�������̊p�x���擾)
		float angle = acos(XMVectorGetX(dot));

		//���W�A���p����f�B�O���[�p�ɕϊ�����
		float Deg = XMConvertToDegrees(angle);
		
		//�O�ς��畉�̒l�����̒l���𔻒f����
		if (XMVectorGetZ(XMVector3Cross(data.normal, XMLoadFloat3(&playerNormal))) < 0) {
			Deg *= -1;//���̒l�̏ꍇ��-1��������
		}

		//�p�x���A����]������
		transform_.rotate_.z = (Deg);
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
