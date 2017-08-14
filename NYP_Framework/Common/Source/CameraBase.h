#ifndef CAMERA_BASE_H
#define CAMERA_BASE_H

#include "Mtx44.h"

class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase();

	virtual Mtx44 GetViewMatrix() = 0;

	virtual Vector3 GetCameraPos() const;
	virtual void SetCameraPos(Vector3 pos);
	virtual Vector3 GetCameraTarget() const;
	virtual void SetCameraTarget(Vector3 pos);
	virtual Vector3 GetCameraUp() const;
	virtual void SetCameraUp(Vector3 pos);

protected:
	Vector3 position;
	Vector3 target;
	Vector3 up;

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
};

#endif // CAMERA_BASE_H