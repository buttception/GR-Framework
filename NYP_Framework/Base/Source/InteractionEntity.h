#pragma once
#ifndef INTERACTION_H
#define INTERACTION_H

#include "EntityBase.h"
#include "Collider\Collider.h"
#include "Application.h"

class InteractionEntity : public EntityBase, public Collision {
public:
	InteractionEntity(float _posX, float _posY, float _scaleX, float _scaleY)
		:posX(_posX)
		,posY(_posY)
		,scaleX(_scaleX)
		,scaleY(_scaleY)
	{	
		xFull = Application::GetInstance().GetWindowWidth();
		yFull = Application::GetInstance().GetWindowHeight();
		x = xFull / 2;
		y = yFull / 2;
		position.Set(posX * x, posY * y, 0);
		scale.Set(scaleX * xFull, scaleY * yFull, 0);
		minAABB.Set(position.x - scale.x / 2, position.y - scale.y / 2, 0);
		maxAABB.Set(position.x + scale.x / 2, position.y + scale.y / 2, 0);
	}
	virtual ~InteractionEntity() {}

	void Update() {
		if (xFull != Application::GetInstance().GetWindowWidth() || yFull != Application::GetInstance().GetWindowHeight()) {
			xFull = Application::GetInstance().GetWindowWidth();
			yFull = Application::GetInstance().GetWindowHeight();
			x = xFull / 2;
			y = yFull / 2;
			position.Set(posX * x, posY * y, 0);
			scale.Set(scaleX * xFull, scaleY * yFull, 0);
			minAABB.Set(position.x - scale.x / 2, position.y - scale.y / 2, 0);
			maxAABB.Set(position.x + scale.x / 2, position.y + scale.y / 2, 0);
		}
	}
	int x, y;
	int xFull, yFull;
	float posX, posY;
	float scaleX, scaleY;
};

#endif
