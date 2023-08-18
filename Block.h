#pragma once
#include "Engine/SolidObject.h"

/// <summary>
/// BlockObject‚ÌŠî’êƒNƒ‰ƒX
/// </summary>
class Block : public SolidObject
{
protected:
	bool isHit_;
public:
	Block(GameObject* parent,string modelFileName,string name);

	void ChildInitialize() override;
	void ChildUpdate() override;
	void ChildDraw() override;
	void ChildRelease() override;

	virtual void BlockChildInitialize(){}
	virtual void BlockChildUpdate(){}
	virtual void BlockChildDraw(){}
	virtual void BlockChildRelease(){}

	void SetIsHit(const bool& flag) { isHit_ = flag; }

};

