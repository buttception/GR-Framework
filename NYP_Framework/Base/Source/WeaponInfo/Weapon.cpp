#include "Weapon.h"
#include "../Sound_Engine.h"
#include "Loader.h"

Weapon::Weapon()
{
	std::string weaponName = "";
	int damage = 0;
	double impact = 0;
	int ammo = 0;
	int totalAmmo = 0;
	double reloadSpeed = 0;
	double projectileSpeed = 0;
	double fireRate = 0;
	double range = 0;
	bool penetration = false;
}

Weapon::~Weapon()
{
}

void Weapon::Init(int setWeaponID, std::string setWeaponName, int setDamage, double setImpact,int setCurrentRounds, int setAmmo, int setTotalAmmo, double setReloadSpeed, double setProjectileSpeed, double setFireRate, double setRange, bool setPenetration)
{
	CWeaponInfo::Init();
	weaponID = setWeaponID;
	weaponName = setWeaponName;
	damage = setDamage;
	impact = setImpact;
	totalRounds = setCurrentRounds;
	magRounds = setAmmo;
	maxMagRounds = setTotalAmmo;
	reloadSpeed = setReloadSpeed;
	projectileSpeed = setProjectileSpeed;
	fireRate = setFireRate;
	range = setRange;
	penetration = setPenetration;
	timeBetweenShots = 0.5f;
	
}

void Weapon::LoadWeaponData()
{
	Loader::GetInstance()->LoadData("weapon.csv");
}