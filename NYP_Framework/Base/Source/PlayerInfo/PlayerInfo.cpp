#include "PlayerInfo.h"
#include <iostream>

#include "MouseController.h"
#include "KeyboardController.h"
#include "Mtx44.h"
#include "../HardwareAbstraction/Keyboard.h"
#include "../HardwareAbstraction/Mouse.h"
#include "../Sound_Engine.h"
#include "../SceneText.h"
#include "../Minimap.h"
#include "../WeaponInfo/Weapon.h"
#include "../Projectile/Projectile.h"
#include "Loader.h"
#include "MeshList.h"
#include "../EnemyEntity.h"
#include "LoadTGA.cpp"

bool SceneText::isDay = true;
bool CMinimap::isResizing = false;
// Allocating and initializing Player's static data member.  
// The pointer is allocated but not the object's constructor.

Player::Player(void)
	: m_dSpeed(40.0)
	, GenericEntity(MeshList::GetInstance()->GetMesh("wall"))
	, m_dAcceleration(10.0)
	, m_dElapsedTime(0.0)
	, attachedCamera(NULL)
	, m_pTerrain(NULL)
	, speedMultiplier(1.0)
	, size(5)
	, maxPlayerHealth(100)
	, playerHealth(100)
	, material(3000)
	, currentBuilding(BuildingEntity::BUILDING_WALL)
	, isBuilding(true)
	, isEquipment(false)
	, isWeapon(false)
	, currentEquipment(EquipmentEntity::EQUIPMENT_TURRET)
	, primaryWeapon(NULL)
	, secondaryWeapon(NULL)
	, weaponManager(NULL)
	, m_iCurrentWeapon(1)
	, fatigue(FATIGUE::NORMAL)
	, slept(false)
{
	//EntityManager::GetInstance()->AddEntity(this);
	//objectType = GenericEntity::PLAYER;
}

Player::~Player(void)
{
	m_pTerrain = NULL;
}

// Initialise this class instance
void Player::Init(void)
{
	// Set the current values
	position.Set(MAX_CELLS * CELL_SIZE / 2, 0, (MAX_CELLS * CELL_SIZE / 2) + 5.f);

	// Set the default values
	defaultPosition = position;

	// Set Boundary
	maxBoundary.Set(MAX_CELLS*CELL_SIZE,1,MAX_CELLS*CELL_SIZE);
	minBoundary.Set(0, -1, 0);

	SetAABB(Vector3(position.x + size / 2, position.y + size / 2, position.z + size / 2), Vector3(position.x - size / 2, position.y - size / 2, position.z - size / 2));
	SetRadius(size * 5);
	SetCollider(true);

	this->keyboard = new Keyboard();
	keyboard->Create(this);
	this->mouse = new Mouse();
	mouse->Create(this);

	//Playerinfo is my bitch
	CSoundEngine::GetInstance()->Init();
	CSoundEngine::GetInstance()->Addthefuckingsound("HELLO", "Image//Hello.mp3");
	CSoundEngine::GetInstance()->Addthefuckingsound("Build", "Image//wood1.ogg");
	CSoundEngine::GetInstance()->Addthefuckingsound("PewPew", "Image//9mm.mp3");
	CSoundEngine::GetInstance()->Addthefuckingsound("Floor", "Image//stone6.ogg");
	CSoundEngine::GetInstance()->Addthefuckingsound("CUCK" , "Image//AA.mp3");
	//CSoundEngine::GetInstance()->Addthefuckingsound("ISIS", "Image//ISIS.mp3");
	CSoundEngine::GetInstance()->Addthefuckingsound("Remove", "Image//out.ogg");
	CSoundEngine::GetInstance()->Addthefuckingsound("NULL", "Image//click.ogg");
	CSoundEngine::GetInstance()->Addthefuckingsound("PEW", "Image//pew.mp3");
	CSoundEngine::GetInstance()->Addthefuckingsound("MELEE", "Image//melee.mp3");
	CSoundEngine::GetInstance()->Addthefuckingsound("NIGHT", "Image//night ost.mp3");
	CSoundEngine::GetInstance()->Addthefuckingsound("DAY", "Image//day.mp3");

	// Set the pistol as the primary weapon
	Loader::GetInstance()->ReadFileWeapon("weapon.csv", weaponList);
	primaryWeapon = weaponList[0];
	primaryWeapon->Init();

	weaponManager = new CWeaponInfo*[m_iNumOfWeapon];
	weaponManager[1] = weaponList[0];
	weaponManager[1]->Init();

	weaponManager[2] = weaponList[1];
	weaponManager[2]->Init();

	SetScale(Vector3(size, size, size));

	
	core = BuildingManager::GetInstance()->AddBuilding((int)(Player::GetInstance()->GetPosition().x / CELL_SIZE),
		(int)(Player::GetInstance()->GetPosition().z / CELL_SIZE),
		BuildingTile::TOP, BuildingEntity::BUILDING_CORE);
}

// Set the boundary for the player info
void Player::SetBoundary(Vector3 max, Vector3 min)
{
	maxBoundary = max;
	minBoundary = min;
}

// Set the terrain for the player info
void Player::SetTerrain(GroundEntity* m_pTerrain)
{






}

// Reset this player instance to default
void Player::Reset(void)
{
	// Set the current values to default values
	position = defaultPosition;
}

/********************************************************************************
 Hero Update
 ********************************************************************************/
void Player::Update(double dt)
{
	keyboard->Read((float)dt);
	mouse->Read((float)dt);

	if (attachedCamera == NULL)
		std::cout << "No camera attached! Please make sure to attach one" << std::endl;
	//direction = attachedCamera->GetCameraTarget() - attachedCamera->GetCameraPos();
	//direction.Normalize();

	Vector3 up(0, 1, 0);

	//if it is a FPS Camera
	//if (dynamic_cast<FPSCamera*>(attachedCamera))
	//{
	//	Vector3 rightUV;
	//	if (KeyboardController::GetInstance()->IsKeyDown('W'))
	//	{
	//		position += direction.Normalized() * (float)m_dSpeed * (float)speedMultiplier * (float)dt;
	//	}
	//	else if (KeyboardController::GetInstance()->IsKeyDown('S'))
	//	{
	//		position -= direction.Normalized() * (float)m_dSpeed * (float)speedMultiplier * (float)dt;
	//	}
	//	if (KeyboardController::GetInstance()->IsKeyDown('A'))
	//	{
	//		rightUV = (direction.Normalized()).Cross(up);
	//		rightUV.y = 0;
	//		rightUV.Normalize();
	//		position -= rightUV * (float)m_dSpeed * (float)speedMultiplier * (float)dt;
	//	}
	//	else if (KeyboardController::GetInstance()->IsKeyDown('D'))
	//	{
	//		rightUV = (direction.Normalized()).Cross(up);
	//		rightUV.y = 0;
	//		rightUV.Normalize();
	//		position += rightUV * (float)m_dSpeed * (float)speedMultiplier * (float)dt;
	//	}
	//	// Constrain the position
	//	Constrain();
	//}

	// If a camera is attached to this playerInfo class, then update it
	if (attachedCamera)
	{
		/*if (dynamic_cast<FPSCamera*>(attachedCamera)) {
			Vector3 cameraView = attachedCamera->GetCameraTarget() - attachedCamera->GetCameraPos();
			attachedCamera->SetCameraPos(position);
			attachedCamera->SetCameraTarget(position + cameraView.Normalized());
			dynamic_cast<FPSCamera*>(attachedCamera)->Update(dt);
		}*/
		if (dynamic_cast<TopDownCamera*>(attachedCamera)) {
			attachedCamera->SetCameraPos(position + dynamic_cast<TopDownCamera*>(attachedCamera)->GetHeight());
			attachedCamera->SetCameraTarget(position);
			dynamic_cast<TopDownCamera*>(attachedCamera)->Update(dt);
		}
	}

	SetAABB(Vector3(position.x + size / 2, position.y + size / 2, position.z + size / 2), Vector3(position.x - size / 2, position.y - size / 2, position.z - size / 2));

	//testing cout
	//std::cout << (int)(position.x / CELL_SIZE) << ", " << (int)(position.z / CELL_SIZE) << std::endl;

	if (KeyboardController::GetInstance()->IsKeyPressed(VK_F5) && !SceneText::isDay)
		playerHealth = Math::Max(0.f, playerHealth - 10.f);

	CMinimap::GetInstance()->SetPosition(( position.x - 250.f )/ MAX_CELLS * CELL_SIZE * 0.5f * 0.01f,
		 (250.f - position.z) / MAX_CELLS * CELL_SIZE * 0.5f * 0.01f);

	//weapon update
	if (primaryWeapon)
		primaryWeapon->Update(dt);
	if (secondaryWeapon)
		secondaryWeapon->Update(dt);
	if (weaponManager[m_iCurrentWeapon])
		weaponManager[m_iCurrentWeapon]->Update(dt);

	//healTimer update
	//equipment->healTimer += (float)dt;
	//if(equipment->healTimer >= equipment->healCoolDown)
		//MeshList::GetInstance()->GetMesh("Healing Station")->textureID[0] = LoadTGA("Image//Equipment//Heal_Active.tga");

	switch (fatigue)
	{
	case TIRED:
		maxPlayerHealth = 150.f;
		break;
	case NORMAL:
		maxPlayerHealth = 100.f;
		if (playerHealth >= 100.f)
			playerHealth = 100.f;
		break;
	case ENERGETIC:
		maxPlayerHealth = 50.f;
		if (playerHealth >= 50.f)
			playerHealth = 50.f;
		break;
	}

	if (playerHealth <= 0)
	{
		playerHealth = maxPlayerHealth;
		material = Math::Max(0, material - 100);
		position.Set(MAX_CELLS * CELL_SIZE / 2 + 10, 0, (MAX_CELLS * CELL_SIZE / 2) + 10);
	}
}

// Reload current weapon
bool Player::ReloadWeapon(void)
{
	if (weaponManager[m_iCurrentWeapon])
	{
		weaponManager[m_iCurrentWeapon]->Reload();
		return true;
	}
	return false;
}

bool Player::SwitchWeapon(void)
{
	if (m_iCurrentWeapon == 1)
	{
		m_iCurrentWeapon = 2;
	}
	else
	{
		m_iCurrentWeapon = 1;
	}

	return true;
}

// Discharge Primary Weapon
bool Player::DischargePrimaryWeapon(const float deltaTime, Vector3 position, Vector3 target)
{
	if (weaponManager[m_iCurrentWeapon])
	{
		std::cout << weaponManager[m_iCurrentWeapon]->GetName() << std::endl;
		weaponManager[m_iCurrentWeapon]->PrintSelf();
		//std::cout << "fire" << std::endl;
		weaponManager[m_iCurrentWeapon]->Discharge(position, target, this);

		return true;
	}

	return false;
}

// Discharge Secondary Weapon
bool Player::DischargeSecondaryWeapon(const float deltaTime)
{
	if (secondaryWeapon)
	{
		secondaryWeapon->Discharge(position, target, this);
		return true;
	}

	return false;
}

void Player::changeSecondaryWeapon(int weaponID)
{
	switch (weaponID)
	{
	case 1:
		std::cout << weaponList.size() << std::endl;
	/*	weaponManager[2] = weaponList[1];
		weaponManager[2]->Init();*/
		break;
	case 2:
		weaponManager[2] = weaponList[2];
		weaponManager[2]->Init();
		break;
	case 3:
		weaponManager[2] = weaponList[3];
		weaponManager[2]->Init();
		break;
	case 4:
		weaponManager[2] = weaponList[4];
		weaponManager[2]->Init();
		break;
	case 5:
		weaponManager[2] = weaponList[5];
		weaponManager[2]->Init();
		break;
	case 6:
		weaponManager[2] = weaponList[6];
		weaponManager[2]->Init();
		break;
	case 7:
		weaponManager[2] = weaponList[7];
		weaponManager[2]->Init();
		break;
	case 8:
		weaponManager[2] = weaponList[8];
		weaponManager[2]->Init();
		break;
	}
}

std::list<Projectile*> Player::GetProj()
{
	return weaponManager[m_iCurrentWeapon]->GetProj();
}


// Constrain the position within the borders
void Player::Constrain(void)
{
	//constrain the player to stay within the map/play area 
	//min for z  and x is 0, max is 500
	if (position.x > maxBoundary.x )
	{
		position.x = maxBoundary.x;
		playerHealth = Math::Max(0, playerHealth - 1);
		Render_Another_qUAD = true;
	}
	if (position.z > maxBoundary.z)
	{
		position.z = maxBoundary.z;
		playerHealth = Math::Max(0, playerHealth - 1);
		Render_Another_qUAD = true;
	}
	if (position.x < minBoundary.x)
	{
		position.x = minBoundary.x;
		playerHealth = Math::Max(0, playerHealth - 1);
		Render_Another_qUAD = true;
	}
	if (position.z < minBoundary.z)
	{
		position.z = minBoundary.z;
		playerHealth = Math::Max(0, playerHealth - 1);
		Render_Another_qUAD = true;
	}
	else
	{
		Render_Another_qUAD = false;
	}
}

CameraBase * Player::getCamera()
{
	return attachedCamera;
}

void Player::AttachCamera(CameraBase* _cameraPtr)
{
	attachedCamera = _cameraPtr;
	/*if (dynamic_cast<FPSCamera*>(attachedCamera)) {
		Vector3 target = position + Vector3(1, 0, 0);
		Vector3 view = target - position;
		Vector3 up = Vector3(0, 0, 1).Cross(view).Normalized();
		dynamic_cast<FPSCamera*>(attachedCamera)->Init(position, target, up);
		std::cout << "FPS Camera loaded" << std::endl;
	}*/
	if (dynamic_cast<TopDownCamera*>(attachedCamera)){
		Vector3 target = position;
		Vector3 up(0, 0, -1);
		dynamic_cast<TopDownCamera*>(attachedCamera)->Init(Vector3(position.x, position.y + 20, position.z), target, up, 100);
		std::cout << "Top down camera Loaded" << std::endl;
	}
}

void Player::DetachCamera()
{
	attachedCamera = nullptr;
}

bool Player::MoveFrontBack(const float deltaTime, const bool direction, const float speedMultiplier)
{
	if (dynamic_cast<TopDownCamera*>(attachedCamera)) {
		defaultPosition.z = position.z;
		if (direction)
		{
			position -= Vector3(0, 0, 1) * (float)m_dSpeed * (float)speedMultiplier * (float)deltaTime;
			Constrain();
			return true;
		}
		else
		{
			position += Vector3(0, 0, 1) * (float)m_dSpeed * (float)speedMultiplier * (float)deltaTime;
			Constrain();
			return true;
		}
	}
	return false;
}

bool Player::MoveLeftRight(const float deltaTime, const bool direction, const float speedMultiplier)
{
	if (dynamic_cast<TopDownCamera*>(attachedCamera)) {
		defaultPosition.x = position.x;
		if (!direction)
		{
			position -= Vector3(1, 0, 0) * (float)m_dSpeed * (float)speedMultiplier * (float)deltaTime;
			Constrain();
			return true;
		}
		else
		{
			position += Vector3(1, 0, 0) * (float)m_dSpeed * (float)speedMultiplier * (float)deltaTime;
			Constrain();
			return true;
		}
	}
	return false;
}

bool Player::LeftClick(float dt)
{
	//convert mouse pos on window onto world
	double mouseX, mouseY;
	MouseController::GetInstance()->GetMousePosition(mouseX, mouseY);
	MouseController::GetInstance()->UpdateMousePosition(mouseX, mouseY);//Application::GetInstance().GetWindowHeight() - 
	MouseController::GetInstance()->GetMousePosition(mouseX, mouseY);

	float windowWidth = (float)Application::GetInstance().GetWindowWidth();
	float windowHeight = (float)Application::GetInstance().GetWindowHeight();
	Vector3 Up_Direction = Vector3(windowWidth / 2.f, windowHeight, 0.f) - Vector3(windowWidth / 2.f, windowHeight / 2.f, 0.f);
	Vector3 playerMouse_Direction = Vector3((float)mouseX, (float)mouseY, 0.f) - Vector3(windowWidth / 2.f, windowHeight / 2.f, 0.f);
	try
	{
		playerMouse_Direction.Normalize();
		float angle = Math::RadianToDegree(acosf(playerMouse_Direction.Dot(Up_Direction) / (playerMouse_Direction.Length() * Up_Direction.Length())));
		if (playerMouse_Direction.x < 0)
			angle = -angle;

		//Add buildings according to angles formed with pre-detemined vectors based on mouse and player positions
		if (SceneText::isDay)
		{
			if (isBuilding)
			{
				int x = (int)(position.x / CELL_SIZE);
				int z = (int)(position.z / CELL_SIZE);
				Vector3 ghostPos, ghostScale;
				// Up
				if (angle >= -53.f && angle <= 53.f)
				{
					ghostPos.Set(x * CELL_SIZE + CELL_SIZE / 2, 1, z * CELL_SIZE);
					ghostScale.Set(CELL_SIZE, 10, 2);
					if (position.x + scale.x / 2.f >= ghostPos.x - ghostScale.x / 2.f &&
						position.x - scale.x / 2.f <= ghostPos.x + ghostScale.x / 2.f &&
						position.z + scale.z / 2.f >= ghostPos.z - ghostScale.z / 2.f &&
						position.z - scale.z / 2.f <= ghostPos.z + ghostScale.z / 2.f)
						return false;

					BuildingManager::GetInstance()->AddBuilding(x, z, BuildingTile::TOP, currentBuilding);
				}
				// Left
				else if (angle >= -127.f && angle <= -53.f)
				{
					ghostPos.Set(x * CELL_SIZE, 1, z * CELL_SIZE + CELL_SIZE / 2);
					ghostScale.Set(2, 10, CELL_SIZE);
					if (position.x + scale.x / 2.f >= ghostPos.x - ghostScale.x / 2.f &&
						position.x - scale.x / 2.f <= ghostPos.x + ghostScale.x / 2.f &&
						position.z + scale.z / 2.f >= ghostPos.z - ghostScale.z / 2.f &&
						position.z - scale.z / 2.f <= ghostPos.z + ghostScale.z / 2.f)
						return false;

					BuildingManager::GetInstance()->AddBuilding(x, z, BuildingTile::LEFT, currentBuilding);
				}
				// Right
				else if (angle >= 53.f && angle <= 127.f)
				{
					ghostPos.Set(x * CELL_SIZE + CELL_SIZE, 1, z * CELL_SIZE + CELL_SIZE / 2);
					ghostScale.Set(2, 10, CELL_SIZE);
					if (position.x + scale.x / 2.f >= ghostPos.x - ghostScale.x / 2.f &&
						position.x - scale.x / 2.f <= ghostPos.x + ghostScale.x / 2.f &&
						position.z + scale.z / 2.f >= ghostPos.z - ghostScale.z / 2.f &&
						position.z - scale.z / 2.f <= ghostPos.z + ghostScale.z / 2.f)
						return false;

					BuildingManager::GetInstance()->AddBuilding(x, z, BuildingTile::RIGHT, currentBuilding);
				}
				// Down
				else if ((angle >= -180.f && angle <= -127.f) || (angle >= 127.f && angle <= 180.f))
				{
					ghostPos.Set(x * CELL_SIZE + CELL_SIZE / 2, 1, z * CELL_SIZE + CELL_SIZE);
					ghostScale.Set(CELL_SIZE, 10, 2);
					if (position.x + scale.x / 2.f >= ghostPos.x - ghostScale.x / 2.f &&
						position.x - scale.x / 2.f <= ghostPos.x + ghostScale.x / 2.f &&
						position.z + scale.z / 2.f >= ghostPos.z - ghostScale.z / 2.f &&
						position.z - scale.z / 2.f <= ghostPos.z + ghostScale.z / 2.f)
						return false;

					BuildingManager::GetInstance()->AddBuilding(x, z, BuildingTile::BOTTOM, currentBuilding);
				}
			}
			else if (isEquipment)
				BuildingManager::GetInstance()->AddEquipment((int)(Player::GetInstance()->GetPosition().x / CELL_SIZE), (int)(Player::GetInstance()->GetPosition().z / CELL_SIZE), currentEquipment);
			else if (currentBuilding == BuildingEntity::BUILDING_FLOOR)
				BuildingManager::GetInstance()->AddBuilding((int)(Player::GetInstance()->GetPosition().x / CELL_SIZE), (int)(Player::GetInstance()->GetPosition().z / CELL_SIZE), BuildingTile::LEFT, BuildingEntity::BUILDING_FLOOR);
			return true;
		}
		else
		{
			DischargePrimaryWeapon(dt, position, playerMouse_Direction);
			
		}

		
	}
	catch (DivideByZero)
	{
		std::cout << "Cannot move mouse to center, divide by zero(Normalize for placing buildings)" << std::endl;
	}
	return false;
}

bool Player::RightClick()
{
	//convert mouse pos on window onto world
	double mouseX, mouseY;
	MouseController::GetInstance()->GetMousePosition(mouseX, mouseY);
	MouseController::GetInstance()->UpdateMousePosition(mouseX, Application::GetInstance().GetWindowHeight() - mouseY);
	MouseController::GetInstance()->GetMousePosition(mouseX, mouseY);

	float windowWidth = (float)Application::GetInstance().GetWindowWidth();
	float windowHeight = (float)Application::GetInstance().GetWindowHeight();
	//for the direction player is pointing at
	Vector3 Up_Direction = Vector3(windowWidth / 2.f, windowHeight, 0.f) - Vector3(windowWidth / 2.f, windowHeight / 2.f, 0.f);
	Vector3 playerMouse_Direction = Vector3((float)mouseX, (float)mouseY, 0.f) - Vector3(windowWidth / 2.f, windowHeight / 2.f, 0.f);

	try
	{
		playerMouse_Direction.Normalize();
		float angle = Math::RadianToDegree(acosf(playerMouse_Direction.Dot(Up_Direction) / (playerMouse_Direction.Length() * Up_Direction.Length())));
		if (playerMouse_Direction.x < 0)
			angle = -angle;

		int x = (int)(position.x / CELL_SIZE);
		int z = (int)(position.z / CELL_SIZE);
		if (SceneText::isDay)
		{
			// Up
			if ((angle >= -180.f && angle <= -127.f) || (angle <= 180.f && angle >= 127.f))
			{
				BuildingTile* tile = &BuildingManager::GetInstance()->GetBuildingArray()[x][z];
				if (tile->topWall != nullptr)
				{
					tile->topWall->SetIsDone(true);
					tile->topWall = nullptr;
					CSoundEngine::GetInstance()->playthesound("Remove", 0.2f);
					std::cout << "Remove Sound Played" << std::endl;
				}
			}
			// Left
			else if (angle >= -127.f && angle <= -53.f)
			{
				BuildingTile* tile = &BuildingManager::GetInstance()->GetBuildingArray()[x][z];
				if (tile->leftWall != nullptr)
				{
					tile->leftWall->SetIsDone(true);
					tile->leftWall = nullptr;
					CSoundEngine::GetInstance()->playthesound("Remove", 0.2f);
					std::cout << "Remove Sound Played" << std::endl;
				}
			}
			// Right
			else if (angle >= 53.f && angle <= 127.f)
			{
				if (x + 1 != MAX_CELLS)
				{
					BuildingTile* tile = &BuildingManager::GetInstance()->GetBuildingArray()[x + 1][z];
					if (tile->leftWall != nullptr)
					{
						tile->leftWall->SetIsDone(true);
						tile->leftWall = nullptr;
						CSoundEngine::GetInstance()->playthesound("Remove", 0.2f);
						std::cout << "Remove Sound Played" << std::endl;
					}
				}
				else
				{
					BuildingTile* tile = &BuildingManager::GetInstance()->GetBuildingArray()[x][z];
					if (tile->rightWall != nullptr)
					{
						tile->rightWall->SetIsDone(true);
						tile->rightWall = nullptr;
						CSoundEngine::GetInstance()->playthesound("Remove", 0.2f);
						std::cout << "Remove Sound Played" << std::endl;
					}
				}
			}
			// Down
			else if (angle >= -53.f && angle <= 53.f)
			{
				if (z >= 0)
				{
					BuildingTile* tile = &BuildingManager::GetInstance()->GetBuildingArray()[x][z + 1];
					if (tile->topWall != nullptr)
					{
						tile->topWall->SetIsDone(true);
						tile->topWall = nullptr;
						CSoundEngine::GetInstance()->playthesound("Remove", 0.2f);
						std::cout << "Remove Sound Played" << std::endl;
					}
				}
				else
				{
					BuildingTile* tile = &BuildingManager::GetInstance()->GetBuildingArray()[x][z];
					if (tile->bottomWall != nullptr)
					{
						tile->bottomWall->SetIsDone(true);
						tile->bottomWall = nullptr;
						CSoundEngine::GetInstance()->playthesound("Remove", 0.2f);
						std::cout << "Remove Sound Played" << std::endl;
					}
				}
			}
			// Floor
			if (isBuilding && currentBuilding == BuildingEntity::BUILDING_FLOOR)
			{
				BuildingTile* tile = &BuildingManager::GetInstance()->GetBuildingArray()[x][z];
				if (tile->floor != nullptr)
				{
					tile->floor->SetIsDone(true);
					tile->floor = nullptr;
					CSoundEngine::GetInstance()->playthesound("Remove", 0.2f);
					std::cout << "Remove Sound Played" << std::endl;
				}
			}
			else if (isEquipment)
			{
				BuildingTile* tile = &BuildingManager::GetInstance()->GetBuildingArray()[x][z];
				if (tile->equipment != nullptr)
				{
					tile->equipment->SetIsDone(true);
					tile->equipment = nullptr;
					CSoundEngine::GetInstance()->playthesound("Remove", 0.2f);
					std::cout << "Remove Sound Played" << std::endl;
				}
			}
		}
		else
		{
			CSoundEngine::GetInstance()->playsinglesound("NULL", 0.2f);
			std::cout << "Null Sound Played" << std::endl;

		}
		
			

		
	}
	catch (DivideByZero)
	{
		std::cout << "Cannot move mouse to center, divide by zero(Normalize to find angle)" << std::endl;
	}
	return false;
}

bool Player::MapResize()
{
	if (CMinimap::isResizing)
		CMinimap::isResizing = false;
	else
		CMinimap::isResizing = true;
	return false;
}

void Player::CollisionResponse(GenericEntity *thatEntity)
{
	switch (thatEntity->objectType)
	{
	case BUILDING:
		// if collide with building, move player to previous position
		position = defaultPosition;
		break;
	case EQUIPMENT: {
		//down cast to equipment entity
		EquipmentEntity* equipment = dynamic_cast<EquipmentEntity*>(thatEntity);
		switch (equipment->type)
		{
		case EquipmentEntity::EQUIPMENT_HEALING_STATION:
			if (equipment->healTimer >= equipment->healCoolDown &&
				!SceneText::isDay)
			{
				playerHealth = Math::Min(maxPlayerHealth, playerHealth + 20);
				equipment->healTimer = 0.f;
			}
			break;
		}
	}
	   break;
	case ENEMY: {
		//make the enemy attack the player
		EnemyEntity* e = dynamic_cast<EnemyEntity*>(thatEntity);
		e->AddState(StateMachine::ATTACK_STATE);
		e->SetTarget(Player::GetInstance());
	}
	   break;
	case PROJECTILE:{
		Projectile* p = dynamic_cast<Projectile*>(thatEntity);
		if (p) {
			switch (p->source) {
			case Projectile::ENEMY_SOURCE:
				playerHealth -= p->GetDamage();
				p->SetIsDone(true);
				break;
			default:
				return;
			}
		}
	}
	   break;
	default:
		return;
	}
	return;
}

void Player::SetIsBuilding()
{
	isBuilding = true;

	isEquipment = false;
	isWeapon = false;
}

void Player::SetIsEquipment()
{
	isBuilding = false;

	isEquipment = true;
	
	isWeapon = false;
}

void Player::SetIsWeapon()
{
	isBuilding = false;
	isEquipment = false;
	
	isWeapon = true;
}
