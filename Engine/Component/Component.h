#pragma once

//前方宣言
class GameObject;

/// <summary>
/// コンポーネント基底クラス
/// </summary>
class Component
{
public:
    GameObject* parent_;//親オブジェクト
public:
    //コンストラクタ
    Component() :parent_(nullptr) {}

    //デストラクタ
    virtual ~Component() {}

    //開始(最初の一回だけ呼ばれる)
    virtual void Start() {}

    //更新
    virtual void Update() {}

    //描画
    virtual void Draw() {}
};