#include "SkySphere.h"
#include "Engine/Model.h"

SkySphere::SkySphere(GameObject* parent)
	:GameObject(parent,"SkySpheere")
{
}

void SkySphere::Initialize()
{
	ASSIGN(hModel_, Model::Load("Models/SkySphere/BackGround.fbx"));
	assert(hModel_ <= 0);
}

void SkySphere::Update()
{
}

void SkySphere::Draw()
{
	Model::SetTransform(hModel_,)
}
