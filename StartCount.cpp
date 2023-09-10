#include "StartCount.h"
#include "Timer.h"
#include "Engine/Image.h"
#include "AudioManager.h"
#include <string>

StartCount::StartCount(GameObject* obj)
	:GameObject(obj,"StartCount"),isfinished_(false),hPict_{},pTimer_(nullptr)
{
}

void StartCount::Initialize()
{
	//�^�C�}�[�𐶐�
	pTimer_ = Instantiate<Timer>(this); {
		pTimer_->IsDraw(false);
		pTimer_->Start(false);
	}

	//�摜�����[�h
	for (int i = 0; i < 4; i++){
		hPict_[i] = Image::Load("Image/Count" + std::to_string(i) + ".png");
	}
	transform_.scale_ = { 0.5f,0.5f,1.0f };
}

void StartCount::Update()
{
	//�R�D�Q�D�P�DStart..(4Count)�܂ł�������I��
	if (pTimer_->IsFinished(4 + 1)) {
		isfinished_ = true;
		pTimer_->Stop(false);
	}
}

void StartCount::Draw()
{
	//�摜��`��
	CountDraw(pTimer_->GetTime_Seconds());
}

void StartCount::Release()
{
}

bool StartCount::IsFinished()
{
	//�I���������ǂ�����Ԃ�
	return isfinished_;
}

void StartCount::CountDraw(int time)
{
	//�I�����Ă�����Ȍ�͍s��Ȃ�
	if (isfinished_)return;

	//�e�b�����Ƃɉ摜��`��
	if (time == 1){
		Image::SetTransform(hPict_[3], transform_);
		Image::Draw(hPict_[3]);
		AudioManager::Play_DonSound();
	}
	else if (time == 2){
		Image::SetTransform(hPict_[2], transform_);
		Image::Draw(hPict_[2]);
		AudioManager::Play_DonSound();
	}
	else if (time == 3){
		Image::SetTransform(hPict_[1], transform_);
		Image::Draw(hPict_[1]);
		AudioManager::Play_DonSound();
	}
	else if (time == 4){
		Image::SetTransform(hPict_[0], transform_);
		Image::Draw(hPict_[0]);
	}
}