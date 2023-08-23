#include "StageSelectScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//コンストラクタ
StageSelectScene::StageSelectScene(GameObject* parent)
	: GameObject(parent, "StageSelectScene"),hPict_{-1,-1,-1,-1},hPict_2(-1),count(0),posX(-0.8 ,0 ,0)
{
}

//初期化
void StageSelectScene::Initialize()
{
	for(int i = 0; i < 4; i++)
	{
		/*switch (i)
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		*/

		hPict_[i] = Image::Load("Stage01.png");
		transform_.scale_ = { 0.4,0.4,0.4 };
	}
	hPict_2 = Image::Load("Cursor.png");
	transform_.scale_ = { 0.4, 0.4, 0.4 };
	CursorTransform_.position_ = {0,0,0};
	
	//今の数値が分かる文字列。いらない。
	pText = new Text;
	pText->Initialize();
}

//更新
void StageSelectScene::Update()
{
	//A/→　を押したとき
	if (Input::IsKeyDown(DIK_RIGHT))
	count -= 1;

	//D/←　を押したとき
	if (Input::IsKeyDown(DIK_LEFT))
	count += 1;

	switch (count)
	{
	case 0:
		posX.x = -0.8;
		if (Input::IsKeyDown(DIK_SPACE)) {
			SceneManager* sm = (SceneManager*)FindObject("SceneManager");
			sm->ChangeScene(SCENE_ID_PLAY, TID_BLACKOUT);
		}
		break;

	case 1:
		posX.x = -0.3;
		if (Input::IsKeyDown(DIK_SPACE)) {
			SceneManager* sm = (SceneManager*)FindObject("SceneManager");
			sm->ChangeScene(SCENE_ID_PLAY, TID_BLACKOUT);
		}
		break;

	case 2:
		posX.x = 0.2;
		if (Input::IsKeyDown(DIK_SPACE)) {
			SceneManager* sm = (SceneManager*)FindObject("SceneManager");
			sm->ChangeScene(SCENE_ID_PLAY, TID_BLACKOUT);
		}
		break;

	case 3:
		posX.x = 0.7;
		if (Input::IsKeyDown(DIK_SPACE)) {
			SceneManager* sm = (SceneManager*)FindObject("SceneManager");
			sm->ChangeScene(SCENE_ID_PLAY, TID_BLACKOUT);
		}
		break;

		//この下はカーソルの移動をわかりやすくするもの
	case 4:
		count = 0;
		break;

	case -1:
		count = 3;
		break;
	}

	//ここでケースによって設定された座標が記録、反映される
	transform_.position_ = posX;
	Image::SetTransform(hPict_2, transform_);
}

//描画
void StageSelectScene::Draw()
{
	for (int i = 0; i < 4; i++) {
		//transformの計算式　【画面左端(-1)、余白(0.2)、移動量(i*0.5)】
		transform_.position_.x = -1 + 0.2 + i * 0.5;
		Image::SetTransform(hPict_[i],transform_);
		Image::Draw(hPict_[i]);
	}


	Image::Draw(hPict_2);
	//今の値を表示してくれる。いらない。
	pText->Draw(30, 30, count);
}

//開放
void StageSelectScene::Release()
{
}
