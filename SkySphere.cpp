#include "SkySphere.h"
#include "Engine/Model.h"
#include "Engine/Direct3D.h"
#include "Engine/Image.h"

SkySphere::SkySphere(GameObject* parent)
	:GameObject(parent,"SkySphere"),hModel_(-1)
{
}

void SkySphere::Initialize()
{
	hPict_ = Image::Load("TitleIMage.png");
	hModel_ = Model::Load("Models/BackGroundModel.fbx");
}

void SkySphere::Update()
{	
	transform_.rotate_.y += 0.1f;
}

void SkySphere::Draw()
{
	Direct3D::SetShader(Direct3D::SHADER_TYPE::SHADER_SKY);
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	Direct3D::SetShader(Direct3D::SHADER_TYPE::SHADER_SKY);

	Transform PictT;
	PictT.scale_ = { 1.2f,1.2f,1.0f };;
	Image::SetTransform(hPict_, PictT);
	Image::Draw(hPict_);

}
