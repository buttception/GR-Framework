#include "Mouse.h"
#include <iostream>
#include <sstream>
using namespace std;

#include "MouseController.h"
#include "../PlayerInfo/PlayerInfo.h"
#include "../SceneText.h"

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

	KeyList[CONTROLLER_LEFTCLICK] = MouseController::LMB;
	KeyList[CONTROLLER_AIM] = MouseController::RMB;

	return false;
}


// Read from the controller
int Mouse::Read(const float deltaTime)
{
	Controller::Read(deltaTime);
	if (_CONTROLLER_MOUSE_DEBUG)
		cout << "Mouse::Read()" << endl;

	for (int i = CONTROLLER_LEFTCLICK;i < NUM_CONRTOLLER;++i)
	{
		if (MouseController::GetInstance()->IsButtonReleased(KeyList[i]))
		{
			(this->*(controllerfunc[i]))(deltaTime);
		}
	}

	//for switching buildings / equipment / weapons
	if (MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) != 0.0)
	{
		if (SceneText::isDay)
		{
			if (Player::GetInstance()->GetIsBuilding())
			{
				switch ((int)MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET))
				{
				case 1:
					Player::GetInstance()->SetCurrentBuilding(BuildingEntity::BUILDING_WALL);
					break;
				case 2:
					Player::GetInstance()->SetCurrentBuilding(BuildingEntity::BUILDING_DOOR);
					break;
				case 3:
					Player::GetInstance()->SetCurrentBuilding(BuildingEntity::BUILDING_COVER);
					break;
				case 4:
					Player::GetInstance()->SetCurrentBuilding(BuildingEntity::BUILDING_FLOOR);
					break;
				}
			}
			else if (Player::GetInstance()->GetIsEquipment())
			{
				switch ((int)MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET))
				{
				case 1:
					Player::GetInstance()->SetCurrentEquipment(EquipmentEntity::EQUIPMENT_TURRET);
					break;
				case 2:
					Player::GetInstance()->SetCurrentEquipment(EquipmentEntity::EQUIPMENT_HEALING_STATION);
					break;
				case 3:
					Player::GetInstance()->SetCurrentEquipment(EquipmentEntity::EQUIPMENT_FLOOR_SPIKE);
					break;
				case 4:
					Player::GetInstance()->SetCurrentEquipment(EquipmentEntity::EQUIPMENT_SHIELD);
					break;
				}
			}
			else if (Player::GetInstance()->GetIsWeapon())
			{
				if ((int)MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) != Player::GetInstance()->GetCurrentWeapon())
				{
					if ((MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) >= 0.0) &&
						((int)MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) < Player::GetInstance()->GetNumberOfWeapon()))
						Player::GetInstance()->SetCurrentWeapon((int)MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET));
				}
			}
		}
	}
	return 0;
}
