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
	this->controllerfunc[CONTROLLER_SWITCHWEAPON] = &Controller::SwitchWeapon;
	this->controllerfunc[CONTROLLER_RESET] = &Controller::Reset;
	this->controllerfunc[CONTROLLER_LEFTCLICK] = &Controller::LeftClick;
	this->controllerfunc[CONTROLLER_AIM] = &Controller::Aim;
	this->controllerfunc[CONTROLLER_MAPRESIZE] = &Controller::MapResize;
	this->controllerfunc[CONTROLLER_ISBUILDING] = &Controller::isBuilding;
	this->controllerfunc[CONTROLLER_ISEQUIPMENT] = &Controller::isEquipment;
	this->controllerfunc[CONTROLLER_ISWEAPON] = &Controller::isWeapon;

	return false;
}

// Read from the controller
int Controller::Read(const float deltaTime)
{
	if (_CONTROLLER_DEBUG)
		cout << "Controller::Read()" << endl;
	return 0;
}

bool Controller::MoveFront(double dt)
{
	thePlayerInfo->MoveFrontBack((float)dt, true);
	return false;
}

bool Controller::MoveBack(double dt)
{
	thePlayerInfo->MoveFrontBack((float)dt, false);
	return false;
}

bool Controller::MoveLeft(double dt)
{
	thePlayerInfo->MoveLeftRight((float)dt, false);
	return false;
}

bool Controller::MoveRight(double dt)
{
	thePlayerInfo->MoveLeftRight((float)dt, true);
	return false;
}

bool Controller::Interact(double dt)
{
	std::cout << "Interact" << std::endl;
	return false;
}

bool Controller::Reload(double dt)
{
	thePlayerInfo->ReloadWeapon();
	return false;
}

bool Controller::SwitchWeapon(double dt)
{
	std::cout << "Switch Weapon" << std::endl;
	thePlayerInfo->SwitchWeapon();
	return false;
}

bool Controller::Reset(double dt)
{
	thePlayerInfo->Reset();
	return false;
}

bool Controller::LeftClick(double dt)
{
	thePlayerInfo->LeftClick((float)dt);
	return false;
}

bool Controller::Aim(double dt)
{
	std::cout << "Aim" << std::endl;
	return false;
}

bool Controller::MapResize(double dt)
{
	thePlayerInfo->MapResize();
	return false;
}

bool Controller::isBuilding(double dt)
{
	thePlayerInfo->SetIsBuilding();
	return false;
}

bool Controller::isEquipment(double dt)
{
	thePlayerInfo->SetIsEquipment();
	return false;
}

bool Controller::isWeapon(double dt)
{
	thePlayerInfo->SetIsWeapon();
	return false;
}
