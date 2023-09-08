#include "TestScene.h"
#include "Engine/Text.h"

#include <cstdio>//フォーマット指定子を使用

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"),flame_(0),pText_(nullptr)
{
}

//初期化
void TestScene::Initialize()
{
	//制限時間をセット/秒
	SetSeconds(20);

	//Textの初期化
	pText_ = new Text;
	pText_->Initialize();
}

//更新
void TestScene::Update()
{
	//フレームを更新
	flame_--;
}

//描画
void TestScene::Draw()
{
	if (flame_ < 0)return;//0以下になったら描画をやめる

	// ゼロ埋めのフォーマット指定子を使用して文字列を生成
	char buffer[4];//文字数+1分の配列サイズ
	snprintf(buffer, sizeof(buffer), "%03d", flame_ / 60);

	//文字を描画
	std::string result = "time : " + (std::string)buffer;
	pText_->Draw(30,30,result.c_str());

}

//開放
void TestScene::Release()
{
}
