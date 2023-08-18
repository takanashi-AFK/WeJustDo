#pragma once
#include "Engine/SolidObject.h"
class Stage : public SolidObject
{
	bool isFlag_;
public:
	Stage(GameObject* _parent, string _modelFileName);
	void ChildInitialize() override;
	void ChildUpdate() override;
	void ChildDraw() override;
	void ChildRelease() override;

	void IsMove(bool f) { isFlag_ = f; }
};

