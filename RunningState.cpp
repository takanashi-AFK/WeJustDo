#include "RunningState.h"

//�C���N���[�h
#include "Player.h"

//�X�V
void RunningState::Update(Player* _p)
{
	//���͏���
	HandleInput(_p);
}

//�J�n
void RunningState::Enter(Player* _p)
{
}

//���͏���
void RunningState::HandleInput(Player* _p)
{
}
