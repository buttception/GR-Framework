#include "ParticleManager.h"

#include "MeshList.h"

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
	for (auto it : particleList) {
		if (it->GetActive()) {
			it->Update(dt);
		}
	}
}

void ParticleManager::Render()
{
	for (auto it : particleList) {
		if (it->GetActive()) {
			it->Render();
		}
	}
}

void ParticleManager::GenerateBlood(Vector3 _pos)
{
	for (size_t i = 0; i < 10; ++i) {
		ParticleEntity* p;
		if (p = AddParticle(ParticleEntity::BLOOD, MeshList::GetInstance()->GetMesh("sphere"), _pos)){
			float dX, dZ;
			float scale;
			dX = Math::RandFloatMinMax(-10, 10);
			dZ = Math::RandFloatMinMax(-10, 10);
			scale = Math::RandFloatMinMax(0.2, 1);
			p->SetDirection(Vector3(dX, 0, dZ).Normalized());
			p->SetVelocity(Math::RandFloatMinMax(5, 10));
			p->SetScale(Vector3(scale, scale, scale));
		}
	}
}

ParticleEntity* ParticleManager::AddParticle(ParticleEntity::PARTICLE_TYPE _p, Mesh* _mesh, Vector3 _pos)
{
	ParticleEntity* p;
	if (p = FetchParticle()) {
		p->SetPosition(_pos);
		p->particleType = _p;
		p->SetMesh(_mesh);
		p->SetActive(true);
		p->ResetTimer();
		p->SetDuration(1.f);
		return p;
	}
	else
		return nullptr;
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
