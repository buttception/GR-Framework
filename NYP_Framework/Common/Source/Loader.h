#ifndef _LOADER_H
#define _LOADER_H

#include "SingletonTemplate.h"

#include <fstream>
#include <string.h>
#include <vector>

#include "../../Base/Source/WeaponInfo/Weapon.h"

class Loader : public Singleton<Loader>
{
	friend Singleton <Loader>;
private:
	std::fstream* m_file;
	std::vector<std::string> m_file_data;
	Loader();
	~Loader();

	bool OpenFile(std::string _name);
	bool CloseFile();

	std::string file_WeaponID;
	std::string file_WeaponName;
	std::string file_WeaponDamage;
	std::string file_WeaponImpact;
	std::string file_WeaponHeld;
	std::string file_WeaponAmmo;
	std::string file_WeaponTotalAmmo;
	std::string file_WeaponReloadSpeed;
	std::string file_WeaponProjectileSpeed;
	std::string file_WeaponFireRate;
	std::string file_WeaponRange;
	std::string file_WeaponPenetration;

public:
	/*
	Calling this function puts each line of a text file into a string vector.
	Use GetData() to retreive the data.
	*/
	bool LoadData(std::string _name);

	/*
	Calling this function puts selected data into the text file.
	Use SetData() to set write data.
	*/
	bool WriteData(std::string _name);

	std::vector<std::string> GetData();
	void SetData(std::vector<std::string> _data);
	bool ReadFileWeapon(std::string File, std::vector<Weapon*> &List);
};

#endif