#include "PlayerObject.h"
#include "Engine/Model.h"
using namespace std;

//json�w�b�_�[�̃C���N���[�h
#include "Engine/json.hpp"
using json = nlohmann::json;//json�f�[�^�C���X�^���X���i�[

//�t�@�C���X�g���[�����C���N���[�h
#include <fstream>


PlayerObject::PlayerObject(GameObject* parent)
	:GameObject(parent,"PlayerObject"),hModel_(-1)
{
}

void PlayerObject::Initialize()
{
	//���f���̃��[�h
	hModel_ = Model::Load("DebugCollision/BoxCollider.fbx");
	assert(hModel_ <= 0);

	SavePosition(transform_);
}

void PlayerObject::Update()
{
}

void PlayerObject::Draw()
{
	//���f���̕`��
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void PlayerObject::Release()
{
}

void PlayerObject::SavePosition(Transform& transform)
{
	//�t�@�C�������`
	char fileName[MAX_PATH] = "����.json";

	//�������ݗp��json�I�u�W�F�N�g���`
	json json_object;

	//Player
	json_object["Player"]["Position"] = { transform.position_.x,transform.position_.y,transform.position_.z };
	json_object["Player"]["Scale"] = { transform.scale_.x,transform.scale_.y,transform.scale_.z };

	//�����p�P
	json_object["Enemy"]["Position"] = { transform.position_.x+2,transform.position_.y,transform.position_.z };
	json_object["Enemy"]["Scale"] = { transform.scale_.x+2,transform.scale_.y,transform.scale_.z };

	//�����p�Q
	json_object["Chara1"]["Position"] = { transform.position_.x + 2,transform.position_.y,transform.position_.z };
	json_object["Chara1"]["Scale"] = { transform.scale_.x + 2,transform.scale_.y,transform.scale_.z };

	//��������
	std::ofstream output_file(fileName);
	output_file << json_object;
	output_file.close();

}

