#include "ResultScene.h"

//インクルード
#include "Engine/Image.h"

//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	:GameObject(parent,"ResultScene"),hPict_(-1)
{
}

//初期化
void ResultScene::Initialize()
{
	//画像のロード
	ASSIGN(hPict_, Image::Load("Image/ResultImage.png"));assert(hPict_ <= 0);
}

//更新
void ResultScene::Update()
{
}

//描画
void ResultScene::Draw()
{
	//画像の描画
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}
