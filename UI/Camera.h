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
	//�������λ��
	Vector3 _eye;
	//������۲�ķ���
	Vector3 _look;
	//��������ϵķ���
	Vector3 _up;
	//������ұ߷���
	Vector3 _right;
	//������ƶ��ٶ�
	float _moveSpeed;
};

#endif // !__CAMERA_H__



