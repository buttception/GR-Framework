#include "PlayerInfo.h"
#include <iostream>

#include "MouseController.h"
#include "KeyboardController.h"
#include "Mtx44.h"
#include "../HardwareAbstraction/Keyboard.h"
#include "../BuildingManager.h"

// Allocating and initializing Player's static data member.  
// The pointer is allocated but not the object's constructor.

Player::Player(void)
	: m_dSpeed(40.0)
	, m_dAcceleration(10.0)
	, m_bJumpUpwards(false)
	, m_dJumpSpeed(10.0)
	, m_dJumpAcceleration(-10.0)
	, m_bFallDownwards(false)
	, m_dFallSpeed(0.0)
	, m_dFallAcceleration(-10.0)
	, m_dElapsedTime(0.0)
	, attachedCamera(NULL)
	, m_pTerrain(NULL)
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

	this->keyboard = new Keyboard();
	keyboard->Create();
}

// Returns true if the player is on ground
bool Player::isOnGround(void)
{



	return false;
}

// Returns true if the player is jumping upwards
bool Player::isJumpUpwards(void)
{



	return false;
}

// Returns true if the player is on freefall
bool Player::isFreeFall(void)
{



	return false;
}

// Set the player's status to free fall mode
void Player::SetOnFreeFall(bool isOnFreeFall)
{





}

// Set the player to jumping upwards
void Player::SetToJumpUpwards(bool isOnJumpUpwards)
{





}

// Set position
void Player::SetPos(const Vector3& pos)
{
	position = pos;
}

// Set m_dJumpAcceleration of the player
void Player::SetJumpAcceleration(const double m_dJumpAcceleration)
{
	this->m_dJumpAcceleration = m_dJumpAcceleration;
}

// Set Fall Acceleration of the player
void Player::SetFallAcceleration(const double m_dFallAcceleration)
{
	this->m_dFallAcceleration = m_dFallAcceleration;
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

// Stop the player's movement
void Player::StopVerticalMovement(void)
{
	m_bJumpUpwards = false;
	m_bFallDownwards = false;
}

// Reset this player instance to default
void Player::Reset(void)
{
	// Set the current values to default values
	position = defaultPosition;

	// Stop vertical movement too
	StopVerticalMovement();
}

// Get position x of the player
Vector3 Player::GetPos(void) const
{
	return position;
}

// Get m_dJumpAcceleration of the player
double Player::GetJumpAcceleration(void) const
{
	return m_dJumpAcceleration;
}

// Update Jump Upwards
void Player::UpdateJumpUpwards(double dt)
{
	if (m_bJumpUpwards == false)
		return;

	// Update the jump's elapsed time

	// Update position and target y values
	// Use SUVAT equation to update the change in position and target
	// s = u * t + 0.5 * a * t ^ 2


	// Use this equation to calculate final velocity, v
	// SUVAT: v = u + a * t;
	// v is m_dJumpSpeed AFTER updating using SUVAT where u is the initial speed and is equal to m_dJumpSpeed

	// Check if the jump speed is less than zero, then it should be falling
	if (m_dJumpSpeed < 0.0)
	{




	}
}

// Update FreeFall
void Player::UpdateFreeFall(double dt)
{
	if (m_bFallDownwards == false)
		return;

	// Update the jump's elapsed time

	// Update position and target y values
	// Use SUVAT equation to update the change in position and target
	// s = u * t + 0.5 * a * t ^ 2


	// Use this equation to calculate final velocity, v
	// SUVAT: v = u + a * t;
	// v is m_dJumpSpeed AFTER updating using SUVAT where u is the initial speed and is equal to m_dJumpSpeed

	// Check if the jump speed is below terrain, then it should be reset to terrain height
	if (position.y < m_pTerrain->GetTerrainHeight(position))
	{





	}
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

	keyboard->Read(dt);

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
			position += direction.Normalized() * (float)m_dSpeed * (float)dt;
		}
		else if (KeyboardController::GetInstance()->IsKeyDown('S'))
		{
			position -= direction.Normalized() * (float)m_dSpeed * (float)dt;
		}
		if (KeyboardController::GetInstance()->IsKeyDown('A'))
		{
			rightUV = (direction.Normalized()).Cross(up);
			rightUV.y = 0;
			rightUV.Normalize();
			position -= rightUV * (float)m_dSpeed * (float)dt;
		}
		else if (KeyboardController::GetInstance()->IsKeyDown('D'))
		{
			rightUV = (direction.Normalized()).Cross(up);
			rightUV.y = 0;
			rightUV.Normalize();
			position += rightUV * (float)m_dSpeed * (float)dt;
		}
		// Constrain the position
		Constrain();
	}
	else if (dynamic_cast<TopDownCamera*>(attachedCamera)) {
		if (KeyboardController::GetInstance()->IsKeyDown('D'))
		{
			position += Vector3(1, 0, 0) * (float)m_dSpeed * (float)dt;
		}
		else if (KeyboardController::GetInstance()->IsKeyDown('A'))
		{
			position -= Vector3(1, 0, 0) * (float)m_dSpeed * (float)dt;
		}
		if (KeyboardController::GetInstance()->IsKeyDown('W'))
		{
			position -= Vector3(0, 0, 1) * (float)m_dSpeed * (float)dt;
		}
		else if (KeyboardController::GetInstance()->IsKeyDown('S'))
		{
			position += Vector3(0, 0, 1) * (float)m_dSpeed * (float)dt;
		}
		//Constrain();
	}

	// Update the weapons
	if (KeyboardController::GetInstance()->IsKeyReleased('R'))
	{
	}

	// if Mouse Buttons were activated, then act on them
	if (MouseController::GetInstance()->IsButtonPressed(MouseController::LMB))
	{
		std::cout << "Left mouse down" << std::endl;
	}
	else if (MouseController::GetInstance()->IsButtonPressed(MouseController::RMB))
	{

	}

	// If the user presses R key, then reset the view to default values
	if (KeyboardController::GetInstance()->IsKeyDown('P'))
	{
		Reset();
	}
	else
	{


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
