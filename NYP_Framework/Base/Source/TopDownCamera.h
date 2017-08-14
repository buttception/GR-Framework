#pragma once
#ifndef TOP_DOWN_CAMERA_H
#define TOP_DONW_CAMERA_H

#include "CameraBase.h"

class TopDownCamera : public CameraBase {
public:
	TopDownCamera();
	virtual ~TopDownCamera();

	virtual Mtx44 GetViewMatrix();

	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up, const float &height);
	virtual void Update(double dt);
	virtual void Reset();

	Vector3 GetHeight();
	void SetHeight(Vector3 _value);

private:
	Vector3 height;
};

#endif