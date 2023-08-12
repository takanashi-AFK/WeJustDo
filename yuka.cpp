#include "yuka.h"
#include "Engine/Model.h"
//コンストラクタ
yuka::yuka(GameObject* parent)
	: GameObject(parent, "yuka")
{
}

//初期化
void yuka::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("yuka.fbx");
	assert(hModel_ >= 0);
	transform_.position_.y = -2.0f;
}

//更新
void yuka::Update()
{
}

//描画
void yuka::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void yuka::Release()
{
}
