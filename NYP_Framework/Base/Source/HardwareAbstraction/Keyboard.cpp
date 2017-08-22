#include "Keyboard.h"
#include <iostream>
#include <sstream>
using namespace std;

#include "KeyboardController.h"
#include "../PlayerInfo/PlayerInfo.h"

const bool _CONTROLLER_KEYBOARD_DEBUG = false;

Keyboard::Keyboard()
{
}


Keyboard::~Keyboard()
{
}

// Create this controller
bool Keyboard::Create(Player* thePlayerInfo)
{
	Controller::Create(thePlayerInfo);
	KeyList[CONTROLLER_MOVEFRONT] = 'W';
	KeyList[CONTROLLER_MOVEBACK] = 'S';
	KeyList[CONTROLLER_MOVELEFT] = 'A';
	KeyList[CONTROLLER_MOVERIGHT] = 'D';
	KeyList[CONTROLLER_RUN] = VK_LSHIFT;
	KeyList[CONTROLLER_INTERACT] = 'E';
	KeyList[CONTROLLER_RELOAD] = 'R';
	KeyList[CONTROLLER_SWITCHWEAPON] = 'Q';
	KeyList[CONTROLLER_RESET] = 'P';
	KeyList[CONTROLLER_MAPRESIZE] = 'M';
	KeyList[CONTROLLER_ISBUILDING] = '1';
	KeyList[CONTROLLER_ISEQUIPMENT] = '2';
	KeyList[CONTROLLER_ISWEAPON] = '3';

	return false;
}


bool Keyboard::Load(std::string _filePath)
{
    return false;
}

// Read from the controller
int Keyboard::Read(const float deltaTime)
{
	Controller::Read(deltaTime);
	if (_CONTROLLER_KEYBOARD_DEBUG)
	return 0;

	for (int i = 0;i < CONTROLLER_LEFTCLICK;++i)
	{
		if (i >= 0 && i <= 4)
		{
			if (Player::GetInstance()->fatigue == Player::FATIGUE::NORMAL)
			{
				if (KeyboardController::GetInstance()->IsKeyDown(KeyList[CONTROLLER_RUN]))
				{
					if (KeyboardController::GetInstance()->IsKeyDown(KeyList[CONTROLLER_MOVEFRONT]))
						thePlayerInfo->MoveFrontBack(deltaTime, true, 2.0f);
					if (KeyboardController::GetInstance()->IsKeyDown(KeyList[CONTROLLER_MOVEBACK]))
						thePlayerInfo->MoveFrontBack(deltaTime, false, 2.0f);
					if (KeyboardController::GetInstance()->IsKeyDown(KeyList[CONTROLLER_MOVELEFT]))
						thePlayerInfo->MoveLeftRight(deltaTime, false, 2.0f);
					if (KeyboardController::GetInstance()->IsKeyDown(KeyList[CONTROLLER_MOVERIGHT]))
						thePlayerInfo->MoveLeftRight(deltaTime, true, 2.0f);
					break;
				}
				else
				{
					if (KeyboardController::GetInstance()->IsKeyDown(KeyList[i]))
						(this->*(controllerfunc[i]))(deltaTime);
				}
			}
			else if (Player::GetInstance()->fatigue == Player::FATIGUE::ENERGETIC)
			{
				if (KeyboardController::GetInstance()->IsKeyDown(KeyList[CONTROLLER_RUN]))
				{
					if (KeyboardController::GetInstance()->IsKeyDown(KeyList[CONTROLLER_MOVEFRONT]))
						thePlayerInfo->MoveFrontBack(deltaTime, true, 4.0f);
					if (KeyboardController::GetInstance()->IsKeyDown(KeyList[CONTROLLER_MOVEBACK]))
						thePlayerInfo->MoveFrontBack(deltaTime, false, 4.0f);
					if (KeyboardController::GetInstance()->IsKeyDown(KeyList[CONTROLLER_MOVELEFT]))
						thePlayerInfo->MoveLeftRight(deltaTime, false, 4.0f);
					if (KeyboardController::GetInstance()->IsKeyDown(KeyList[CONTROLLER_MOVERIGHT]))
						thePlayerInfo->MoveLeftRight(deltaTime, true, 4.0f);
					break;
				}
				else
				{
					if (KeyboardController::GetInstance()->IsKeyDown(KeyList[CONTROLLER_MOVEFRONT]))
						thePlayerInfo->MoveFrontBack(deltaTime, true, 2.0f);
					if (KeyboardController::GetInstance()->IsKeyDown(KeyList[CONTROLLER_MOVEBACK]))
						thePlayerInfo->MoveFrontBack(deltaTime, false, 2.0f);
					if (KeyboardController::GetInstance()->IsKeyDown(KeyList[CONTROLLER_MOVELEFT]))
						thePlayerInfo->MoveLeftRight(deltaTime, false, 2.0f);
					if (KeyboardController::GetInstance()->IsKeyDown(KeyList[CONTROLLER_MOVERIGHT]))
						thePlayerInfo->MoveLeftRight(deltaTime, true, 2.0f);
					break;
				}
			}
			else if (Player::GetInstance()->fatigue == Player::FATIGUE::TIRED)
			{
				if (KeyboardController::GetInstance()->IsKeyDown(KeyList[CONTROLLER_MOVEFRONT]))
					thePlayerInfo->MoveFrontBack(deltaTime, true, 0.5f);
				if (KeyboardController::GetInstance()->IsKeyDown(KeyList[CONTROLLER_MOVEBACK]))
					thePlayerInfo->MoveFrontBack(deltaTime, false, 0.5f);
				if (KeyboardController::GetInstance()->IsKeyDown(KeyList[CONTROLLER_MOVELEFT]))
					thePlayerInfo->MoveLeftRight(deltaTime, false, 0.5f);
				if (KeyboardController::GetInstance()->IsKeyDown(KeyList[CONTROLLER_MOVERIGHT]))
					thePlayerInfo->MoveLeftRight(deltaTime, true, 0.5f);
				break;
			}
		}
		else if (KeyboardController::GetInstance()->IsKeyReleased(KeyList[i]))
		{
			(this->*(controllerfunc[i]))(deltaTime);
		}
	}
	return 0;
}
