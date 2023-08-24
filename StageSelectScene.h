#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

class StageSelectScene :
    public GameObject
{
private:
	//スクリーンの大きさをとってくる
	int screenWidth = GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini");		//スクリーンの幅
	int screenHeight = GetPrivateProfileInt("SCREEN", "Height", 600, ".\\setup.ini");	//スクリーンの高さ

	int hPict_[4];
	int	hPict_2;
	int count;//A,Dキーを押したときに変わる変数
	XMFLOAT3 posX; //カーソルの移動はここ

	Text* pText;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	StageSelectScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	/// <summary>
	///	画像を均等に設置します。
	/// </summary>
	/// <param name="_num">画像の枚数をここに入れます</param>
	/// <param name="_pos">GameObject Transform::transform_.xをポインタで渡します</param>
	void CalcPosition(int _num,float* _pos);
};

