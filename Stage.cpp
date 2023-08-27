#include "Stage.h"
#include "Engine/Input.h"

Stage::Stage(GameObject* parent, string modelFileName)
	:SolidObject(parent,modelFileName,"Stage")
{
}

void Stage::ChildUpdate()
{
	/*if (Input::IsKey(DIK_W))transform_.position_.y += 0.1f;
	if (Input::IsKey(DIK_S))transform_.position_.y -= 0.1f;*/
}

void Stage::ChildDraw()
{
	Direct3D::SetShader(Direct3D::SHADER_UNLIT);
}
