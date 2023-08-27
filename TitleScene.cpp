#include "TitleScene.h"

//インクルード
#include "Engine/Image.h"	//画像の表示の為
#include "Engine/Model.h"	//モデルの表示の為
#include "Engine/SceneManager.h"	//シーン遷移の為
#include "Engine/Input.h"	//シーン遷移の為
#include "Engine/Camera.h"	//カメラの位置更新の為
#include "AudioManager.h"	//BGMを流す為

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene"),hPict_(-1),hModel_(-1)
{
}

//初期化
void TitleScene::Initialize()
{
	//モデルのロード
	ASSIGN(hModel_, Model::Load("Models/SkySphere/BackGroundModel.fbx")); assert(hModel_ <= 0);
	
	//画像のロード
	ASSIGN(hPict_, Image::Load("Image/TitleImage2.png")); assert(hPict_ <= 0);

	//カメラの初期化
	Camera::SetPosition(0, 0, -5);Camera::SetTarget(0, 0, 0);

	//BGMを再生
	AudioManager::Initialize();
	AudioManager::Play_TitleMusic();
}

//更新
void TitleScene::Update()
{
	//スペースキーの入力時...
	if (Input::IsKeyDown(DIK_SPACE)) {
		//シーン遷移を行う
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_PLAY, TID_WHITEOUT);
	}

	//SkySphereモデルを回転させる
	transform_.rotate_.y += 0.05f;
}

//描画
void TitleScene::Draw()
{
	//影無しシェーダーを適用
	Direct3D::SetShader(Direct3D::SHADER_NOSHADE);

	//モデルを描画
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	
	//画像を描画
	Transform t;
	Image::SetTransform(hPict_, t);
	Image::Draw(hPict_);

	//シェーダーをリセット
	Direct3D::SetShader(Direct3D::SHADER_3D);
}
