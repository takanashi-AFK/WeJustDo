#include "Stage.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent, string modelFileName)
	:SolidObject(parent,modelFileName,"Stage")
{
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
