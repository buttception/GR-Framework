#include "Turret.h"

#include "EntityManager.h"
#include "BuildingManager.h"
#include "EnemyEntity.h"
#include "Projectile\Projectile.h"
#include "Sound_Engine.h"

EquipmentTurret * Create::Turret(Vector3 pos)
{
	EquipmentTurret* t = new EquipmentTurret(pos);

	t->SetScale(Vector3(CELL_SIZE/4, CELL_SIZE/4, CELL_SIZE/4));
	t->SetDirection(Vector3(1, 0, 0));
	return t;
}

EquipmentTurret::EquipmentTurret(Vector3 pos)
	:EquipmentEntity("Turret")
	,projectileSpeed(20)
	,attackSpeed(1)
	,attackElasped(0)
	,damage(20)
	,range(40)
{
	SetPosition(pos);
	states.push(SEARCH);
}

EquipmentTurret::~EquipmentTurret()
{
}

void EquipmentTurret::Update(double dt)
{
	if (attackElasped < attackSpeed)
		attackElasped += dt;

	switch (states.top()) {
	case ATTACK:
		attack();
		break;
	case SEARCH:
		search();
		break;
	}
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
	return false;
}

void EquipmentTurret::search()
{
	static int i = 0;
	// do a search once every 60 frames to improves frames
	if (i > 120) {
		i = 0;
		for (auto it : EntityManager::GetInstance()->GetEntityList()) {
			if (it->objectType == ENEMY) {
				if ((it->GetPosition() - position).LengthSquared() > range * range)
					continue;
				EnemyEntity* e = dynamic_cast<EnemyEntity*>(it);
				if (e->GetActive()) {
					target = e;
					for (auto it : EntityManager::GetInstance()->GetEntityList()) {
						if (it->objectType == BUILDING) {
							GenericEntity* g = dynamic_cast<GenericEntity*>(it);
							if (rayCast(e->GetPosition() - position, position, g)) {
								if ((g->GetPosition() - position).LengthSquared() > (e->GetPosition() - position).LengthSquared())
									continue;
								target = nullptr;
								break;
							}
						}
					}
					if (target)
						states.push(ATTACK);
				}
				else
					continue;
			}
			else
				continue;
		}
	}
	++i;
}

void EquipmentTurret::attack()
{
	static int i = 0;
	if (i < 60) {
		i = 0;
		if (target){
			target->GetPosition();
		}
		else{
			target = nullptr;
			states.pop();
			return;
		}
		direction = (target->GetPosition() - position).Normalized();
		if (attackElasped > attackSpeed) {
			attackElasped = 0.f;

			Projectile* p = Create::Bullet("sphere");
			p->SetPosition(position);
			p->SetDamage(damage);
			p->SetSpeed(projectileSpeed);
			p->SetDirection(Vector3(direction.x, -direction.z, 0));
			p->SetLifetime(10);
			p->SetAABB(Vector3(0.5f, 0.5f, 0.5f), Vector3(-0.5f, -0.5f, -0.5f));
			p->source = Projectile::PLAYER_SOURCE;
			p->SetStatus(true);

			CSoundEngine::GetInstance()->playsinglesound("PEW", 0.2f);

			states.pop();
		}
	}
	++i;
}
