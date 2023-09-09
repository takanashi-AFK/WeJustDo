#include "Timer.h"
#include "Engine/Image.h"
#include "Engine/Text.h"

#include <cstdio>//フォーマット指定子を使用

static const int FPS = 60;//フレームレート

Timer::Timer(GameObject* obj)
	: GameObject(obj, "Timer"), frame_(0), limitActive_(false),countActive_(false), pText_(nullptr),
	drawPosX_(0),drawPosY_(0)
{
}

void Timer::Initialize()
{
	//テキストの初期化
	pText_ = new Text;
	pText_->Initialize();

	//描画位置.サイズの初期化
	SetDrawPosition(1150, 100);
	SetDrawSize(1.5f);
}

void Timer::Update()
{
	//どっちもActiveだとだめだからエラーチェック
	if (limitActive_ && countActive_)return;

	if (limitActive_)frame_--;//カウントダウン
	if (countActive_)frame_++;//カウントアップ
}

void Timer::Draw()
{
	// ゼロ埋めのフォーマット指定子を使用して文字列を生成
	char buffer[4];//文字数+1分の配列サイズ
	snprintf(buffer, sizeof(buffer), "%03d", GetTime_Seconds());
	std::string result = (std::string)buffer;
	
	float tx_defaultSize = 1.5f;//テキストサイズ

	//通常時の描画
	SetDrawSize(tx_defaultSize);

	//10秒以下になったら
	if (GetTime_Seconds() <= 10)
	{
		//frame_を FPS（フレームレート）で割った余りが10未満だったら
		if (frame_ % FPS < 10)
			SetDrawSize((frame_ % FPS) * 0.1f + 1.0f);
		else
			SetDrawSize(tx_defaultSize);
		pText_->Draw(drawPosX_, drawPosY_, result.c_str());
	}
	else
		pText_->Draw(drawPosX_, drawPosY_, result.c_str());
	
}

void Timer::Release()
{
	//テキストを開放
	delete pText_;
}

void Timer::Start(bool _flag)
{
	//trueならカウントダウンを開始
	if (_flag) { limitActive_ = true; return; }
	//falseならカウントアップを開始
	countActive_ = true;
}

void Timer::Stop(bool _flag)
{
	//trueならカウントダウンを停止
	if (_flag) { limitActive_ = false; return; }
	//falseならカウントアップを停止
	countActive_ = false;
}

bool Timer::IsFinished()
{
	//０以下になったらtrueを返す
	return (frame_ <= 0);
}

bool Timer::IsFinished(int _s)
{
	//_s 以上になったらtrueを返す
	return (frame_ >= _s);
}

void Timer::SetDrawSize(float _size)
{
	pText_->SetScale(_size);
}
