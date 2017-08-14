#include "CameraBase.h"

CameraBase::CameraBase()
{
}

CameraBase::~CameraBase()
{
}

Vector3 CameraBase::GetCameraPos() const
{
	return position;
}

void CameraBase::SetCameraPos(Vector3 pos)
{
	position = pos;
}
Vector3 CameraBase::GetCameraTarget() const
{
	return target;
}
void CameraBase::SetCameraTarget(Vector3 target)
{
	this->target = target;
}
Vector3 CameraBase::GetCameraUp() const
{
	return up;
}
void CameraBase::SetCameraUp(Vector3 up)
{
	this->up = up;
}