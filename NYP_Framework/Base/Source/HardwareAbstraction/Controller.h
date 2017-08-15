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
		CONTROLLER_RESET,
		CONTROLLER_FIRE,
		CONTROLLER_AIM,

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
	virtual bool Reset(double dt);
	virtual bool Fire(double dt);
	virtual bool Aim(double dt);

};

