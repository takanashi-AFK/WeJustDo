#include "player.h"
#include "Engine/Model.h"
#include"Engine/Input.h"
#include "yuka.h"
#include"asiba.h"
#include"Engine/Camera.h"
#include"Engine/Debug.h"


//�R���X�g���N�^
player::player(GameObject* parent)
	: GameObject(parent, "player"),hModel_(-1)
{
}

//������
void player::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("DebugCollision/SphereCollider.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { 0.0f,1.8f,0.0f };
	transform_.rotate_.y = 180;
}

//�X�V
void player::Update()
{
	std::vector<Model::DaH> DaHList;
	Camera::SetPosition(XMFLOAT3(transform_.position_.x + 5, 3.5f, -15.0f));
	Camera::SetTarget(XMFLOAT3(transform_.position_.x + 5, 1.5f, 0.0f));

	//PlayerObject���牺�����ɑ΂��ĐL�т钼����p��
	RayCastData DownRayData;
	DownRayData.start = transform_.position_;
	DownRayData.dir = { 0.0f,-1.0f,0.0f };

	DaHList = Model::GetHitModelList(&DownRayData, hModel_);
	Model::DaH nearDist = Model::SortList(DaHList);

	RayCastData UpRayData;
	UpRayData.start = transform_.position_;
	UpRayData.dir = { 0.0f,1.0f,0.0f };

	XMFLOAT3 playerNormal = { 0.0f,-1.0f,0.0f };
	//XMVECTOR wPlayerNormal = XMVector3Transform(XMLoadFloat3(&playerNormal), GetWorldMatrix());
	
	Model::RayCast((*(asiba*)FindObject("asiba")).GetModelHandle(), &UpRayData); //���C�𔭎�
/*
	if (transform_.position_.y >= 2.5f) {
		Model::RayCast((*(asiba*)FindObject("asiba")).GetModelHandle(), &DownRayData); //���C�𔭎�
	}
	else
	{
		Model::RayCast((*(yuka*)FindObject("yuka")).GetModelHandle(), &DownRayData); //���C�𔭎�
	}
*/


	if (DownRayData.hit) {
		//�I�u�W�F�N�g�̉��ɃI�u�W�F�N�g�����݂���ꍇ�̏���

		//�W�����v�̏���
		if (Input::IsKeyDown(DIK_SPACE) && isJumping == false)
		{
			flame = 0;
			//�y�W�����v�̏�����̉����x���Z�Z�z
			moveY += 0.5f;

			//�y�W�����v���Ă���t���O�𗧂Ă�z
			isJumping = true;
		}

		//�y�n�ɑ������Ă��Ȃ����z
		else if (isJumping == true)
		{
			flame++;
			//�y�d�͉����x���Z�Z�z
			moveY -= 0.02f;

			//�y�������������̉����x�����l�Z�Z�ȉ��ł����
			if (moveY <= -0.3f)
			{
				//�y�������̉����x���Z�Z�ɌŒ肷��z
				moveY = -0.3f;
			}
		}

		//�y�v���C���[�ƒn�ʂ̈ʒu����苗���Z�Z�ɂȂ�����z
		if ((DownRayData.dist <= 0.4f))
		{
			//�y�㉺�����̉����x�͂O�z
			moveY = 0.0f;

			//�y�n�ɑ������Ă���z
			isJumping = false;
		}

		//�y�n�ɑ������Ă���Ƃ��z
		if (isJumping == false)
		{
			//�y���C�̓������������Ɏ��g��u���z
			transform_.position_.y -= (nearDist.Dist - 1);
		}

		//�y�v���C���[��Y���W�̈ړ��z
		transform_.position_.y += moveY;

	}
	else {
		//�I�u�W�F�N�g�̑����ɃI�u�W�F�N�g�����݂��Ȃ��ꍇ�̏���
		transform_.rotate_.z = 0;

		moveY -= 0.02f;
		transform_.position_.y += moveY;
	}


	if (UpRayData.hit&&UpRayData.dist<=1.5f)
	{
		moveY -= 0.2;
		//�y�v���C���[��Y���W�̈ړ��z
		transform_.position_.y += moveY;
	}


	if (Input::IsKey(DIK_A))
	{
		transform_.position_.x -= 0.5;
	}
	if (Input::IsKey(DIK_D))
	{
		transform_.position_.x += 0.5;
	}

	if (Input::IsKeyDown(DIK_V))
	{
		Debug::Log(flame);
	}

}

//�`��
void player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void player::Release()
{
}
