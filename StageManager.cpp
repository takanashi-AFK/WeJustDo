#include "StageManager.h"
#include "TestObject.h"
#include "Stage.h"
#include <vector>

namespace StageManager
{
	CsvReader CsvFile_;
	int vertical;
	int horizontal;
	vector<vector<int>> Table_;

	int YHeight = -7;

	SolidObject* p1;
	SolidObject* p2;
	SolidObject* p3;
}

enum BlockPattern
{
	Block_Null = 0,
	Block_Grass = 1,
	Block_Soil = 2,
	Block_FireWood = 3
};
void StageManager::CreateStage(GameObject* parent)
{

	///// setting Object1 ///////////////////////////////////////////////////////
	p1 = CreateSolidObject<TestObject>(parent, "Models/kusaBlock.fbx");
	{
		dynamic_cast<TestObject*>(p1)->IsMove(false);
		p1->SetPositionX(-2.0f);
	}

	///// setting Object2 ///////////////////////////////////////////////////////
	for (int i = 0; i < 250; i++) {
		 p2 = CreateSolidObject<TestObject>(parent, "Models/kusaBlock.fbx");
		p2->SetPositionX(i);
	}
}

void StageManager::CreateStage(GameObject* parent, string _filename)
{
	CsvFile_.Load(_filename);

	vertical = CsvFile_.GetHeight();
	horizontal = CsvFile_.GetWidth();

	Table_.resize(horizontal, vector<int>(vertical, 0));
	for (int x = 0; x < horizontal; x++)
		for (int y = 0; y < vertical; y++)
			Table_[x][y] = CsvFile_.GetValue(x, ((vertical - 1) - y));

	for (int x = 0; x < horizontal; x++)
	{
		for (int y = 0; y < vertical; y++)
		{
			if (Table_[x][y] == Block_Grass)
			{
				p1 = CreateSolidObject<Stage>(parent, "Models/kusaBlock.fbx");
				{
					dynamic_cast<Stage*>(p1);
					p1->SetPositionX(x);
					p1->SetPositionY(y + YHeight);
				}
				
			}
			else if (Table_[x][y] == Block_Soil)
			{
				 p2 = CreateSolidObject<Stage>(parent, "Models/SoilBlock.fbx");

				dynamic_cast<Stage*>(p2);
				p2->SetPositionX(x);
				p2->SetPositionY(y + YHeight);
			
			}

			else if (Table_[x][y] == Block_FireWood)
			{
				p3 = CreateSolidObject<Stage>(parent, "Models/rengaBlock.fbx");
				{
					dynamic_cast<Stage*>(p3);
					p3->SetPositionX(x);
					p3->SetPositionY(y + YHeight);
				}
				
				
			}
		}
	}

}

void StageManager::DeleteStage()
{
	 p1->KillMe();
	 p2->KillMe();
	 p3->KillMe();
	
}



void StageManager::StageTableRelease()
{
	Table_.clear();
	std::vector<std::vector<int>>().swap(Table_);
}


