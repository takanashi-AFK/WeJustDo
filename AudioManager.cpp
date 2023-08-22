#include "AudioManager.h"
#include "Engine/Audio.h"	
#include<cassert>
namespace AudioManager
{
	//•Ï”éŒ¾
	int hDonSound_ ;
	int hTitleMusic_;
	int hConfirmSound_;
	void Initialize()
	{
		hDonSound_ = Audio::Load("Sounds/don.wav",3);
		assert(hDonSound_ >= 0);

		hTitleMusic_ = Audio::Load("Sounds/TitleBGM.wav");
		assert(hTitleMusic_ >= 0);

		hConfirmSound_ = Audio::Load("Sounds/Confirm.wav");
		assert(hConfirmSound_ >= 0);

	}

	void PlayDonSound()
	{
		Audio::Play(hDonSound_);
	}

	void StopDonSound()
	{
		Audio::Stop(hDonSound_);
	}

	void PlayTitleMusic()
	{
		Audio::Play(hTitleMusic_);
	}

	void PlayConfirmSound()
	{
		Audio::Play(hConfirmSound_);
	}

	void Release()
	{
		Audio::Release();
	}


}