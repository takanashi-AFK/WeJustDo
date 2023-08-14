#pragma once
#include "Engine/SolidObject.h"
class TestObject : public SolidObject
{
	bool isFlag_;
public:
	TestObject(GameObject* _parent, string _modelFileName);
	void ChildInitialize() override;
	void ChildUpdate() override;
	void ChildDraw() override;
	void ChildRelease() override;
	
	void IsMove(bool f) { isFlag_ = f; }
};

