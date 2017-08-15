#pragma once

#include "Controller.h"

#include <fstream>

class Mouse :
	public Controller
{
private:
	unsigned int KeyList[NUM_CONRTOLLER];
public:
	Mouse();
	virtual ~Mouse();
	// Create this controller
	virtual bool Create(Player* thePlayerInfo = NULL);
	// Read from the controller
	//virtual bool Load(std::string _filePath);
	virtual int Read(const float deltaTime);
};

