#pragma once
#include "Vector3.h"
#include "../FPSCamera.h"
#include "../TopDownCamera.h"
#include "../GroundEntity.h"
#include "../GenericEntity.h"
#include "SingletonTemplate.h"
#include "../Minimap.h"
#include "../Application.h"
#include "../BuildingManager.h"
#include "../WeaponInfo/WeaponInfo.h"

class Keyboard;
class Mouse;
class SceneText;
class CWeaponInfo;
class Weapon;

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

	// Set the boundary for the player info
	void SetBoundary(Vector3 max, Vector3 min);
	// Set the terrain for the player info
	void SetTerrain(GroundEntity* m_pTerrain);

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
	bool LeftClick(float dt);
	bool MapResize();
	void CollisionResponse(EntityBase* thatEntity);

	int GetMaterial(void) const { return material; }
	void SetMaterial(int material) { this->material = material; }
	float GetPlayerHealth(void) const { return playerHealth; }
	void SetPlayerHealth(float playerHealth) { this->playerHealth = playerHealth; }
	BuildingEntity::BUILDING_TYPE GetCurrentBuilding(void) const { return currentBuilding; }
	void SetCurrentBuilding(BuildingEntity::BUILDING_TYPE currentBuilding) { this->currentBuilding = currentBuilding; }
	bool GetIsBuilding(void) const { return isBuilding; }
	void SetIsBuilding();
	bool GetIsEquipment(void) const { return isEquipment; }
	void SetIsEquipment();
	EquipmentEntity::EQUIPMENT_TYPE GetCurrentEquipment(void) const { return currentEquipment; }
	void SetCurrentEquipment(EquipmentEntity::EQUIPMENT_TYPE currentEquipment) { this->currentEquipment = currentEquipment; }

	// Reload current weapon
	bool ReloadWeapon(void);
	// Change current weapon
	bool ChangeWeapon(void);
	// Change current weapon(Keyboard)
	bool ChangeWeaponK(void);
	// Get Current Weapon
	int GetWeapon(void) const;
	// Discharge Primary Weapon
	bool DischargePrimaryWeapon(const float deltaTime, Vector3 position, Vector3 target);
	// Discharge Secondary Weapon
	bool DischargeSecondaryWeapon(const float deltaTime);

	//GetProj
	std::list<Projectile*>GetProj();

	// Scrollable weapon switching
	CWeaponInfo** weaponManager;
	std::vector<Weapon*> weaponList;
	int m_iCurrentWeapon;
	const int m_iNumOfWeapon = 2;
	CWeaponInfo* primaryWeapon;
	CWeaponInfo* secondaryWeapon;

private:
	Vector3 defaultPosition;
	Vector3 direction;
	Vector3 target;
	Vector3 maxBoundary, minBoundary;
	GroundEntity* m_pTerrain;
	float size;

	double m_dSpeed;
	double m_dAcceleration;
	double m_dElapsedTime;
	double speedMultiplier;

	CameraBase* attachedCamera;
	Keyboard* keyboard;
	Mouse* mouse;

	int material;
	float playerHealth;
	BuildingEntity::BUILDING_TYPE currentBuilding;
	bool isBuilding, isEquipment;
	EquipmentEntity::EQUIPMENT_TYPE currentEquipment;
};
