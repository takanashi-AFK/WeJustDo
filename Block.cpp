#include "Block.h"
#include "Engine/Model.h"
Block::Block(GameObject* parent, string modelFileName, string name)
	:SolidObject(parent,modelFileName,name)
{
}

void Block::ChildInitialize()
{
	//コライダーをセット

	//あたり判定を有効化
	Model::SetRayFlag(hModel_, true);

	BlockChildInitialize();

}

void Block::ChildUpdate()
{
	//当たり判定を設定

	//継承先の更新
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
