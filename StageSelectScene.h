#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

class StageSelectScene :
    public GameObject
{
private:
	int hPict_[4];
	int	hPict_2;
	int count;//A,Dキーを押したときに変わる変数
	int numStage; //ステージの数をここに。
	XMFLOAT3 posX; //カーソルの移動はここ
	Transform CursorTransform_;

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
};

