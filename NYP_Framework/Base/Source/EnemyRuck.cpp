#include "EnemyRuck.h"
#include "MeshList.h"
#include "PlayerInfo\PlayerInfo.h"
#include "Sound_Engine.h"
#include "Projectile\Projectile.h"
#include "SceneText.h"

EnemyRuck::EnemyRuck(std::string _meshName, Vector3 pos) : EnemyEntity(_meshName)
{
	position = pos;
	range = 40;
}

EnemyRuck::~EnemyRuck()
{
}

void EnemyRuck::Init()
{
	stateStack.push(DEFAULT_STATE);
	attackElaspedTime = 0;
	attacking = false;
	attackSpeed = 1.5;
	attackType = MELEE_ATTACK;
	speed = 7;
	damage = 5;
	health = 50;
	size = 2.5f;
	scale.Set(size, size, size);
	optimalRoute.push(Vector3(MAX_CELLS * CELL_SIZE / 2, 0, MAX_CELLS * CELL_SIZE / 2));
	direction = (optimalRoute.top() - position).Normalized();
	active = true;
}

void EnemyRuck::Update(double dt)
{
	if (!active)
		return;
	if (target == Player::GetInstance())
		attackType = RANGED_ATTACK;
	if (!attacking) {
		switch (stateStack.top()) {
		case StateMachine::DEFAULT_STATE:
			// if enemy reached a node
			if ((int)position.x == optimalRoute.top().x && (int)position.z == optimalRoute.top().z) {
				// pop the stack
				optimalRoute.pop();
			}
			// find new direction to next node
			if (optimalRoute.empty())
				stateStack.push(StateMachine::NONE);
			else {
				direction = (optimalRoute.top() - position).Normalized();
			}
			direction.y = 0;
			direction.Normalize();
			position += direction * speed * dt;
			//updates AABB if enemy move
			SetAABB(Vector3(position.x + size / 2, position.y + size / 2, position.z + size / 2), Vector3(position.x - size / 2, position.y - size / 2, position.z - size / 2));

			if ((position - Player::GetInstance()->GetPosition()).LengthSquared() < (range + 5) * (range + 5)) {
				stateStack.push(CHASE_STATE);
				target = Player::GetInstance();
			}
			break;
		case StateMachine::ATTACK_STATE:

			if (target != nullptr) {
				attacking = true;
			}
			stateStack.pop();
			break;
		case StateMachine::CHASE_STATE:
			try {
				if (target == nullptr)
					stateStack.pop();
				else {
					direction = (target->GetPosition() - position);
					direction.y = 0;
					direction.Normalize();
				}
			}
			catch (std::exception &e) {
				direction.SetZero();
			}

			//shoot the player if withing range
			if ((position - Player::GetInstance()->GetPosition()).LengthSquared() < range * range) {
				if ((position - Player::GetInstance()->GetPosition()).LengthSquared() < (range - 5) * (range - 5)) {
					stateStack.push(FLEE_STATE);
				}
				else
					stateStack.push(ATTACK_STATE);
			}

			position += direction * speed * dt;
			SetAABB(Vector3(position.x + size / 2, position.y + size / 2, position.z + size / 2), Vector3(position.x - size / 2, position.y - size / 2, position.z - size / 2));
			break;
		case FLEE_STATE:
			direction = (position - Player::GetInstance()->GetPosition());
			direction.y = 0;
			direction.Normalize();
			position += direction * speed * dt;

			if ((position - Player::GetInstance()->GetPosition()).LengthSquared() > (range) * (range))
				stateStack.pop();
				break;
		default:
			return;
		}
	}
	else if (attacking) {
		Attack(target, dt);
	}
}

void EnemyRuck::CollisionResponse(GenericEntity * thatEntity)
{
	if (active) {
		switch (thatEntity->objectType) {
		case GenericEntity::BUILDING:
			//if collide with a building
			//set state to attack mode
			//if enemy is not already in attack mode
			if (!stateStack.empty())
				if (stateStack.top() != ATTACK_STATE)
					stateStack.push(ATTACK_STATE);
			target = thatEntity;
			break;
		case EntityBase::PROJECTILE: {
			Projectile* p = dynamic_cast<Projectile*>(thatEntity);
			if (p->source != Projectile::ENEMY_SOURCE) {
				health -= p->GetDamage();
				if (health <= 0)
					active = false;
			}
			p->SetIsDone(true);
		}
			break;
		case EntityBase::EQUIPMENT: {
			EquipmentEntity* equipment = dynamic_cast<EquipmentEntity*>(thatEntity);
			// Attack Equipment except floor spike and healing station
			if (stateStack.top() != ATTACK_STATE &&
				equipment->type != EquipmentEntity::EQUIPMENT_FLOOR_SPIKE &&
				equipment->type != EquipmentEntity::EQUIPMENT_HEALING_STATION)
			{
				stateStack.push(ATTACK_STATE);
				target = thatEntity;
			}
			break;
			switch (equipment->type) {
			case EquipmentEntity::EQUIPMENT_TURRET:
				std::cout << "collided with turret" << std::endl;
				break;
			case EquipmentEntity::EQUIPMENT_FLOOR_SPIKE:
				if (equipment->spikeTimer >= equipment->spikeCoolDown)
				{
					switch (equipment->GetLevel())
					{
					case 1:
						health = Math::Max(0, health - 10);
						break;
					case 2:
						health = Math::Max(0, health - 20);
						break;
					case 3:
						health = Math::Max(0, health - 30);
						break;
					}
					speed = 2.f;
					equipment->spikeTimer = 0.f;
				}
				if (health == 0)
					SetActive(false);
				break;
			}
		}
			break;
		default:
			return;
		}
	}
	else
		return;
}

void EnemyRuck::Attack(GenericEntity * thatEntity, double dt)
{
	if (!active)
		return;

	attackElaspedTime += (float)dt;
	direction = (Player::GetInstance()->GetPosition() - position).Normalized();
	// if ruck is melee attack mode
	if (attackType == MELEE_ATTACK) {
		if (attackElaspedTime >= attackSpeed) {
			//check if still in contact with its target
			//test if this is too weak against player
			if (target)
			{
				if (thatEntity->objectType == BUILDING) {
					BuildingEntity* building = dynamic_cast<BuildingEntity*>(thatEntity);
					if (building) {
						// damage the building
						building->SetHealth(building->GetHealth() - damage);
						// check if the building is dead
						if (building->GetHealth() <= 0) {
							//destroy the building
							building->SetIsDone(true);
							if (building->type != BuildingEntity::BUILDING_CORE) {
								if (building->tile->leftWall == building) {
									building->tile->leftWall = nullptr;
								}
								else if (building->tile->rightWall == building) {
									building->tile->rightWall = nullptr;
								}
								else if (building->tile->topWall == building) {
									building->tile->topWall = nullptr;
								}
								else if (building->tile->bottomWall == building) {
									building->tile->bottomWall = nullptr;
								}
							}
							if (stateStack.top() == CHASE_STATE)
								target = Player::GetInstance();
							else
								target = nullptr;
						}
					}
				}
				else if (thatEntity->objectType == EQUIPMENT) {
					EquipmentEntity* e;
					if (e = dynamic_cast<EquipmentEntity*>(thatEntity)) {
						if (e->type == EquipmentEntity::EQUIPMENT_TURRET) {
							e->SetHealth(e->GetHealth() - damage);
							if (e->GetHealth() <= 0) {
								e->SetIsDone(true);
								if (e->tile->equipment == e) {
									e->tile->equipment = nullptr;
								}
							}
						}
					}
					if (stateStack.top() == CHASE_STATE)
						target = Player::GetInstance();
					else
						target = nullptr;
				}
				else {
					stateStack.pop();
					if (stateStack.top() == CHASE_STATE)
						target = Player::GetInstance();
				}
			}
			// resets attack time
			attackElaspedTime = 0.f;
			// stop attack animation
			attacking = false;

			CSoundEngine::GetInstance()->playsinglesound("MELEE", 0.1f);	
		}
	}
	else {
		if (attackElaspedTime >= attackSpeed) {
			//if ranged enemy is attacking player
			Projectile* aProjectile = Create::Bullet("sphere");
			aProjectile->SetPosition(position);
			aProjectile->SetCollider(true);
			aProjectile->SetLifetime(10);
			aProjectile->SetDamage(damage);
			aProjectile->SetDirection(Vector3(direction.x, -direction.z, 0));
			aProjectile->SetStatus(true);
			aProjectile->SetAABB(Vector3(0.5f, 0.5f, 0.5f), Vector3(-0.5f, -0.5f, -0.5f));
			aProjectile->source = Projectile::ENEMY_SOURCE;
			aProjectile->SetSpeed(20.f);
			// resets attack time
			attackElaspedTime = 0.f;
			// stop attack animation
			attacking = false;

			//shoot the player if withing range
			if ((position - Player::GetInstance()->GetPosition()).LengthSquared() < range * range) {
				if ((position - Player::GetInstance()->GetPosition()).LengthSquared() < (range - 5) * (range - 10)) {
					stateStack.push(FLEE_STATE);
				}
				else
					stateStack.push(ATTACK_STATE);
			}

			CSoundEngine::GetInstance()->playsinglesound("PEW", 0.1f);
		}
	}
}

EnemyRuck * Create::Ruck(std::string _meshName, Vector3 pos)
{
	EnemyRuck* ruck = new EnemyRuck(_meshName, pos);
	EntityManager::GetInstance()->AddEntity(ruck);
	return ruck;
}
