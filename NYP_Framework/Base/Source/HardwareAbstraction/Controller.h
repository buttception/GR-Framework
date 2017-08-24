#pragma once

#include "../PlayerInfo/PlayerInfo.h"

class Controller
{
protected:
	Player* thePlayerInfo;
public:

	//Add more based on how many functions you have
    enum CONTROLLER_STATES
    {
        CONTROLLER_MOVEFRONT = 0,
        CONTROLLER_MOVEBACK,
        CONTROLLER_MOVELEFT,
        CONTROLLER_MOVERIGHT,
		CONTROLLER_RUN,

		CONTROLLER_INTERACT,
		
		CONTROLLER_RELOAD,
		CONTROLLER_SWITCHWEAPON,
		CONTROLLER_RESET,
		CONTROLLER_MAPRESIZE,
		CONTROLLER_ISBUILDING,
		CONTROLLER_ISEQUIPMENT,
		CONTROLLER_ISWEAPON,

		CONTROLLER_LEFTCLICK,
		CONTROLLER_RIGHTCLICK,

        NUM_CONRTOLLER,
    };

	Controller();
	virtual ~Controller();

	// Create this controller
	virtual bool Create(Player* thePlayerInfo = NULL);
	// Read from the controller
	virtual int Read(const float deltaTime);

	bool(Controller::*controllerfunc[NUM_CONRTOLLER])(double dt);

	virtual bool MoveFront(double dt);
	virtual bool MoveBack(double dt);
	virtual bool MoveLeft(double dt);
	virtual bool MoveRight(double dt);
	virtual bool Interact(double dt);
	virtual bool Reload(double dt);
	virtual bool SwitchWeapon(double dt);
	virtual bool Reset(double dt);
	virtual bool LeftClick(double dt);
	virtual bool RightClick(double dt);
	virtual bool MapResize(double dt);
	virtual bool isBuilding(double dt);
	virtual bool isEquipment(double dt);
	virtual bool isWeapon(double dt);

};

