#ifndef __CAMERA_H__
#define __CAMERA_H__

#include"Vector3.h"

class Camera
{
public:
	Camera();
	~Camera();

	void updateCamera(float fpsTime);

public:
	//摄像机的位置
	Vector3 _eye;
	//摄像机观察的方向
	Vector3 _look;
	//摄像机向上的方向
	Vector3 _up;
	//摄像机右边方向
	Vector3 _right;
	//摄像机移动速度
	float _moveSpeed;
};

#endif // !__CAMERA_H__



