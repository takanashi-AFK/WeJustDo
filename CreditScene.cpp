#include "CreditScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "AudioManager.h"

CreditScene::CreditScene(GameObject* parent)
{
}

void CreditScene::Initialize()
{
	ASSIGN(hPict_, Image::Load("Image/Credit.png"));
}

void CreditScene::Update()
{


	if (Input::IsKeyDown(DIK_RETURN))
	{
		AudioManager::Play_ConfirmSound();
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_TITLE, TID_WHITEOUT, 1);
	}
}

void CreditScene::Draw()
{

}

void CreditScene::Release()
{
}
