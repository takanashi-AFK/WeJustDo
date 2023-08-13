#include "TestObject.h"
#include "Engine/Input.h"

TestObject::TestObject(GameObject* _parent, string _modelFileName)
	:SolidObject(_parent,_modelFileName,"TestObject")
{
}

void TestObject::ChildInitialize()
{
}

void TestObject::ChildUpdate()
{
	if (Input::IsKey(DIK_D))transform_.position_.x+=0.1f;
	if (Input::IsKey(DIK_A))transform_.position_.x-=0.1f;
}

void TestObject::ChildDraw()
{
}

void TestObject::ChildRelease()
{
}
