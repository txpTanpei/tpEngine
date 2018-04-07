#include"include.h"

Camera::Camera()
{
	_moveSpeed = 5;
	_eye = Vector3(.0, 10.0, .0);
	_look = Vector3(.5, -0.4f, -0.5f);
	_up = Vector3(0, 1, 0);
	_right = Vector3(1, 0, 0);
}

Camera::~Camera()
{
}

void Camera::updateCamera(float fpsTime)
{
	Vector3 tmpLook = _look;
	Vector3 dir = _look - _eye;
	dir.normailze();

	unsigned char keys[256];
	GetKeyboardState(keys);
	if (keys[VK_UP] & 0x80)
	{
		_eye -= dir * -_moveSpeed * fpsTime;
		_look -= dir * -_moveSpeed *fpsTime;
	}
	if (keys[VK_DOWN] & 0x80)
	{
		_eye += (dir * -_moveSpeed) * fpsTime;
		_look += (dir * -_moveSpeed) *fpsTime;
	}
	if (keys[VK_LEFT] & 0x80)
	{
		_eye -= (_right * -_moveSpeed) * fpsTime;
		_look -= (_right * -_moveSpeed) *fpsTime;
	}
	if (keys[VK_RIGHT] & 0x80)
	{
		_eye +=  (_right * _moveSpeed) * fpsTime;
		_look += (_right * _moveSpeed) *fpsTime;
	}
}
