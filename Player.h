#pragma once
#include "Engine/SolidObject.h"
#include "PlayerStateManager.h"

/// <summary>
/// Playerの基底クラス
/// </summary>
class Player : public SolidObject
{
protected:
	///// 必要な情報 ////////////////////////////////////////
	PlayerStateManager* pState_;	//Playerの状態管理
public:
	//コンストラクタ
	Player(GameObject* _parent, string _modelFileName);

	//継承{初期化・更新・開放}
	void ChildInitialize() override;
	void ChildUpdate() override;
	void ChildRelease() override;

	///// 必要な関数 //////////////////////////////////////// 

	/// <summary>
	/// 状態を取得
	/// </summary>
	/// <returns>状態</returns>
	PlayerStateManager* GetState(){return pState_;};
};
