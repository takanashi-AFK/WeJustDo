#pragma once
#include "Engine/SolidObject.h"
class TestObject : public SolidObject
{
public:
	TestObject(GameObject* _parent, string _modelFileName);
	void ChildInitialize() override;
	void ChildUpdate() override;
	void ChildDraw() override;
	void ChildRelease() override;

};

