#include "Projectile.h"

#include "MeshBuilder.h"
#include "../EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "../Sound_Engine.h"

Projectile::Projectile(std::string _meshName) : GenericEntity(MeshList::GetInstance()->GetMesh(_meshName))
, m_bStatus(false)
, theDirection(0, 0, 0)
, m_fLifetime(-1.0f)
, m_fSpeed(10.0f)
{

}

Projectile::~Projectile()
{
}

void Projectile::SetStatus(const bool m_bStatus)
{
	if (m_bStatus == false)
		m_fLifetime = -1;
	this->m_bStatus = m_bStatus;
}

bool Projectile::GetStatus(void) const
{
	return m_bStatus;
}

void Projectile::Set(Vector3 theNewPosition, Vector3 theNewDirection, const float m_fLifetime, const float m_fSpeed)
{
	position = theNewPosition;
	theDirection = theNewDirection;
	this->m_fLifetime = m_fLifetime;
	this->m_fSpeed = m_fSpeed;
}

void Projectile::SetDirection(Vector3 theNewDirection)
{
	theDirection = theNewDirection;
}

Vector3 Projectile::GetDirection(void)
{
	return theDirection;
}

void Projectile::SetLifetime(const float m_fLifetime)
{
	this->m_fLifetime = m_fLifetime;
}

float Projectile::GetLifetime(void) const
{
	return m_fLifetime;
}

void Projectile::SetSpeed(const float m_fSpeed)
{
	this->m_fSpeed = m_fSpeed;
}

float Projectile::GetSpeed(void) const
{
	return m_fSpeed;
}

void Projectile::Update(double dt)
{
	if (m_bStatus == false)
		return;

	// Update TimeLife of projectile. Set to inactive if too long
	m_fLifetime -= (float)dt;
	if (m_fLifetime < 0.0f)
	{
		SetStatus(false);
		SetIsDone(true);	// This method is to inform the EntityManager that it should remove this instance
		return;
	}

	// Update Position
	Vector3 d(theDirection.x, 0, -theDirection.y);
	position += d * (float)dt * m_fSpeed;
}

void Projectile::Render(void)
{
	if (m_bStatus == false)
		return;

	if (m_fLifetime < 0.0f)
		return;

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	//modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMesh(modelMesh);
	modelStack.PopMatrix();
}

Projectile * Create::Bullet(std::string _meshName)
{
	Projectile* p = new Projectile(_meshName);
	EntityManager::GetInstance()->AddEntity(p);
	return p;
	
}
