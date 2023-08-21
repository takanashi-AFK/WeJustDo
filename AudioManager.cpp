#include "AudioManager.h"
#include "Engine/Audio.h"	
#include<cassert>
namespace AudioManager
{
	//•Ï”éŒ¾
	int hDonSound_ ;

	void Initialize()
	{
		hDonSound_ = Audio::Load("Sounds/don.wav",3);
		assert(hDonSound_ >= 0);
	}

	void PlayDonSound()
	{
		Audio::Play(hDonSound_);
	}

	void StopDonSound()
	{
		Audio::Stop(hDonSound_);
	}


}