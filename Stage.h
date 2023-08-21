#pragma once
#include "Engine/SolidObject.h"
class Stage : public SolidObject
{
public:
	Stage(GameObject* parent, string modelFileName);
	void ChildUpdate() override;
	void ChildDraw() override;
};

