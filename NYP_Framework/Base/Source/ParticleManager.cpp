#include "ParticleManager.h"

#include "MeshList.h"
#include "Application.h"

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
			if (it->mode == ParticleEntity::MODE_3D)
				it->Render();
		}
	}
}

void ParticleManager::RenderUI()
{
	for (auto it : particleList) {
		if (it->GetActive()) {
			if (it->mode == ParticleEntity::MODE_2D)
				it->Render();
		}
	}
}

void ParticleManager::GenerateBlood(Vector3 _pos)
{
	for (size_t i = 0; i < 10; ++i) {
		ParticleEntity* p;
		if (p = AddParticle(ParticleEntity::BLOOD, MeshList::GetInstance()->GetMesh("blood"), _pos)){
			float dX, dZ;
			float scale;
			dX = Math::RandFloatMinMax(-10, 10);
			dZ = Math::RandFloatMinMax(-10, 10);
			scale = Math::RandFloatMinMax(0.2, 0.5);
			p->SetDirection(Vector3(dX, 0, dZ).Normalized());
			p->SetVelocity(Math::RandFloatMinMax(5, 10));
			p->SetScale(Vector3(scale, scale, scale));
			p->mode = ParticleEntity::MODE_3D;
		}
	}
}

void ParticleManager::GenerateExplosion(Vector3 _pos)
{
	for (size_t i = 0; i < 20; ++i) {
		ParticleEntity* p;
		if (p = AddParticle(ParticleEntity::EXPLOSION, MeshList::GetInstance()->GetMesh("explosion"), _pos)) {
			float dX, dZ;
			float scale;
			dX = Math::RandFloatMinMax(-10, 10);
			dZ = Math::RandFloatMinMax(-10, 10);
			scale = Math::RandFloatMinMax(0.5, 1);
			p->SetDirection(Vector3(dX, 0, dZ).Normalized());
			p->SetVelocity(Math::RandFloatMinMax(5, 15));
			p->SetScale(Vector3(scale, scale, scale));
			p->mode = ParticleEntity::MODE_3D;
		}
	}
}

void ParticleManager::GenerateAmmoFeedback()
{
	ParticleEntity* p;
	if (p = AddParticle(ParticleEntity::FEEDBACK_AMMO, MeshList::GetInstance()->GetMesh("ammoFeedback"), Vector3(0,0,Math::RandFloatMinMax(1, 2)))) {
		float dX, dZ;
		float scale;
		dX = 0;
		dZ = 1;
		scale = Application::GetInstance().GetWindowWidth();
		p->SetDirection(Vector3(dX, dZ, 0).Normalized());
		p->SetVelocity(Math::RandFloatMinMax(30, 50));
		p->SetScale(Vector3(scale, scale, scale));
		p->mode = ParticleEntity::MODE_2D;
	}
}

void ParticleManager::GenerateUnlockFeedback()
{
	ParticleEntity* p;
	if (p = AddParticle(ParticleEntity::FEEDBACK_UNLOCK, MeshList::GetInstance()->GetMesh("unlockFeedback"), Vector3(0, 0, Math::RandFloatMinMax(1, 2)))) {
		float dX, dZ;
		float scale;
		dX = 0;
		dZ = 1;
		scale = Application::GetInstance().GetWindowWidth();
		p->SetDirection(Vector3(dX, dZ, 0).Normalized());
		p->SetVelocity(Math::RandFloatMinMax(30, 50));
		p->SetScale(Vector3(scale, scale, scale));
		p->mode = ParticleEntity::MODE_2D;
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
