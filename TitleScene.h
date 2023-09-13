#pragma once
#include "Engine/GameObject.h"

class Button;

//タイトルシーンを管理するクラス
class TitleScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
private:
	Button* start;
	Button* back;
	enum SELECT {
		NONE = -1,
		START = 0,
		BACK,
	};
	SELECT selected;
};