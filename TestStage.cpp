#include "TestStage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

TestStage::TestStage(GameObject* parent)
	:GameObject(parent,"TestStage"),hModel_(-1)
{
}

void TestStage::Initialize()
{
	hModel_ = Model::Load("Models/TestStageProvisional3.fbx");
	assert(hModel_ >= 0);

	

}

void TestStage::Update()
{
	//Model::DebugMove(&transform_);
}

void TestStage::Draw()
{
	transform_.position_.x = 46.5f;
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TestStage::Release()
{
}
