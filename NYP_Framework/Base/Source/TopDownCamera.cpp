#include "TopDownCamera.h"

TopDownCamera::TopDownCamera()
{
}

TopDownCamera::~TopDownCamera()
{
}

Mtx44 TopDownCamera::GetViewMatrix()
{
	Mtx44 result;
	result.SetToLookAt(position.x, position.y, position.z,
		target.x, target.y, target.z,
		up.x, up.y, up.z);
	return result;
}

void TopDownCamera::Init(const Vector3 & pos, const Vector3 & target, const Vector3 & up, const float &height)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	this->height.Set(0, height, 0);
}

void TopDownCamera::Update(double dt)
{
	//no update for topdown as camera follows character
}

void TopDownCamera::Reset()
{
	//should not have reset as well as it must always follow the player
}

Vector3 TopDownCamera::GetHeight()
{
	return height;
}

void TopDownCamera::SetHeight(Vector3 _value)
{
	height = _value;
}
