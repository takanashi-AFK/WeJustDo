#pragma once
#include "Engine/GameObject.h"

class Button : public GameObject
{
private:
	int hReleased_;		//モデル番号(押されていない状態の画像)
	int hPressed_;		//モデル番号(押されている状態の画像)

	bool pushed_;		//押されているかどうか
	
	XMFLOAT3 center_;	//画像の中心点
	XMFLOAT3 size_;		//画像のサイズ
public:
	//コンストラクタ
	Button(GameObject* _parent);
	//継承{初期化,更新,描画,解放}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
public:
	//設定：使用する画像
	void SetImage(std::string _released, std::string _pressed);

	//設定：配置する位置
	void SetPosition(int _x, int _y);

	//設定：押されているかどうか
	void Push(bool _pushed);

	//判定：マウスカーソルの位置が画像範囲内かどうか
	void MouseInArea(XMFLOAT3 _mousePos);

	/// <summary>
	/// 移動させる処理
	/// </summary>
	/// <param name="_toX">移動後の座標x</param>
	/// <param name="_toY">移動後の座標y</param>
	/// <param name="_second">移動時間(秒)</param>
	void SetMovePosition(int _toX, int _toY, float _second);
};

