#include "Stage.h"

Stage::Stage(GameObject* parent, string modelFileName)
	:SolidObject(parent,modelFileName,"Stage")
{
}

void Stage::ChildDraw()
{
	Direct3D::SetShader(Direct3D::SHADER_NOSHADE);
}
