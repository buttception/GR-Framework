#include "ParticleManager.h"

ParticleEntity * ParticleManager::FetchParticle()
{
	for (auto it : particleList) {
		if (!it->GetActive())
			return it;
	}
	return nullptr;
}

void ParticleManager::Update(double dt)
{
}

void ParticleManager::Render()
{
}

bool ParticleManager::AddParticle(ParticleEntity::PARTICLE_TYPE _p, Vector3 _pos)
{
	ParticleEntity* p;
	if (p = FetchParticle()) {

	}
	else
		return false;
}

ParticleManager::ParticleManager()
	:maxParticles(100)
{
	for (int i = 0; i < maxParticles; ++i) {
		particleList.push_back(new ParticleEntity());
	}
}

ParticleManager::~ParticleManager()
{
}
