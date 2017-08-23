#pragma once
#ifndef ENEMY_RUCK_H
#define ENEMY_RUCK_H

#include "EnemyEntity.h"

class EnemyRuck : public EnemyEntity {
public:
	EnemyRuck(std::string _meshName, Vector3 pos);
	~EnemyRuck();
};

namespace Create {
	EnemyRuck* Ruck(std::string _meshName, Vector3 pos);
}

#endif