#include "ItemCounter.h"
#include "Player.h"
#include "Engine/Text.h"
#include <cstdio>//�t�H�[�}�b�g�w��q���g�p

ItemCounter::ItemCounter(GameObject* parent)
	:GameObject(parent,"ItemCounter")
{
}

void ItemCounter::Initialize()
{
	//�e�L�X�g�̏�����
	ASSIGN(pText_, new Text);
	pText_->Initialize("Fonts/QuizFont_number.png", 64, 68, 15);

	//�摜�̏�����
	ASSIGN(hPict_, Image::Load("Image/ItemFlame.png"));
}

void ItemCounter::Update()
{
}

void ItemCounter::Draw()
{
	//�t���[���̕`��
	Transform t_flame;
	t_flame.scale_ = { 0.12f, 0.12f, 1.0f };
	t_flame.position_ = { 0.45f,0.875f,0.0f };
	Image::SetTransform(hPict_, t_flame);
	Image::Draw(hPict_);

	//�e�L�X�g�̕`��
	{
		//�v���C���[���(�d�̐�)���擾
		Player* p = (Player*)FindObject("Player");
		int n_firewood = 0; if (p)n_firewood = p->GetFirewoodNum();

		// �[�����߂̃t�H�[�}�b�g�w��q���g�p���ĕ�����𐶐�
		char buffer[8];//������+1���̔z��T�C�Y
		_snprintf_s(buffer, sizeof(buffer), "%03d", n_firewood/5);
		std::string result = (std::string)buffer;

		pText_->SetScale(0.6f);
		pText_->Draw(917.5, 50, result.c_str());
	}
}

void ItemCounter::Release()
{
}
