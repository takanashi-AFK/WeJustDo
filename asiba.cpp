#include "asiba.h"
#include "Engine/Model.h"
//コンストラクタ
asiba::asiba(GameObject* parent)
	: GameObject(parent, "asiba")
{
}

//初期化
void asiba::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("asiba.fbx");
	assert(hModel_ >= 0);

	transform_.position_.y = 3.0f;
	transform_.position_.x = 7.0f;
}

//更新
void asiba::Update()
{
}

//描画
void asiba::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void asiba::Release()
{
}
