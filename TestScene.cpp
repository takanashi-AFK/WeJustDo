#include "TestScene.h"
#include "Stage.h"
#include "Player.h"
#include "DebugObject.h"
#include "Engine/Image.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	pText_ = new Text;
	pText_->Initialize();

	//Stage Create
	Instantiate<Stage>(this);

	//Player Create
	p_ = CreateSolidObject<Player>(this, "Models/ziro_move.fbx"); {
		//p->SetIsMove(false); 
	}

	//DebugObject Create
	//CreateSolidObject<DebugObject>(this, "Models/defaultModel.fbx");

	ASSIGN(hPict_, Image::Load("Image/BackGround4.png"));
}

//更新
void TestScene::Update()
{
}

//描画
void TestScene::Draw()
{
	pText_->Draw(30, 30, p_->GetFirewoodNum()/5);
	//Image::SetRect(hPict_, );
	Transform t_bg; t_bg.scale_ = { 1.4f,1.4f,1.4f };
	Image::SetTransform(hPict_, t_bg);
	Image::Draw(hPict_);
}

//開放
void TestScene::Release()
{
}
