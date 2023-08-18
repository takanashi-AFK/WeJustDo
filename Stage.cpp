#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

Stage::Stage(GameObject* _parent, string _modelFileName)
	:SolidObject(_parent, _modelFileName, "Stage"), isFlag_(true)
{
}

void Stage::ChildInitialize()
{
	//���C�̓����蔻���L���ɂ���
	Model::SetRayFlag(hModel_, true);
}

void Stage::ChildUpdate()
{

}

void Stage::ChildDraw()
{
}

void Stage::ChildRelease()
{
}
