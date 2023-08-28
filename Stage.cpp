#include "Stage.h"

//コンストラクタ
Stage::Stage(GameObject* parent, string modelFileName)
	:SolidObject(parent,modelFileName,"Stage")
{
}

//更新
void Stage::ChildUpdate()
{
}

//描画
void Stage::ChildDraw()
{
	//debug-ワイヤーフレーム表示のシェーダーを適用
	Direct3D::SetShader(Direct3D::SHADER_NOSHADE);
}
