#pragma once
#include "Engine/SolidObject.h"
class DebugObject : public SolidObject
{
public:
	DebugObject(GameObject* parent, string modelFileName);
	void ChildInitialize() override;
	void ChildUpdate() override;
	void ChildDraw() override;

	void HandleInput();
};

