#ifndef __MATRIX4X4_H__
#define __MATRIX4X4_H__

#include <math.h>

struct Vector3;

class Matrix4x4
{
public:
	Matrix4x4();
	~Matrix4x4();

	/**
	*����λ��
	*/
	void identity();
	/**
	*��������
	*/
	void scale(const Vector3& vec);

	/**
	*��ת����
	*/
	void rotate(const Vector3& dir,float angle);

	/**
	*��ξ���
	*/
	void project(const Vector3& vec);

	/**
	*ƽ��
	*/
	Vector3& operator *(const Vector3& vec);
	/**
	*����˷�
	*/
	Matrix4x4& operator *(const Matrix4x4& mat);
	/**
	*�������������
	*/
	void ortho(float left, float right, float bottom, float top, float zNear,
		float zFar);
	/**
	*�����͸�Ӿ���
	*/
	void perspective(float fovy, float aspect, float zNear, float zFar);

	/**
	*�۲����
	*/
	void lookAt(Vector3 &_eye,Vector3 &_look,Vector3 &_up);
public:
	float value[4][4];

};

#endif //end __MATRIX4X4_H__


