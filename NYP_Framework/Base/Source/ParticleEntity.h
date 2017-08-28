#ifndef PARTICLE_ENTITY_H
#define PARTICLE_ENTITY_H

#include "Mesh.h"
#include "EntityBase.h"

class ParticleEntity : public EntityBase {
public:
	ParticleEntity();
	virtual ~ParticleEntity();

	enum PARTICLE_TYPE {
		BLOOD
	}particleType;

	void Update(double dt);
	void Render();

	void SetMesh(Mesh* _mesh);

	inline bool GetActive() { return active; }
	inline void SetActive(bool _value) { active = _value; }

private:
	Mesh* modelMesh;

	bool active;
};

#endif