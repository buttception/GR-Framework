#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H

#include <vector>

#include "SingletonTemplate.h"
#include "ParticleEntity.h"

class ParticleManager : public Singleton<ParticleManager> {
	friend Singleton<ParticleManager>;
public:
	ParticleEntity* FetchParticle();

	void Update(double dt);
	void Render();

	bool AddParticle(ParticleEntity::PARTICLE_TYPE _p, Vector3 _pos);

private:
	ParticleManager();
	virtual ~ParticleManager();

	std::vector<ParticleEntity*>particleList;

	int maxParticles;
};

#endif