#pragma once
#include "Engine/SolidObject.h"

/// <summary>
/// プレイ中、ゲーム画面上に表示されるステージオブジェクト
/// </summary>
class Stage : public SolidObject
{
public:
	//コンストラクタ
	Stage(GameObject* parent, string modelFileName);
	
	//継承{更新・描画}
	void ChildInitialize() override;
	void ChildUpdate() override;
	void ChildDraw() override;
};

