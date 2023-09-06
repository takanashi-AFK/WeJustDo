#include "TestScene.h"
#include "Stage.h"
#include "Player.h"
#include "Engine/Image.h"

//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//‰Šú‰»
void TestScene::Initialize()
{
	//”wŒi‚ğ¶¬
	ASSIGN(hPict_, Image::Load("Image/BackGround4.png")); {

	}
	//Stage Create
	Instantiate<Stage>(this);

	//Player Create
	CreateSolidObject<Player>(this, "Models/ziro_move.fbx");
}

//XV
void TestScene::Update()
{
}
//•`‰æ
void TestScene::Draw()
{
	//”wŒi‰æ‘œ‚ğ•`‰æ
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//ŠJ•ú
void TestScene::Release()
{
}
