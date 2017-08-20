#ifndef WEAPON_H
#define WEAPON_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "WeaponInfo.h"

//using namespace std;

class Weapon :
	public CWeaponInfo
{
private:


	struct data {

	};

	std::vector<data>weaponList;

public:
	Weapon();
	~Weapon();

	//Set data with weapon info
	void Init(int setWeaponID, std::string setWeaponName, int setDamage, double setImpact, int setCurrentRounds, int setAmmo, int setTotalAmmo, double setReloadSpeed, double setProjectileSpeed, double setFireRate, double setRange, bool setPenetration);

	//function overloading for wepaon variables
	data WeaponData;

	//load data from csv
	void LoadWeaponData();

	//init

	//print weapon data
	std::string PrintWeaponData();

	//getters
	//int getID();
	//std::string getName();
	//int getDamage();
	//double getImpact();
	//int getAmmo();
	//int getTotalAmmo();
	//double getReloadSpeed();
	//double getProjectileSpeed();
	//double getRange();
	//int getPenetration();
	//int getData(int choice);

};

#endif