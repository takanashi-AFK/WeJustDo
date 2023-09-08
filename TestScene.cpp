#include "TestScene.h"
#include "Engine/Text.h"

#include <cstdio>//�t�H�[�}�b�g�w��q���g�p

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"),flame_(0),pText_(nullptr)
{
}

//������
void TestScene::Initialize()
{
	//�������Ԃ��Z�b�g/�b
	SetSeconds(20);

	//Text�̏�����
	pText_ = new Text;
	pText_->Initialize();
}

//�X�V
void TestScene::Update()
{
	//�t���[�����X�V
	flame_--;
}

//�`��
void TestScene::Draw()
{
	if (flame_ < 0)return;//0�ȉ��ɂȂ�����`�����߂�

	// �[�����߂̃t�H�[�}�b�g�w��q���g�p���ĕ�����𐶐�
	char buffer[4];//������+1���̔z��T�C�Y
	snprintf(buffer, sizeof(buffer), "%03d", flame_ / 60);

	//������`��
	std::string result = "time : " + (std::string)buffer;
	pText_->Draw(30,30,result.c_str());

}

//�J��
void TestScene::Release()
{
}
