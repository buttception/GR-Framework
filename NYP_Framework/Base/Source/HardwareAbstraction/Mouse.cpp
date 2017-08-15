#include "Mouse.h"
#include <iostream>
#include <sstream>
using namespace std;

#include "MouseController.h"
#include "../PlayerInfo/PlayerInfo.h"

const bool _CONTROLLER_MOUSE_DEBUG = false;

Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}

// Create this controller
bool Mouse::Create(Player* thePlayerInfo)
{
	Controller::Create(thePlayerInfo);
	if (_CONTROLLER_MOUSE_DEBUG)
		cout << "Mouse::Create()" << endl;

	KeyList[CONTROLLER_FIRE] = MouseController::LMB;
	KeyList[CONTROLLER_AIM] = MouseController::RMB;

	return false;
}


// Read from the controller
int Mouse::Read(const float deltaTime)
{
	Controller::Read(deltaTime);
	if (_CONTROLLER_MOUSE_DEBUG)
		cout << "Mouse::Read()" << endl;

	//double mousePosX, mousePosY;
	//MouseController::GetInstance()->GetMousePosition(mousePosX, mousePosY);
	//cout << "mouseX: " << mousePosX << endl;
	//cout << "mouseY: " << mousePosY << endl;

	for (int i = CONTROLLER_FIRE;i < NUM_CONRTOLLER;++i)
	{
		if (MouseController::GetInstance()->IsButtonDown(KeyList[i]))
		{
			(this->*(controllerfunc[i]))(deltaTime);
		}
	}
	return 0;
}
