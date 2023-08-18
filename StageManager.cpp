#include "StageManager.h"
#include "TestObject.h"

void StageManager::CreateStage(GameObject* parent)
{

	///// setting Object1 ///////////////////////////////////////////////////////
	SolidObject* p1 = CreateSolidObject<TestObject>(parent, "Models/kusaBlock.fbx");
	{
		dynamic_cast<TestObject*>(p1)->IsMove(false);
		p1->SetPositionX(-2.0f);
	}

	///// setting Object2 ///////////////////////////////////////////////////////
	for (int i = 0; i < 250; i++) {
		SolidObject* p2 = CreateSolidObject<TestObject>(parent, "Models/kusaBlock.fbx");
		p2->SetPositionX(i);
	}

}


bool isPsoitionHits(XMFLOAT3 p,XMFLOAT3 s,XMFLOAT3 *pos) {
	return p.x + (BLOCK_SIZE * s.x) > pos->x &&
		p.x - (BLOCK_SIZE * s.x) < pos->x &&
		p.y - (BLOCK_SIZE * s.y) < pos->y &&
		p.y + (BLOCK_SIZE * s.y) > pos->y &&
		p.z - (BLOCK_SIZE * s.z) < pos->z &&
		p.z + (BLOCK_SIZE * s.z) > pos->z;
}

bool StageManager::IsBlock(XMFLOAT3* pos, int status)
{
	//連想for文
	for (const auto& block : tBlock_){
		//ポジションとサイズを変数に入れておく
		XMFLOAT3 p = block->GetPosition();
		XMFLOAT3 s = block->GetScale();

		if (isPsoitionHits(p,s,pos)){
			//方向によって処理を分ける
			switch (status){
			case Right:
				pos->x = (p.x + (PLAYER_MODEL_SIZE.x / 2) + (BLOCK_SIZE * s.x));break;
			case Left:
				pos->x = (p.x - (PLAYER_MODEL_SIZE.x / 2) - (BLOCK_SIZE * s.x));break;
			case Under:
				pos->y = (p.y + (PLAYER_MODEL_SIZE.y / 2) + (BLOCK_SIZE * s.y));break;
			case Top:
				pos->y = (p.y - (PLAYER_MODEL_SIZE.y / 2) - (BLOCK_SIZE * s.y));
				block->SetIsHit(true);break;
			}
			return true;
	}}
	return false;
}
