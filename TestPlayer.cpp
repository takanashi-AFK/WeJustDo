#include "TestPlayer.h"
#include "Engine/Model.h"
#include "TestStage.h"

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
	Model::DebugMove(&transform_);

	//PlayerObject���牺�����ɑ΂��ĐL�т钼����p��
	RayCastData data;
	data.start = transform_.position_;
	data.dir = XMFLOAT3(0, -1, 0);
	Model::RayCast((*(TestStage*)FindObject("TestStage")).GetModelHandle(), &data); //���C�𔭎�

	if (data.hit){
		//�I�u�W�F�N�g�̉��ɃI�u�W�F�N�g�����݂���ꍇ�̏���
		if (true);//�I�u�W�F�N�g���m���ڐG���Ă���ꍇ�̏���
		else;	//�I�u�W�F�N�g���m���ڐG���Ă��Ȃ��ꍇ�̏���
	}
	else {
		//�I�u�W�F�N�g�̑����ɃI�u�W�F�N�g�����݂��Ȃ��ꍇ�̏���
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
