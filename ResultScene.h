#pragma once
#include "Engine/GameObject.h"
#include "Engine/Global.h"

//前方宣言
class Text;

/// <summary>
/// ゲーム終了後、結果を表示するシーンオブジェクト
/// </summary>
class ResultScene : public GameObject
{
private:
	int hPict_;	//画像番号

	int frameCount_;

	int iTimeScore_ = 123;
	int iFirewoodScore_ = 456;
	int iTotalScore_ = 789;

	Text* tTimeScore_;
	Text* tFirewoodScore_;
	Text* tTotalScore_;



public:
	//コンストラクタ
	ResultScene(GameObject* parent);
	
	//継承{初期化・更新・描画・開放}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override{}
};

