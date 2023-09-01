#include "PlayerStateManager.h"

//�R���X�g���N�^
PlayerStateManager::PlayerStateManager()
{
	//�e��ԃC���X�^���X��p��
	ASSIGN(pStanding_,new StandingState);
	ASSIGN(pRunning_, new RunningState);
	ASSIGN(pJumping_, new JumpingState);
	ASSIGN(pMovie_,new MovieState);

	//������Ԃŏ�����
	ASSIGN(playerState_,pStanding_);
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
void PlayerStateManager::ChangeState(PlayerState* change, Player* _p)
{
	//��Ԃ�ύX����
	playerState_ = change;

	//�J�n�������s��
	playerState_->Enter(_p);
}
