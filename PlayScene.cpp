#include "PlayScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

#include "TestPlayer.h"
#include "TestStage.h"
#include "backGround.h"
#include "Player/Player.h"


PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene"),pText(nullptr)
{
}

void PlayScene::Initialize()
{
	Instantiate<backGround>(this);
	//Instantiate<Player>(this);
	Instantiate<TestPlayer>(this);
	Instantiate<TestStage>(this);
	pText = new Text;
	pText->Initialize("JiyuuFont.png", 32, 64, 92);


}

void PlayScene::Update()
{/*
	Player* Pla = (Player*)FindObject("Player");
	if (Pla->GetPosition().y <= -20.0f) {
		SceneManager* Sm = (SceneManager*)FindObject("SceneManager");
		Sm->ChangeScene(SCENE_ID_END, TID_WHITEOUT);
	}*/


	TestPlayer* Tp = (TestPlayer*)FindObject("TestPlayer");
	if (Tp->GetPosition().y <= -20.0f) {
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_END, TID_WHITEOUT);
	}
}

void PlayScene::Draw()
{
	int hp = 100;

	pText->Draw(0, 1, hp);
}

void PlayScene::Release()
{
	pText->Release();
}
