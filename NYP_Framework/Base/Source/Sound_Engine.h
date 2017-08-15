#pragma once

#include "SingletonTemplate.h"
//#include "../IK/irrKlang.h" 
#include "../irrklang/IK/irrKlang.h"
using namespace irrklang;
#include <map>

class CSoundEngine : public Singleton<CSoundEngine>
{
protected:
	ISoundEngine* isthesoundEngine;

	//The library map of souunds created
	std::map<std::string, std::string> soundMap;


public:
	CSoundEngine();
	virtual ~CSoundEngine();


	bool Init(void);
	


	ISoundEngine* getthesoundEngine(void);

	//Add Irrklang/sound to this library
	void Addthefuckingsound(const std::string& _soundIndex, const std::string& _soundsource);

	//Get the sound from the map 
	std::string getthesound(const std::string&_soundIndex);

	bool removethesound(const std::string& _soundIndex);
	void playthesound(const std::string& _soundIndex,float volume);



};




























