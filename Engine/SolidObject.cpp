#include "SolidObject.h"
#include "Model.h"

SolidObject::SolidObject(GameObject* _parent, string _modelFileName, string name)
	:GameObject(_parent,name),modelFileName_(_modelFileName),hModel_(-1)
{
	//トランスフォームコンポーネントを追加
	//ASSIGN(transform_, new Transform);
}

SolidObject::~SolidObject()
{
}

void SolidObject::Initialize()
{
	//モデルのロード
	ASSIGN(hModel_, Model::Load(modelFileName_));
	assert(hModel_ >= 0);

	//継承先の初期化
	ChildInitialize();
}

void SolidObject::Update()
{
	//継承先の更新
	ChildUpdate();
}

void SolidObject::Draw()
{
	//継承先の描画
	ChildDraw();

	//モデルの描画
	Model::SetTransform(hModel_,transform_);
	Model::Draw(hModel_);

	PolyDraw();

	//シェーダーのリセット
	Direct3D::SetShader(Direct3D::SHADER_3D);
}

void SolidObject::Release()
{
	//継承先の開放
	ChildRelease();

	//トランスフォームコンポーネントの開放
	//SAFE_DELETE(transform_);
}

void SolidObject::PolyDraw()
{
}
