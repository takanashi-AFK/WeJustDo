#pragma once

//前方宣言
class GameObject;

/// <summary>
/// コンポーネント基底クラス
/// </summary>
class Component
{
public:
	GameObject* parent;	//親オブジェクト
public:
	//コンストラクタ
	Component():parent(nullptr){}

    //デストラクタ
    virtual ~Component() {}

    //初期化(最初の一回だけ呼ばれる)
    virtual void Initialize() {}

    //更新
    virtual void Update() {}

    //描画
    virtual void Draw() {}
};