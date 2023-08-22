#pragma once
#include "Engine/SolidObject.h"

#include <vector>
#include "Block.h"
//�萔
namespace
{
	static float BLOCK_SIZE = 1.0f;				    //�u���b�N�̃T�C�Y
	static XMFLOAT3 PLAYER_MODEL_SIZE = { 1.0f,1.0f,1.0f };  //Player��X�̃��f���T�C�Y
}

namespace StageManager	//�p���͂��Ȃ�
{
	/// <summary>
	/// �X�e�[�W���쐬
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	void CreateStage(GameObject* parent);

	
	/// <summary>
	/// �u���b�N�Ƃ̓����蔻��Ɏg��
	/// </summary>
	enum BlockHitTest{
		Right = 0,     //�E
		Left,          //��
		Under,         //��
		Top,           //��
	};

	bool IsBlock(XMFLOAT3* pos,int s);
};

