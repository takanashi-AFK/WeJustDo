#pragma once
#include "GameObject.h"

/// <summary>
/// 立体的なオブジェクトの基底クラス
/// </summary>
class SolidObject :public GameObject
{
protected:
	//共通する情報		///////////////////

	int hModel_;                     //モデル番号
	std::string modelFileName_;      //ファイルネームパス
public:
	// コンストラクタ
	SolidObject(GameObject* _parent, string _modelFileName, string name);

	// デストラクタ
	~SolidObject();

	// {初期化・更新・描画・開放}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	// {初期化・更新・描画・開放}<継承先用>
	virtual void ChildInitialize() {};
	virtual void ChildUpdate() {};
	virtual void ChildDraw() {};
	virtual void ChildRelease() {};


	virtual void PolyDraw() {};
	/// <summary>
	/// モデル番号を取得する
	/// </summary>
	/// <returns>モデル番号</returns>
	int GetModelHandle() { return hModel_; }

	/// <summary>
	/// addressを取得
	/// </summary>
	/// <returns></returns>
	Transform* GetTransformAddress() { return &transform_; }
};

//立体的なオブジェクトの生成
template <class T>
T* CreateSolidObject(GameObject* _parent, string _modelFileName)
{
	T* newObject = new T(_parent,_modelFileName);
	if (_parent != nullptr)
	{
		_parent->PushBackChild(newObject);
	}
	newObject->Initialize();
	return newObject;
}
