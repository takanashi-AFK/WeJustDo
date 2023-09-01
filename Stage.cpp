#include "Stage.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent, string modelFileName)
	:SolidObject(parent,modelFileName,"Stage")
{
}

void Stage::ChildInitialize()
{
	Model::SetAnimFrame(hModel_, 0, 150, 1);
}

//�X�V
void Stage::ChildUpdate()
{
}

//�`��
void Stage::ChildDraw()
{
	//debug-���C���[�t���[���\���̃V�F�[�_�[��K�p
	Direct3D::SetShader(Direct3D::SHADER_UNLIT);
}
