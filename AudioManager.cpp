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
	void Initialize()
	{
		hDonSound_ = Audio::Load("Sounds/don.wav",3);
		assert(hDonSound_ >= 0);

		hTitleMusic_ = Audio::Load("Sounds/TitleBGM.wav");
		assert(hTitleMusic_ >= 0);

		hConfirmSound_ = Audio::Load("Sounds/Confirm.wav");
		assert(hConfirmSound_ >= 0);

		hPlayMusic_ = Audio::Load("Sounds/PlayScene.wav",true);
		assert(hPlayMusic_ >= 0);

		hDeadSound_ = Audio::Load("Sounds/Dead.wav");
		assert(hDeadSound_ >= 0);

		hJumpSound_ = Audio::Load("Sounds/Jump.wav");
		assert(hJumpSound_ >= 0);


	}

	void PlayDonSound()
	{
		Audio::Play(hDonSound_);
	}

	void StopDonSound()
	{
		Audio::Stop(hDonSound_);
	}

	void Play_TitleMusic()
	{
		Audio::Play(hTitleMusic_);
	}

	void PlayConfirmSound()
	{
		Audio::Play(hConfirmSound_);
	}

	void Play_PlayMusic()
	{
		Audio::Play(hPlayMusic_);
	}

	void Play_DeadSound()
	{
		Audio::Play(hDeadSound_);
	}

	void Play_JumpSound()
	{
		Audio::Play(hJumpSound_);
	}

	void Release()
	{
		Audio::Release();
	}


}