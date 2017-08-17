#pragma once
#include "Vector3.h"
#include "../FPSCamera.h"
#include "../TopDownCamera.h"
#include "../GroundEntity.h"
#include "../GenericEntity.h"
#include "SingletonTemplate.h"
#include "../Minimap.h"
#include "../Application.h"

class Keyboard;
class Mouse;

class Player : public Singleton<Player>, public GenericEntity
{
	friend Singleton<Player>;
public:
	Player();
	~Player();

	// Initialise this class instance
	void Init(void);
	// Reset this player instance to default
	void Reset(void);

	// Set position
	void SetPos(const Vector3& pos);
	// Set the boundary for the player info
	void SetBoundary(Vector3 max, Vector3 min);
	// Set the terrain for the player info
	void SetTerrain(GroundEntity* m_pTerrain);

	// Get position
	Vector3 GetPos(void) const;

	// Update
	void Update(double dt = 0.0333f);

	// Constrain the position within the borders
	void Constrain(void);

	// Handling Camera
	CameraBase* getCamera();
	void AttachCamera(CameraBase* _cameraPtr);
	void DetachCamera();

	// Movement
	bool MoveFrontBack(const float deltaTime, const bool direction, const float speedMultiplier = 1.0f);
	bool MoveLeftRight(const float deltaTime, const bool direction, const float speedMultiplier = 1.0f);

	void CollisionResponse(EntityBase* thatEntity);

private:
	Vector3 defaultPosition;
	Vector3 position, direction;
	Vector3 maxBoundary, minBoundary;
	GroundEntity* m_pTerrain;

	double m_dSpeed;
	double m_dAcceleration;
	double m_dElapsedTime;
	double speedMultiplier;

	CameraBase* attachedCamera;
	Keyboard* keyboard;
	Mouse* mouse;

};
