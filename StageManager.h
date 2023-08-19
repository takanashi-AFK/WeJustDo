#pragma once
#include "Engine/SolidObject.h"
#include "Engine/CsvReader.h"
namespace StageManager	//åpè≥ÇÕÇµÇ»Ç¢
{

	void CreateStage(GameObject* parent);
	void CreateStage(GameObject* parent,string _filename);
	void DeleteStage();
	void StageTableRelease();
};

