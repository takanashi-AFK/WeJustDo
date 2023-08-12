#include "PlayScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

#include "TestPlayer.h"
#include "TestStage.h"
#include "backGround.h"
#include "Player/Player.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{
}

void PlayScene::Initialize()
{
	Instantiate<backGround>(this);
	Instantiate<Player>(this);
	//Instantiate<TestPlayer>(this);
	Instantiate<TestStage>(this);

}

void PlayScene::Update()
{
	Player* Pla = (Player*)FindObject("Player");
	if (Pla->GetPosition().y <= -20.0f) {
		SceneManager* Sm = (SceneManager*)FindObject("SceneManager");
		Sm->ChangeScene(SCENE_ID_END, TID_WHITEOUT);
	}


	//TestPlayer* Tp = (TestPlayer*)FindObject("TestPlayer");
	//if (Tp->GetPosition().y <= -20.0f) {
	//	SceneManager* sm = (SceneManager*)FindObject("SceneManager");
	//	sm->ChangeScene(SCENE_ID_END, TID_WHITEOUT);
	//}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
