#include "SkySphere.h"
#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Engine/Camera.h"

SkySphere::SkySphere(GameObject* parent)
	:GameObject(parent,"SkySpheere"),hModel_(-1)
{
}

void SkySphere::Initialize()
{
	ASSIGN(hModel_, Model::Load("Models/SkySphere/BackGroundModel.fbx"));
	assert(hModel_ <= 0);

	//‰æ‘œ‚Ìƒ[ƒh
	ASSIGN(hPict_, Image::Load("Image/TitleImage.png"));
	assert(hPict_ <= 0);

	Camera::SetPosition(0, 0, -5);
	Camera::SetTarget(0, 0, 0);
}

void SkySphere::Update()
{
	transform_.rotate_.y += 0.1f;
}

void SkySphere::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	Transform t;
	Image::SetTransform(hPict_, t);
	Image::Draw(hPict_);
}
