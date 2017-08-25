#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H

#include "Vector3.h"

class EntityBase
{
public:
	EntityBase();
	virtual ~EntityBase();

	enum OBJECT_TYPE {
		NONE = 0,
		PLAYER,
		BUILDING,
		EQUIPMENT,
		ENEMY,
		PROJECTILE
	}objectType;

	virtual void Update(double _dt);
	virtual void Render();
	virtual void RenderUI();

	inline void SetPosition(const Vector3& _value){ position = _value; };
	inline Vector3 GetPosition(){ return position; };

	inline void SetScale(const Vector3& _value){ scale = _value; };
	inline Vector3 GetScale(){ return scale; };

	bool IsDone();
	void SetIsDone(const bool _value);

	bool IsFixed();
	void SetIsFixed(const bool _value);

	// Check if this entity has a collider class parent
	virtual bool HasCollider(void) const;
	// Set the flag to indicate if this entity has a collider class parent
	virtual void SetCollider(const bool _value);

	// Check if this entity has a physic class parent
	virtual bool HasPhysic(void) const;
	// Set the flag to indicate if this entity has a physic class parent
	virtual void SetPhysic(const bool _value);

protected:

	Vector3 position;
	Vector3 scale;

	bool isDone;
	bool isFixed;
	bool m_bCollider;
	bool m_bPhysic;
};

#endif // ENTITY_BASE_H