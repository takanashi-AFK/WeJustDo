#include "TestObject.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

TestObject::TestObject(GameObject* _parent, string _modelFileName)
	:SolidObject(_parent, _modelFileName, "TestObject"), isFlag_(true)
{
}

void TestObject::ChildInitialize()
{
	//ƒŒƒC‚Ì“–‚½‚è”»’è‚ð—LŒø‚É‚·‚é
	Model::SetRayFlag(hModel_, true);
}

void TestObject::ChildUpdate()
{
	if (isFlag_) {
		if (Input::IsKey(DIK_D))transform_.position_.x+=0.1f;
		if (Input::IsKey(DIK_A))transform_.position_.x-=0.1f;
	}
}

void TestObject::ChildDraw()
{
}

void TestObject::ChildRelease()
{
}
