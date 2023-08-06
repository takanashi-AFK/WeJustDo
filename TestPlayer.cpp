#include "TestPlayer.h"
#include "Engine/Model.h"
#include "TestStage.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Direct3D.h"

TestPlayer::TestPlayer(GameObject* parent)
	:GameObject(parent, "TestPlayer"),isJumping(false),moveY(0),Deg(0)
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
	//Model::DebugMove(&transform_,0.15f);

	Camera::SetPosition(transform_.position_.x+5, 3.5f, -15.0f);
	Camera::SetTarget(transform_.position_.x + 5,5.5f,0.0f);

	//PlayerObject���牺�����ɑ΂��ĐL�т钼����p��
	RayCastData data;
	data.start = transform_.position_;
		
	XMFLOAT3 playerNormal = {0.0f,-1.0f,0.0f};
	//XMVECTOR wPlayerNormal = XMVector3Transform(XMLoadFloat3(&playerNormal), GetWorldMatrix());

	data.dir = { 0.0f,-1.0f,0.0f };
	Model::RayCast((*(TestStage*)FindObject("TestStage")).GetModelHandle(), &data); //���C�𔭎�

	if (data.hit) {
		//�I�u�W�F�N�g�̉��ɃI�u�W�F�N�g�����݂���ꍇ�̏���

		//�W�����v�̏���
		if (Input::IsKeyDown(DIK_SPACE) && isJumping == false)
		{
			//�y�W�����v�̏�����̉����x���Z�Z�z
			moveY += 0.3f;

			//�y�W�����v���Ă���t���O�𗧂Ă�z
			isJumping = true;
		}

		//�y�n�ɑ������Ă��Ȃ����z
		else if(isJumping == true)
		{
			//�y�d�͉����x���Z�Z�z
			moveY -= 0.02f;
			transform_.rotate_.z = 0.0f;

			//�y�������������̉����x�����l�Z�Z�ȉ��ł����
			if (moveY <= -0.3f)
			{
				//�y�������̉����x���Z�Z�ɌŒ肷��z
				moveY = -0.3f;
			}
		}

		//�y�v���C���[�ƒn�ʂ̈ʒu����苗���Z�Z�ɂȂ�����z
		if ((data.dist <= 0.4f))
		{
			//�y�㉺�����̉����x�͂O�B�z
			moveY = 0.0f;
			
			//�y�n�ɑ������Ă���z
			isJumping = false;
		}

		//�y�n�ɑ������Ă���Ƃ��z
		if (isJumping == false)
		{
			//�y���C�̓������������Ɏ��g��u���z
			transform_.position_.y -= (data.dist-0.5f);
		}

		//�y�v���C���[��Y���W�̈ړ��z
		transform_.position_.y += moveY;
		

		//�Q�̃x�N�g��������ς��擾����
		XMVECTOR dot = XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&playerNormal)), XMVector3Normalize(data.normal));

		//�p�x(Radian)���v�Z����(�������̊p�x���擾)
		float angle = acos(XMVectorGetX(dot));

		//���W�A���p����f�B�O���[�p�ɕϊ�����
		Deg = XMConvertToDegrees(angle);
		
		//�O�ς��畉�̒l�����̒l���𔻒f����
		if (XMVectorGetZ(XMVector3Cross(data.normal, XMLoadFloat3(&playerNormal))) < 0) 
		{
			Deg *= -1;//���̒l�̏ꍇ��-1��������
		}

		//�p�x���A����]������
		transform_.rotate_.z = (Deg);
	}
	else {
		//�I�u�W�F�N�g�̑����ɃI�u�W�F�N�g�����݂��Ȃ��ꍇ�̏���
		transform_.rotate_.z = 0;

		moveY -= 0.02f;
		transform_.position_.y += moveY;
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

//https://github.com/takanashi-AFK/WeJustDo/tree/Jump_Test