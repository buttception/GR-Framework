#include "Controller.h"
#include <iostream>
using namespace std;

const bool _CONTROLLER_DEBUG = false;

Controller::Controller()
	: thePlayerInfo(NULL)
{
}


Controller::~Controller()
{
	// We just set thePlayerInfo to NULL without deleting. SceneText will delete this.
	if (thePlayerInfo)
		thePlayerInfo = NULL;
}


// Create this controller
bool Controller::Create(Player* thePlayerInfo)
{
	if (_CONTROLLER_DEBUG)
		cout << "Controller::Create()" << endl;
	this->thePlayerInfo = thePlayerInfo;
	this->controllerfunc[CONTROLLER_MOVEFRONT] = &Controller::MoveFront;
	this->controllerfunc[CONTROLLER_MOVEBACK] = &Controller::MoveBack;
	this->controllerfunc[CONTROLLER_MOVELEFT] = &Controller::MoveLeft;
	this->controllerfunc[CONTROLLER_MOVERIGHT] = &Controller::MoveRight;
	this->controllerfunc[CONTROLLER_INTERACT] = &Controller::Interact;
	this->controllerfunc[CONTROLLER_RELOAD] = &Controller::Reload;
	this->controllerfunc[CONTROLLER_RESET] = &Controller::Reset;
	this->controllerfunc[CONTROLLER_FIRE] = &Controller::Fire;
	this->controllerfunc[CONTROLLER_AIM] = &Controller::Aim;

	return false;
}

// Read from the controller
int Controller::Read(const const float deltaTime)
{
	if (_CONTROLLER_DEBUG)
		cout << "Controller::Read()" << endl;
	return 0;
}

bool Controller::MoveFront(double dt)
{
	thePlayerInfo->MoveFrontBack(dt, true);
	return false;
}

bool Controller::MoveBack(double dt)
{
	thePlayerInfo->MoveFrontBack(dt, false);
	return false;
}

bool Controller::MoveLeft(double dt)
{
	thePlayerInfo->MoveLeftRight(dt, false);
	return false;
}

bool Controller::MoveRight(double dt)
{
	thePlayerInfo->MoveLeftRight(dt, true);
	return false;
}

bool Controller::Interact(double dt)
{
	std::cout << "Interact" << std::endl;
	return false;
}

bool Controller::Reload(double dt)
{
	std::cout << "Reload" << std::endl;
	return false;
}

bool Controller::Reset(double dt)
{
	thePlayerInfo->Reset();
	return false;
}

bool Controller::Fire(double dt)
{
	std::cout << "Fire" << std::endl;
	return false;
}

bool Controller::Aim(double dt)
{
	std::cout << "Aim" << std::endl;
	return false;
}
