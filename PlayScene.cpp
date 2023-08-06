#include "PlayScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

#include "TestPlayer.h"
#include "TestStage.h"
#include "backGround.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{
}

void PlayScene::Initialize()
{
	Instantiate<backGround>(this);
	Instantiate<TestPlayer>(this);
	Instantiate<TestStage>(this);

}

void PlayScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_END, TID_WHITEOUT);
	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
