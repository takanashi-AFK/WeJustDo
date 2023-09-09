#include "ItemCounter.h"
#include "Player.h"
#include "Engine/Text.h"
#include <cstdio>//フォーマット指定子を使用

ItemCounter::ItemCounter(GameObject* parent)
	:GameObject(parent,"ItemCounter")
{
}

void ItemCounter::Initialize()
{
	//テキストの初期化
	ASSIGN(pText_, new Text);
	pText_->Initialize("Fonts/QuizFont_number.png", 64, 68, 15);

	//画像の初期化
	ASSIGN(hPict_, Image::Load("Image/ItemFlame.png"));
}

void ItemCounter::Update()
{
}

void ItemCounter::Draw()
{
	//フレームの描画
	Transform t_flame;
	t_flame.scale_ = { 0.12f, 0.12f, 1.0f };
	t_flame.position_ = { 0.45f,0.875f,0.0f };
	Image::SetTransform(hPict_, t_flame);
	Image::Draw(hPict_);

	//テキストの描画
	{
		//プレイヤー情報(薪の数)を取得
		Player* p = (Player*)FindObject("Player");
		int n_firewood = 0; if (p)n_firewood = p->GetFirewoodNum();

		// ゼロ埋めのフォーマット指定子を使用して文字列を生成
		char buffer[8];//文字数+1分の配列サイズ
		_snprintf_s(buffer, sizeof(buffer), "%03d", n_firewood/5);
		std::string result = (std::string)buffer;

		pText_->SetScale(0.6f);
		pText_->Draw(917.5, 50, result.c_str());
	}
}

void ItemCounter::Release()
{
}
