#include "Block.h"
#include "Engine/Model.h"
Block::Block(GameObject* parent, string modelFileName, string name)
	:SolidObject(parent,modelFileName,name)
{
}

void Block::ChildInitialize()
{
	//�R���C�_�[���Z�b�g

	//�����蔻���L����
	Model::SetRayFlag(hModel_, true);

	BlockChildInitialize();

}

void Block::ChildUpdate()
{
	//�����蔻���ݒ�

	//�p����̍X�V
	BlockChildUpdate();
}

void Block::ChildDraw()
{
	BlockChildDraw();
}

void Block::ChildRelease()
{
	BlockChildRelease();
}
