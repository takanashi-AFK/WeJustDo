#include "DebugObject.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"

DebugObject::DebugObject(GameObject* parent, string modelFileName)
	:SolidObject(parent,modelFileName,"DebugObject")
{
}

void DebugObject::ChildInitialize()
{
	
}

void DebugObject::ChildUpdate()
{
	//ÉLÅ[ëÄçÏ
	HandleInput();

	//ÉJÉÅÉâ
	Camera::SetPosition(transform_.position_.x,transform_.position_.y, -12.7+transform_.position_.z);
	Camera::SetTarget(transform_.position_.x, transform_.position_.y, 7.3f);
}

void DebugObject::ChildDraw()
{
	Direct3D::SetShader(Direct3D::SHADER_UNLIT);
}

void DebugObject::HandleInput()
{
	if (Input::IsKey(DIK_W))transform_.position_.y += 0.1f;
	if (Input::IsKey(DIK_S))transform_.position_.y -= 0.1f;
	if (Input::IsKey(DIK_A))transform_.position_.x -= 0.1f;
	if (Input::IsKey(DIK_D))transform_.position_.x += 0.1f;
	if (Input::IsKey(DIK_UP))transform_.position_.z += 0.1f;
	if (Input::IsKey(DIK_DOWN))transform_.position_.z -= 0.1f;

}
