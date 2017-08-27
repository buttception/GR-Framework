#include "Turret.h"

#include "EntityManager.h"

EquipmentTurret * Create::Turret(Vector3 pos)
{
	EquipmentTurret* t = new EquipmentTurret(pos);
	EntityManager::GetInstance()->AddEntity(t);
	return t;
}

EquipmentTurret::EquipmentTurret(Vector3 pos)
	:EquipmentEntity("Turret")
{
	SetPosition(pos);
}

EquipmentTurret::~EquipmentTurret()
{
}

void EquipmentTurret::Update(double dt)
{

}

bool EquipmentTurret::rayCast(Vector3 dir, Vector3 origin, GenericEntity* hitbox)
{
	//let the 4 points of the aabb be a, b, c, d
	Vector3 a, b, c, d;
	a.Set(hitbox->GetMaxAABB().x, 0, hitbox->GetMaxAABB().z);
	b.Set(hitbox->GetMinAABB().x, 0, hitbox->GetMinAABB().z);
	c.Set(hitbox->GetMaxAABB().x, 0, hitbox->GetMinAABB().z);
	d.Set(hitbox->GetMinAABB().x, 0, hitbox->GetMaxAABB().z);

	//if a ray intersect one of the 2 segments diagonal in a aabb, collision is true
	Vector3 segment1 = b - a;
	Vector3 segment2 = d - c;
	bool hit = false;

	float product = dir.x * segment1.z - dir.z * segment1.x;

	float u = ((a.x - origin.x) * dir.z - (a.z - origin.z) * dir.x) / product;
	float t = ((a.x - origin.x) * segment1.z - (a.z - origin.z) * segment1.x) / product;

	if (t > 0 && t < 1 && u > 0 && u < 1) {
		hit = true;
	}

	product = dir.x * segment2.z - dir.z * segment2.z;

	u = ((c.x - origin.x) * dir.z - (c.z - origin.z) * dir.x) / product;
	t = ((c.x - origin.x) * segment2.z - (c.z - origin.z) * segment2.x) / product;

	if (t > 0 && t < 1 && u > 0 && u < 1) {
		hit = true;
	}

	if (hit) {
		return true;
	}
}
