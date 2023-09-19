
#include "EndScene.h"

//インクルード
#include "Engine/Image.h"	//チームロゴ画像表示の為
#include "Engine/SceneManager.h"//シーン遷移の為
#include "Engine/Input.h"
#include "AudioManager.h"


//コンストラクタ
EndScene::EndScene(GameObject* parent)
	:GameObject(parent, "EndScene"), hPict_(-1)
{
}

//初期化
void EndScene::Initialize()
{
	scroll = -7.9f;
	//画像をロード
	ASSIGN(hPict_, Image::Load("Image/523_20230919225415.png"));
	assert(hPict_ >= 0);
	transform_.scale_ = { 0.8f,0.8f,0.8f };
	transform_.position_.x = -0.1f;
	transform_.position_.y = scroll;

	pText = new Text;
	pText->Initialize();

	AudioManager::Play_TitleMusic();
}

//更新
void EndScene::Update()
{
	static int time = 0;
	static int changeTime = 3;
	static int FPS = 60;
	//画像の文字を上に流していく
	if (scroll <= 7.3f)
	{
		scroll += 0.005f;

		if (Input::IsKey(DIK_SPACE))//Spaceを押すと加速
		{
			scroll += 0.05f;
		}
	}

	//スクロールが終わった時
	if (scroll >= 7.3f)
	{
		time++;
		//３秒たったらシーン遷移
		if (time / FPS >= changeTime) {
			//シーン遷移を行う
			SceneManager* sm = (SceneManager*)FindObject("SceneManager");
			sm->ChangeScene(SCENE_ID_TITLE, TID_BLACKOUT, 1);
		}
	}
	//スクロールさせる
	transform_.position_.y = scroll;
}

//描画
void EndScene::Draw()
{
	//画像を描画
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}