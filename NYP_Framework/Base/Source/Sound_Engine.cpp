#include "Sound_Engine.h"
#include <iostream>
using namespace std;

CSoundEngine::CSoundEngine()
	:isthesoundEngine(NULL)
{
	background = nullptr;
}

CSoundEngine::~CSoundEngine()
{
	soundMap.clear();

	if (isthesoundEngine)
	{
		delete isthesoundEngine;
		isthesoundEngine = NULL;
	}
}

bool CSoundEngine::Init(void)
{
	isthesoundEngine = createIrrKlangDevice();
	if (!isthesoundEngine)
	{
		return false;
	}


	return true;
}


ISoundEngine* CSoundEngine::getthesoundEngine(void)
{
	return isthesoundEngine;
}

void CSoundEngine::Addthefuckingsound(const std::string & _soundIndex, const std::string & _soundsource)
{
	if (isthesoundEngine == NULL)
	{
		if (Init() == false)
		{
			cout << "SoundEngine::Addthefuckingsound() - not initialised yet" << endl;
		}
	}


	removethesound(_soundIndex);
	soundMap[_soundIndex] = _soundsource;
	

}

std::string CSoundEngine::getthesound(const std::string & _soundIndex)
{

	if (isthesoundEngine == NULL)
	{
		if (Init() == false)
		{
			cout << "SoundEngine::Addthefuckingsound() - not initialised yet" << endl;
			return std::string();
		}
	}


	if (soundMap.count(_soundIndex) != 0)
	{
		return soundMap[_soundIndex];
	}
	return std::string();
}

bool CSoundEngine::removethesound(const std::string & _soundIndex)
{
	if (isthesoundEngine == NULL)
	{
		if (Init() == false)
		{
			cout << "SoundEngine::Addthefuckingsound() - not initialised yet" << endl;
			return NULL;
		}
	}


	std::string aSoundName = getthesound(_soundIndex);
	if (!aSoundName.empty())
	{
		soundMap.erase(_soundIndex);
		return true;
	}

	return false;
}

void CSoundEngine::playthesound(const std::string & _soundIndex, float volume)
{

	std::string aSound = getthesound(_soundIndex);
	if (!isthesoundEngine->isCurrentlyPlaying(aSound.c_str()))
	{
		isthesoundEngine->play2D(aSound.c_str(), false, false, true)->setVolume(volume);
	}
}

void CSoundEngine::playsinglesound(const std::string & _soundIndex, float volume)
{
	std::string bsound = getthesound(_soundIndex);
	isthesoundEngine->play2D(bsound.c_str(), false, false, true)->setVolume(volume);
}

void CSoundEngine::PlayBackground(const std::string & _soundIndex)
{
	std::string bsound = getthesound(_soundIndex);
	background = isthesoundEngine->play2D(bsound.c_str(), false, false, true);
	background->setVolume(0.2f);
}

void CSoundEngine::StopBackground()
{
	if (background) {
		background->setIsPaused(true);
	}
}

//void CSoundEngine::setVolume(int newvolume, float volume)
//{
//	if (newvolume < 0 || newvolume > 100)
//	{
//		volume = 50;
//	}
//
//}
//
//void CSoundEngine::increase_volume()
//{
//	volume += 10;
//
//	if (volume > 100)
//	{
//		volume = 100;
//	}
//	
//
//}
//
//void CSoundEngine::increase_volume(int increament , float volume)
//{
//	volume += increament;
//	if (volume > 100)
//	{
//		volume = 100;
//	}
//
//}
//
//void CSoundEngine::decrease_volume()
//{
//}
//
//void CSoundEngine::decrease_volume(int decrement ,float volume)
//{
//}


