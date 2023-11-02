#include "SplashScene.h"

//インクルード
#include "Engine/Image.h"	//チームロゴ画像表示の為
#include "Engine/SceneManager.h"//シーン遷移の為

//フレームレート/60fps
const float FPS = 60.0f;

//コンストラクタ
SplashScene::SplashScene(GameObject* parent)
	:GameObject(parent,"SplashScene"),hPict_(-1)
{
}

//初期化
void SplashScene::Initialize()
{
	//画像をロード
	ASSIGN(hPict_,Image::Load("Image/Splash.png"));
	assert(hPict_ >= 0);
}

//更新
void SplashScene::Update()
{
	//必要な変数の宣言・初期化
	static float time = 0;
	static float changeTime = 0.7f;

	//0.7秒経過した時に...
	if (time/FPS >= changeTime) {
		//シーン遷移を行う
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_TITLE,TID_BLACKOUT);
	}
	time++;//時間を進める
}

//描画
void SplashScene::Draw()
{
	//画像を描画
	Image::SetTransform(hPict_,transform_);
	Image::Draw(hPict_);
}


