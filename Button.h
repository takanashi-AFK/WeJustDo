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

	//動作用変数
	XMFLOAT3 startPos_;	//動作開始地点
	XMFLOAT3 endPos_;	//動作終了地点
	float totalTime_;	//動作にかかる合計時間
	float currentTime_;	//現時点の動作時間
public:
	//コンストラクタ
	Button(GameObject* _parent);
	//継承{初期化,更新,描画,解放}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override{}
public:
	//設定：使用する画像
	void SetImage(std::string _released, std::string _pressed);

	//設定：配置する位置
	void SetPosition(int _x, int _y);

	//設定：押されているかどうか
	void Push(bool _pushed);

	//判定：マウスカーソルの位置が画像範囲内かどうか
	bool MouseInArea(XMFLOAT3 _mousePos);

	/// <summary>
	/// 移動させる処理
	/// </summary>
	/// <param name="_toX">移動後の座標x</param>
	/// <param name="_toY">移動後の座標y</param>
	/// <param name="_second">移動時間(秒)</param>
	void SetMovePosition(int _toX, int _toY, float _second);

	//取得：動作中かどうか
	bool IsMoving();

	/// <summary>
	/// 強制的に移動を終了させる
	/// </summary>
	void ForceMoveEnd();
};

