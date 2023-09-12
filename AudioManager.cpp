#include "AudioManager.h"
#include "Engine/Audio.h"	
#include<cassert>
namespace AudioManager
{
	//�ϐ��錾
	int hDonSound_ ;
	int hTitleMusic_;//75db
	int hPlayMusic_;//75db
	int hConfirmSound_;
	int hDeadSound_;
	int hJumpSound_;
	int hJetSound_;
	int hFootSound_;
	int hWoodSound_;
	int hBombSound_;

	float masterVol;

	bool flag_ = false;

	bool isJetPlayNow() { return flag_; }

	void SetMasterVol(float vol)
	{
		masterVol = vol;
	}


	//�h���b�F�J�n
	void Play_DonSound()
	{
		hDonSound_ = Audio::Load("Sounds/don.wav",false);
		assert(hDonSound_ >= 0);
		Audio::SetVolume(hDonSound_, masterVol);
		Audio::Play(hDonSound_);
	}
	//�h���b�F��~
	void Stop_DonSound()
	{
		Audio::Stop(hDonSound_);
	}

	//�^�C�g���F�J�n
	void Play_TitleMusic()
	{
		hTitleMusic_ = Audio::Load("Sounds/TitleBGM.wav");
		assert(hTitleMusic_ >= 0);
		Audio::SetVolume(hTitleMusic_, masterVol);
		Audio::Play(hTitleMusic_);
	}

	void Play_ConfirmSound()
	{
		hConfirmSound_ = Audio::Load("Sounds/Confirm.wav");
		assert(hConfirmSound_ >= 0);
		Audio::SetVolume(hConfirmSound_, masterVol);
		Audio::Play(hConfirmSound_);
	}

	void Play_PlayMusic()
	{
		hPlayMusic_ = Audio::Load("Sounds/PlayScene.wav", true);
		assert(hPlayMusic_ >= 0);
		Audio::SetVolume(hPlayMusic_, masterVol);
		Audio::Play(hPlayMusic_);
	}

	void Play_DeadSound()
	{
		hDeadSound_ = Audio::Load("Sounds/Dead.wav");
		assert(hDeadSound_ >= 0);
		Audio::SetVolume(hDeadSound_, masterVol);
		Audio::Play(hDeadSound_);
	}

	void Play_JumpSound()
	{
		hJumpSound_ = Audio::Load("Sounds/Jump.wav");
		assert(hJumpSound_ >= 0);
		Audio::SetVolume(hJumpSound_, masterVol);
		Audio::Play(hJumpSound_);
	}

	void Play_JetSound()
	{
		flag_ = true;
		hJetSound_ = Audio::Load("Sounds/JettPack.wav");
		assert(hJetSound_ >= 0);
		Audio::SetVolume(hJetSound_, masterVol);
		Audio::Play(hJetSound_);
	}

	void Play_FootSound()
	{
		flag_ = false;
		hFootSound_ = Audio::Load("Sounds/���̏�𑖂�.wav",true);
		assert(hFootSound_ >= 0);
		Audio::SetVolume(hFootSound_, masterVol);
		Audio::SetPlaybackRate(hFootSound_,1.2f);
		Audio::Play(hFootSound_);
	}

	void Stop_FootSound()
	{
		Audio::Stop(hFootSound_);
	}

	void Play_BombSound()
	{
		hBombSound_ = Audio::Load("Sounds/����1.wav");
		assert(hBombSound_ >= 0);
		Audio::SetVolume(hBombSound_, masterVol);
		Audio::Play(hBombSound_);
	}

	void Play_WoodSound()
	{
		hWoodSound_ = Audio::Load("Sounds/db63fc113271b1a0.wav");
		assert(hWoodSound_ >= 0);
		Audio::SetVolume(hWoodSound_,masterVol);
		Audio::Play(hWoodSound_);
	}

	void Stop_JetSound()
	{
		Audio::Stop(hJetSound_);
	}

	void Release()
	{
		Audio::Release();
	}


}