#include "PlayerStateManager.h"

//�R���X�g���N�^
PlayerStateManager::PlayerStateManager()
{
	ASSIGN(pStanding_, new StandingState);
	ASSIGN(pRunning_, new RunningState);
	ASSIGN(pJumping_, new JumpingState);
	ASSIGN(pMovie_, new MovieState);
	ASSIGN(pDead_, new DeadState);
	ASSIGN(pJet_, new JetState);
	//������Ԃŏ�����
	ASSIGN(playerState_,pStanding_);
}
PlayerStateManager::~PlayerStateManager()
{
	delete pStanding_;
	delete pRunning_;
	delete pJumping_;
	delete pMovie_;
	delete pDead_;
	delete pJet_;
}
//�X�V
void PlayerStateManager::Update(Player* _p)
{
	//���݂̏�Ԃ̍X�V
	playerState_->Update(_p);
}

//���͏���
void PlayerStateManager::HandleInput(Player* _p)
{

}

//�J�n
void PlayerStateManager::Enter(Player* _p)
{
	//���݂̏�Ԃ̊J�n����
	playerState_->Enter(_p);
}

//��ԑJ��
void PlayerStateManager::ChangeState(PlayerState* change, Player* _p, bool flag)
{
	prevState_ = playerState_;
	if (prevState_ != change)
	{
		//��Ԃ�ύX����
		playerState_ = change;
		if (flag) {
			//�J�n�������s��
			playerState_->Enter(_p);
		}
	}

}

void PlayerStateManager::ChangeState(PlayerState* change, Player* player)
{
	ChangeState(change, player,true);
}
