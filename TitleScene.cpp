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
	ASSIGN(hPict2_, Image::Load("Image/PleseToSpaceKey.png"));
	ASSIGN(hCreditUi_, Image::Load("Image/CreditUI.png")); 

	//カメラの初期化
	Camera::SetPosition(0, 0, -5);Camera::SetTarget(0, 0, 0);

	
	AudioManager::Play_TitleMusic();
}

//更新
void TitleScene::Update()
{
	
	int s = 1;
	if (increasing_) {
		opacity_+=s;
		if (opacity_ >= 255)increasing_ = false; 
	}
	else {
		opacity_-=s;
		if (opacity_ <= 0)increasing_ = true;
	}
	

	//スペースキーの入力時...
	if (Input::IsKeyDown(DIK_SPACE)) {
		//シーン遷移を行う
		AudioManager::Play_ConfirmSound();
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_TEST, TID_WHITEOUT,1);
	}
	
	//press C to Credit
	if (Input::IsKeyDown(DIK_C)) {
		//シーン遷移を行う
		AudioManager::Play_ConfirmSound();
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_END, TID_WHITEOUT,1);
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
	Transform t_Title; 
	t_Title.scale_ = { 0.8f,0.8f,1.0f };
	t_Title.position_.y = 0.1f;
	Image::SetTransform(hPict_, t_Title);
	Image::Draw(hPict_);

	Transform t_Space;
	t_Space.position_.y = -0.8f;
	Image::SetAlpha(hPict2_, opacity_);
	Image::SetTransform(hPict2_, t_Space);
	Image::Draw(hPict2_);
	
	Transform t_CreditUI;
	t_CreditUI.position_ = { 0.7,0.7,0 };
	t_CreditUI.scale_ = { 0.3,0.3,0.3 };
	Image::SetTransform(hCreditUi_, t_CreditUI);
	Image::Draw(hCreditUi_);	

	//シェーダーをリセット
	Direct3D::SetShader(Direct3D::SHADER_3D);
}
