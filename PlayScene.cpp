#include "PlayScene.h"

//インクルード
#include "Player.h"
#include "Stage.h"
#include "Engine/Image.h"
#include "Engine/Camera.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene"),hPict_(-1)
{
}

//初期化
void PlayScene::Initialize()
{
	//背景を生成
	ASSIGN(hPict_, Image::Load("Image/BackGround4.png"));{

	}

	//ステージを生成
	CreateSolidObject<Stage>(this,"Models/stage100.fbx");{

	}

	//プレイヤーを生成
	CreateSolidObject<Player>(this,"Models/ziro2.fbx");{

	}

}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
	//背景画像を描画
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

}

//開放
void PlayScene::Release()
{
}
