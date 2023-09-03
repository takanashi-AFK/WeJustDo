#include "AudioManager.h"
#include "Engine/Audio.h"	
#include<cassert>
namespace AudioManager
{
	//•Ï”éŒ¾
	int hDonSound_ ;
	int hTitleMusic_;//75db
	int hPlayMusic_;//75db
	int hConfirmSound_;
	int hDeadSound_;
	int hJumpSound_;
	int hJetSound_;

	void PlayDonSound()
	{
		hDonSound_ = Audio::Load("Sounds/don.wav",false);
		assert(hDonSound_ >= 0);
		Audio::Play(hDonSound_);
	}

	void StopDonSound()
	{
		Audio::Stop(hDonSound_);
	}

	void Play_TitleMusic()
	{
		hTitleMusic_ = Audio::Load("Sounds/TitleBGM.wav");
		assert(hTitleMusic_ >= 0);
		Audio::Play(hTitleMusic_);
	}

	void PlayConfirmSound()
	{
		hConfirmSound_ = Audio::Load("Sounds/Confirm.wav");
		assert(hConfirmSound_ >= 0);
		Audio::Play(hConfirmSound_);
	}

	void Play_PlayMusic()
	{
		hPlayMusic_ = Audio::Load("Sounds/PlayScene.wav", true);
		assert(hPlayMusic_ >= 0);
		Audio::Play(hPlayMusic_);
	}

	void Play_DeadSound()
	{
		hDeadSound_ = Audio::Load("Sounds/Dead.wav");
		assert(hDeadSound_ >= 0);
		Audio::Play(hDeadSound_);
	}

	void Play_JumpSound()
	{
		hJumpSound_ = Audio::Load("Sounds/Jump.wav");
		assert(hJumpSound_ >= 0);
		Audio::Play(hJumpSound_);
	}

	void Play_JetSound()
	{
		hJetSound_ = Audio::Load("Sounds/JettPack.wav");
		assert(hJetSound_ >= 0);
		Audio::Play(hJetSound_);
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