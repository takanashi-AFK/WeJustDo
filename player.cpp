#include "player.h"
#include "Engine/Model.h"
#include"Engine/Input.h"
#include "yuka.h"
#include"Engine/Camera.h"


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
	Camera::SetPosition(XMFLOAT3(transform_.position_.x + 5, 3.5f, -15.0f));
	Camera::SetTarget(XMFLOAT3(transform_.position_.x + 5, 1.5f, 0.0f));

	//PlayerObject���牺�����ɑ΂��ĐL�т钼����p��
	RayCastData data;
	data.start = transform_.position_;

	XMFLOAT3 playerNormal = { 0.0f,-1.0f,0.0f };
	//XMVECTOR wPlayerNormal = XMVector3Transform(XMLoadFloat3(&playerNormal), GetWorldMatrix());

	data.dir = { 0.0f,-1.0f,0.0f };
	Model::RayCast((*(yuka*)FindObject("yuka")).GetModelHandle(), &data); //���C�𔭎�

	if (data.hit) {
		//�I�u�W�F�N�g�̉��ɃI�u�W�F�N�g�����݂���ꍇ�̏���

		//�W�����v�̏���
		if (Input::IsKeyDown(DIK_SPACE) && isJumping == false)
		{
			//�y�W�����v�̏�����̉����x���Z�Z�z
			moveY += 0.5f;

			//�y�W�����v���Ă���t���O�𗧂Ă�z
			isJumping = true;
		}

		//�y�n�ɑ������Ă��Ȃ����z
		else if (isJumping == true)
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
			transform_.position_.y -= (data.dist - 0.5f);
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



	if (Input::IsKey(DIK_A))
	{
		transform_.position_.x -= 0.5;
	}
	if (Input::IsKey(DIK_D))
	{
		transform_.position_.x += 0.5;
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
