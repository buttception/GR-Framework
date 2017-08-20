#pragma once
#include "../Projectile/Projectile.h"
#include "../PlayerInfo/PlayerInfo.h"
#include "Vector3.h"
#include <list>
#include <string>


class Player;

class CWeaponInfo
{
public:
	CWeaponInfo();
	virtual ~CWeaponInfo();

	//ID for weapon
	int weaponID;
	//name for weapon
	std::string weaponName;
	//Damage for weapon
	int damage;
	//Knock back distance
	double impact;
	//Amount of the ammo the weapon hold
	int magRounds;
	//max ammo for the weapon
	int maxMagRounds;
	//Reload Speed for weapon
	double reloadSpeed;
	//Projectile Speed for weapon
	double projectileSpeed;
	//Time between each shots for weapon
	double fireRate;
	//Maximum effective of the projectile before disappearing
	double range;
	//Pentration for projectile
	int penetration;
	// The current total number of rounds currently carried by this player
	int totalRounds;
	// The max total number of rounds currently carried by this player
	int maxTotalRounds;

protected:
	// The time between shots in milliseconds
	double timeBetweenShots;
	// The elapsed time (between shots) in milliseconds
	double elapsedTime;
	// Boolean flag to indicate if weapon can fire now
	bool bFire;

	//bullets
	std::list<Projectile*>bullets;

	//bullet fired
	bool bFired;

public:
	//set the damage for the bullet
	virtual void WeaponDamage(const int damage);
	// Set the number of ammunition in the magazine for this player
	virtual void SetMagRound(const int magRounds);
	// Set the maximum number of ammunition in the magazine for this weapon
	virtual void SetMaxMagRound(const int magRounds);
	// The current total number of rounds currently carried by this player
	virtual void SetTotalRound(const int totalRounds);
	// The max total number of rounds currently carried by this player
	virtual void SetMaxTotalRound(const int maxTotalRounds);

	// Get the weapon ID
	virtual int GetWeaponID(void) const;
	// Get the weapon damage for this weapon
	virtual int GetWeaponDamage(void) const;
	// Get the number of ammunition in the magazine for this player
	virtual int GetMagRound(void) const;
	// Get the maximum number of ammunition in the magazine for this weapon
	virtual int GetMaxMagRound(void) const;
	// Get the current total number of rounds currently carried by this player
	virtual int GetTotalRound(void) const;
	// Get the max total number of rounds currently carried by this player
	virtual int GetMaxTotalRound(void) const;
	// Get the weapon Name
	virtual std::string GetName(void) const;

	// Set the time between shots
	virtual void SetTimeBetweenShots(const double timeBetweenShots);
	// Set the firing rate in rounds per min
	virtual void SetFiringRate(const int firingRate);
	// Set the firing flag
	virtual void SetCanFire(const bool bFire);

	// Get the time between shots
	virtual double GetTimeBetweenShots(void) const;
	// Get the firing rate
	virtual int GetFiringRate(void) const;
	// Get the firing flag
	virtual bool GetCanFire(void) const;

	// Initialise this instance to default values
	virtual void Init(void);
	// Update the elapsed time
	void Update(const double dt);
	// Discharge this weapon
	void Discharge(Vector3 position, Vector3 target, Player* _source = NULL);
	// Reload this weapon
	void Reload(void);
	// Add rounds
	void AddRounds(const int newRounds);

	// Print Self
	void PrintSelf(void);

	//GetProjectiles
	std::list<Projectile*> GetProj();

};
