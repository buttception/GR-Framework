#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../GenericEntity.h"
#include "../EnemyEntity.h"
#include "MeshList.h"
#include "../PlayerInfo/PlayerInfo.h"

class Player;
class CWeaponInfo;

class Projectile : public GenericEntity {
public:

	Player *player;

	Projectile(std::string _meshName);
	~Projectile();

	enum SOURCE_TYPE {
		ENEMY_SOURCE,
		PLAYER_SOURCE
	}source;

	CWeaponInfo* weap;

	bool pent;

	// Activate the projectile. true == active, false == inactive
	void SetStatus(const bool m_bStatus);
	// get status of the projectile. true == active, false == inactive
	bool GetStatus(void) const;
	// Set the position and direction of the projectile
	void Set(Vector3 theNewPosition,
		Vector3 theNewDirection,
		const float m_fLifetime,
		const float m_fSpeed,
		const int damage);
	void SetDirection(Vector3 theNewDirection);
	// Get the direction of the projectile
	Vector3 GetDirection(void);
	// Set the lifetime of the projectile
	void SetLifetime(const float m_fLifetime);
	// Get the lifetime of the projectile
	float GetLifetime(void) const;
	// Set the speed of the projectile
	void SetSpeed(const float m_fSpeed);
	// Get the speed of the projectile
	float GetSpeed(void) const;

	//set damage
	void SetDamage(const int m_damage);
	//get damage
	float GetDamage(void) const;
	// Update the status of this projectile
	virtual void Update(double dt = 0.0333f);
	// Render this projectile
	virtual void Render(void);

	void CollisionResponse(GenericEntity* thatEntity);
protected:
	// Boolean flag to indicate if this projectile is active. If not active, then do not compute/update
	bool m_bStatus;
	// Remaining lifetime in seconds
	float m_fLifetime;
	// Speed of this projectile in unit / sec
	float m_fSpeed;
	// damage of the projectile
	int damage;
	// The direction of the projectile
	Vector3 theDirection;
	// Size of the projectile
	float size;
};

namespace Create {
	Projectile* Bullet(std::string _meshName);
}

#endif