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
	//タイマーを生成
	pTimer_ = Instantiate<Timer>(this); {
		pTimer_->IsDraw(false);
		pTimer_->Start(false);
	}

	//画像をロード
	for (int i = 0; i < 4; i++){
		hPict_[i] = Image::Load("Image/Count" + std::to_string(i) + ".png");
	}
	transform_.scale_ = { 0.5f,0.5f,1.0f };
}

void StartCount::Update()
{
	//３．２．１．Start..(4Count)までいったら終了
	if (pTimer_->IsFinished(4 + 1)) {
		isfinished_ = true;
		pTimer_->Stop(false);
	}
}

void StartCount::Draw()
{
	//画像を描画
	CountDraw(pTimer_->GetTime_Seconds());
}

void StartCount::Release()
{
}

bool StartCount::IsFinished()
{
	//終了したかどうかを返す
	return isfinished_;
}

void StartCount::CountDraw(int time)
{
	//終了していたら以後は行わない
	if (isfinished_)return;

	//各秒数ごとに画像を描画
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