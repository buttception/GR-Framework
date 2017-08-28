#include "ParticleEntity.h"

ParticleEntity::ParticleEntity()
{
	active = false;
	modelMesh = nullptr;
}

ParticleEntity::~ParticleEntity()
{
}

void ParticleEntity::Update(double dt)
{
}

void ParticleEntity::Render()
{
}

void ParticleEntity::SetMesh(Mesh * _mesh)
{
	_mesh = modelMesh;
}
