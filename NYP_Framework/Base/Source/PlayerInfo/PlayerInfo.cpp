#include "PlayerInfo.h"
#include <iostream>

#include "MouseController.h"
#include "KeyboardController.h"
#include "Mtx44.h"
#include "../HardwareAbstraction/Keyboard.h"
#include "../BuildingManager.h"
#include "../HardwareAbstraction/Mouse.h"
#include "../Sound_Engine.h"
#include "../SceneText.h"
#include "../Minimap.h"

bool SceneText::isDay = true;
bool CMinimap::isResizing = false;
// Allocating and initializing Player's static data member.  
// The pointer is allocated but not the object's constructor.

Player::Player(void)
	: m_dSpeed(40.0)
	, GenericEntity(NULL)
	, m_dAcceleration(10.0)
	, m_dElapsedTime(0.0)
	, attachedCamera(NULL)
	, m_pTerrain(NULL)
	, speedMultiplier(1.0)
{
}

Player::~Player(void)
{
	m_pTerrain = NULL;
}

// Initialise this class instance
void Player::Init(void)
{
	// Set the current values
	position.Set(MAX_CELLS * CELL_SIZE / 2, 0, MAX_CELLS * CELL_SIZE / 2);

	// Set the default values
	defaultPosition = position;

	// Set Boundary
	maxBoundary.Set(1,1,1);
	minBoundary.Set(-1, -1, -1);

	SetAABB(Vector3(position.x + 5, position.y + 5, position.z + 5), Vector3(position.x - 5, position.y - 5, position.z - 5));
	SetCollider(true);

	this->keyboard = new Keyboard();
	keyboard->Create(this);
	this->mouse = new Mouse();
	mouse->Create(this);


	CSoundEngine::GetInstance()->Init();
	CSoundEngine::GetInstance()->Addthefuckingsound("HELLO", "Image//Hello.mp3");
	CSoundEngine::GetInstance()->Addthefuckingsound("Build", "Image//Relax.mp3");
	
	//CSoundEngine::GetInstance()->Addthefuckingsound("HI", "Image//Hello.mp3");

	playerHealth = 100.f;
	material = 3000;
}

// Set position
void Player::SetPos(const Vector3& pos)
{
	position = pos;
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

// Get position x of the player
Vector3 Player::GetPos(void) const
{
	return position;
}

/********************************************************************************
 Hero Update
 ********************************************************************************/
void Player::Update(double dt)
{
	double mouse_diff_x, mouse_diff_y;
	MouseController::GetInstance()->GetMouseDelta(mouse_diff_x, mouse_diff_y);

	double camera_yaw = mouse_diff_x * 0.0174555555555556;		// 3.142 / 180.0
	double camera_pitch = mouse_diff_y * 0.0174555555555556;	// 3.142 / 180.0

	keyboard->Read((float)dt);
	mouse->Read((float)dt);

	if (attachedCamera == NULL)
		std::cout << "No camera attached! Please make sure to attach one" << std::endl;
	direction = attachedCamera->GetCameraTarget() - attachedCamera->GetCameraPos();
	direction.Normalize();

	Vector3 up(0, 1, 0);

	//if it is a FPS Camera
	if (dynamic_cast<FPSCamera*>(attachedCamera))
	{
		Vector3 rightUV;
		if (KeyboardController::GetInstance()->IsKeyDown('W'))
		{
			position += direction.Normalized() * (float)m_dSpeed * (float)speedMultiplier * (float)dt;
		}
		else if (KeyboardController::GetInstance()->IsKeyDown('S'))
		{
			position -= direction.Normalized() * (float)m_dSpeed * (float)speedMultiplier * (float)dt;
		}
		if (KeyboardController::GetInstance()->IsKeyDown('A'))
		{
			rightUV = (direction.Normalized()).Cross(up);
			rightUV.y = 0;
			rightUV.Normalize();
			position -= rightUV * (float)m_dSpeed * (float)speedMultiplier * (float)dt;
		}
		else if (KeyboardController::GetInstance()->IsKeyDown('D'))
		{
			rightUV = (direction.Normalized()).Cross(up);
			rightUV.y = 0;
			rightUV.Normalize();
			position += rightUV * (float)m_dSpeed * (float)speedMultiplier * (float)dt;
		}
		// Constrain the position
		Constrain();
	}

	// If a camera is attached to this playerInfo class, then update it
	if (attachedCamera)
	{
		if (dynamic_cast<FPSCamera*>(attachedCamera)) {
			Vector3 cameraView = attachedCamera->GetCameraTarget() - attachedCamera->GetCameraPos();
			attachedCamera->SetCameraPos(position);
			attachedCamera->SetCameraTarget(position + cameraView.Normalized());
			dynamic_cast<FPSCamera*>(attachedCamera)->Update(dt);
		}
		else if (dynamic_cast<TopDownCamera*>(attachedCamera)) {
			attachedCamera->SetCameraPos(position + dynamic_cast<TopDownCamera*>(attachedCamera)->GetHeight());
			attachedCamera->SetCameraTarget(position);
			dynamic_cast<TopDownCamera*>(attachedCamera)->Update(dt);
		}
	}

	SetAABB(Vector3(position.x + 5, position.y + 5, position.z + 5), Vector3(position.x - 5, position.y - 5, position.z - 5));

	//testing cout
	//std::cout << (int)(position.x / CELL_SIZE) << ", " << (int)(position.z / CELL_SIZE) << std::endl;

	if (KeyboardController::GetInstance()->IsKeyPressed(VK_F5) && !SceneText::isDay)
		playerHealth = Math::Max(0.f, playerHealth - 10.f);

	CMinimap::GetInstance()->SetPosition(position.x * CMinimap::GetInstance()->GetSize_x() / Application::GetInstance().GetWindowWidth(),
		(Application::GetInstance().GetWindowHeight() - position.z) * CMinimap::GetInstance()->GetSize_y() / Application::GetInstance().GetWindowHeight());
}

// Constrain the position within the borders
void Player::Constrain(void)
{
















}

CameraBase * Player::getCamera()
{
	return attachedCamera;
}

void Player::AttachCamera(CameraBase* _cameraPtr)
{
	attachedCamera = _cameraPtr;
	if (dynamic_cast<FPSCamera*>(attachedCamera)) {
		Vector3 target = position + Vector3(1, 0, 0);
		Vector3 view = target - position;
		Vector3 up = Vector3(0, 0, 1).Cross(view).Normalized();
		dynamic_cast<FPSCamera*>(attachedCamera)->Init(position, target, up);
		std::cout << "FPS Camera loaded" << std::endl;
	}
	else if (dynamic_cast<TopDownCamera*>(attachedCamera)){
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

bool Player::LeftClick()
{
	//convert mouse pos on window onto world
	double mouseX, mouseY;
	MouseController::GetInstance()->GetMousePosition(mouseX, mouseY);
	MouseController::GetInstance()->UpdateMousePosition(mouseX, mouseY);//Application::GetInstance().GetWindowHeight() - 
	MouseController::GetInstance()->GetMousePosition(mouseX, mouseY);

	Vector3 Up_Direction = Vector3(400.f, 600.f, 0.f) - Vector3(400.f, 300.f, 0.f);
	Vector3 Left_Direction = Vector3(0.f, 300.f, 0.f) - Vector3(400.f, 300.f, 0.f);
	Vector3 playerMouse_Direction = Vector3((float)mouseX, (float)mouseY, 0.f) - Vector3(400.f, 300.f, 0.f);
	float up_angle = Math::RadianToDegree(acosf(playerMouse_Direction.Dot(Up_Direction) / (playerMouse_Direction.Length() * Up_Direction.Length())));
	float left_angle = Math::RadianToDegree(acosf(playerMouse_Direction.Dot(Left_Direction) / (playerMouse_Direction.Length() * Left_Direction.Length())));

	//Build wall according to angles formed with pre-detemined vectors based on mouse and player positions
	if (SceneText::isDay)
	{
		// Up
		if (up_angle <= 53.f)
			BuildingManager::GetInstance()->AddWall((int)(Player::GetInstance()->GetPos().x / CELL_SIZE), (int)(Player::GetInstance()->GetPos().z / CELL_SIZE), 2);
		// Left
		else if (left_angle <= 36.f)
			BuildingManager::GetInstance()->AddWall((int)(Player::GetInstance()->GetPos().x / CELL_SIZE), (int)(Player::GetInstance()->GetPos().z / CELL_SIZE), 1);
		// Right
		else if (left_angle >= 142.f)
			BuildingManager::GetInstance()->AddWall((int)(Player::GetInstance()->GetPos().x / CELL_SIZE), (int)(Player::GetInstance()->GetPos().z / CELL_SIZE), 3);
		// Down
		else if (up_angle >= 125.f)
			BuildingManager::GetInstance()->AddWall((int)(Player::GetInstance()->GetPos().x / CELL_SIZE), (int)(Player::GetInstance()->GetPos().z / CELL_SIZE), 4);
		return true;
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

void Player::CollisionResponse(EntityBase *thatEntity)
{
	std::cout << "collided with wall" << std::endl;
}
