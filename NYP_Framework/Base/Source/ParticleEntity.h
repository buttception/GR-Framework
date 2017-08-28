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

	inline float GetDuration() { return elaspedTime; }
	inline void SetDuration(float _duration) { duration = _duration; }

	inline float GetVelocity() { return velocity; }
	inline void SetVelocity(float _vel) { velocity = _vel; }

	inline Vector3 GetDirection() { return direction; }
	inline void SetDirection(Vector3 _dir) { direction = _dir; }

	inline void ResetTimer() { elaspedTime = 0.f; }

private:
	float elaspedTime;
	float duration;
	float velocity;

	Vector3 direction;

	Mesh* modelMesh;

	bool active;
};

#endif