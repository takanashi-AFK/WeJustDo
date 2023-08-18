#pragma once
#include "Engine/SolidObject.h"

#include <vector>
#include "Block.h"
//定数
namespace
{
	static float BLOCK_SIZE = 1.0f;				    //ブロックのサイズ
	static XMFLOAT3 PLAYER_MODEL_SIZE = { 1,1,1 };  //PlayerのXのモデルサイズ
}

namespace StageManager	//継承はしない
{

	//ステージに存在するブロックの情報を格納するリスト
	std::vector<Block*> tBlock_;


	/// <summary>
	/// ステージを作成
	/// </summary>
	/// <param name="parent">親オブジェクト</param>
	void CreateStage(GameObject* parent);

	/// <summary>
	/// ブロックとの当たり判定に使う
	/// </summary>
	enum BlockHitTest{
		Right = 0,     //右
		Left,          //左
		Under,         //下
		Top,           //上
	};

	bool IsBlock(XMFLOAT3* pos,int s);
};

