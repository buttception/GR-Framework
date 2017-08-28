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
	
	void GenerateBlood(Vector3 _pos);

	ParticleEntity* AddParticle(ParticleEntity::PARTICLE_TYPE _p, Mesh* _mesh, Vector3 _pos);

private:
	ParticleManager();
	virtual ~ParticleManager();

	std::vector<ParticleEntity*>particleList;

	int maxParticles;
};

#endif