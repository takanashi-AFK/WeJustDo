#include "StageManager.h"
#include "TestObject.h"

void StageManager::CleateStage(GameObject* parent)
{

	///// setting Object1 ///////////////////////////////////////////////////////
	SolidObject* p1 = CreateSolidObject<TestObject>(parent, "Models/kusaBlock.fbx");
	{
		dynamic_cast<TestObject*>(p1)->IsMove(false);
		p1->SetPositionX(-2.0f);
	}

	///// setting Object2 ///////////////////////////////////////////////////////
	for (int i = 0; i < 250; i++) {
		SolidObject* p2 = CreateSolidObject<TestObject>(parent, "Models/kusaBlock.fbx");
		p2->SetPositionX(i);
	}
}
