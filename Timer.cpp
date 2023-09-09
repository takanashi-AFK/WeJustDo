#include "Timer.h"
#include "Engine/Image.h"
#include "Engine/Text.h"

#include <cstdio>//�t�H�[�}�b�g�w��q���g�p

static const int FPS = 60;//�t���[�����[�g

namespace {
	const XMFLOAT3 FLAME_SIZE = { 0.12f,0.12f,1.0f };
	const XMFLOAT3 FLAME_POSITION = { 0.8f,0.875f,0.0f };
}	

Timer::Timer(GameObject* obj)
	: GameObject(obj, "Timer"), frame_(0), limitActive_(false),countActive_(false), pText_(nullptr),
	drawPosX_(0),drawPosY_(0)
{
}

void Timer::Initialize()
{
	//�e�L�X�g�̏�����
	ASSIGN(pText_, new Text);
	pText_->Initialize("Fonts/QuizFont_number.png", 64, 68, 15);

	//�摜�̏�����
	ASSIGN(hTimerFlame_, Image::Load("Image/TimerFlame2.png"));

	//�`��ʒu.�T�C�Y�̏�����
	SetDrawPosition(1140, 50);
	SetDrawSize(0.6f);
}

void Timer::Update()
{
	//�ǂ�����Active���Ƃ��߂�����G���[�`�F�b�N
	if (limitActive_ && countActive_)return;

	if (limitActive_)frame_--;//�J�E���g�_�E��
	if (countActive_)frame_++;//�J�E���g�A�b�v
}

void Timer::Draw()
{
	//�^�C�}�[�t���[���̕\��
	Transform t_Flame; {
		t_Flame.scale_ = FLAME_SIZE;
		t_Flame.position_ = FLAME_POSITION;
		Image::SetTransform(hTimerFlame_, t_Flame);
		Image::Draw(hTimerFlame_);
	}
	
	// �[�����߂̃t�H�[�}�b�g�w��q���g�p���ĕ�����𐶐�
	char buffer[4];//������+1���̔z��T�C�Y
	snprintf(buffer, sizeof(buffer), "%03d", GetTime_Seconds());
	std::string result = (std::string)buffer;

	//�ʏ펞�̕`��
	SetDrawSize(GetDrawSize());

	//10�b�ȉ��ɂȂ�����
	if (GetTime_Seconds() <= 10)
	{
		//frame_�� FPS�i�t���[�����[�g�j�Ŋ������]�肪10������������
		if (frame_ % FPS < 10)
			SetDrawSize((frame_ % FPS) * 0.1f + 1.0f);
		else
			SetDrawSize(0.6f);
		pText_->Draw(drawPosX_, drawPosY_, result.c_str());
	}
	else
		pText_->Draw(drawPosX_, drawPosY_, result.c_str());
	
	

}

void Timer::Release()
{
	//�e�L�X�g���J��
	delete pText_;
}

void Timer::Start(bool _flag)
{
	//true�Ȃ�J�E���g�_�E�����J�n
	if (_flag) { limitActive_ = true; return; }
	//false�Ȃ�J�E���g�A�b�v���J�n
	countActive_ = true;
}

void Timer::Stop(bool _flag)
{
	//true�Ȃ�J�E���g�_�E�����~
	if (_flag) { limitActive_ = false; return; }
	//false�Ȃ�J�E���g�A�b�v���~
	countActive_ = false;
}

bool Timer::IsFinished()
{
	//�O�ȉ��ɂȂ�����true��Ԃ�
	return (frame_ <= 0);
}

bool Timer::IsFinished(int _s)
{
	//_s �ȏ�ɂȂ�����true��Ԃ�
	return (frame_ >= _s);
}

void Timer::SetDrawSize(float _size)
{
	drawSize_ = _size;
	pText_->SetScale(_size);
}
