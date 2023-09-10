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
	int hFootSound_;

	void Play_DonSound()
	{
		hDonSound_ = Audio::Load("Sounds/don.wav",false);
		assert(hDonSound_ >= 0);
		Audio::Play(hDonSound_);
	}

	void Stop_DonSound()
	{
		Audio::Stop(hDonSound_);
	}

	void Play_TitleMusic()
	{
		hTitleMusic_ = Audio::Load("Sounds/TitleBGM.wav");
		Audio::ChangePitch(hTitleMusic_, 5.0f);
		Audio::SetVolume(hTitleMusic_, 0.5f);
		assert(hTitleMusic_ >= 0);
		Audio::Play(hTitleMusic_);
	}

	void Play_ConfirmSound()
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

	void Play_FootSound()
	{
		hFootSound_ = Audio::Load("Sounds/»‚Ìã‚ð‘–‚é.wav",true);
		assert(hFootSound_ >= 0);
		Audio::Play(hFootSound_);
	}

	void Stop_FootSound()
	{
		Audio::Stop(hFootSound_);
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