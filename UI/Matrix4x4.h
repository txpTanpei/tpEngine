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
	*矩阵单位化
	*/
	void identity();
	/**
	*矩阵缩放
	*/
	void scale(const Vector3& vec);

	/**
	*旋转矩阵
	*/
	void rotate(const Vector3& dir,float angle);

	/**
	*齐次矩阵
	*/
	void project(const Vector3& vec);

	/**
	*平移
	*/
	Vector3& operator *(const Vector3& vec);
	/**
	*矩阵乘法
	*/
	Matrix4x4& operator *(const Matrix4x4& mat);
	/**
	*摄像机正交矩阵
	*/
	void ortho(float left, float right, float bottom, float top, float zNear,
		float zFar);
	/**
	*摄像机透视矩阵
	*/
	void perspective(float fovy, float aspect, float zNear, float zFar);

	/**
	*观察矩阵
	*/
	void lookAt(Vector3 &_eye,Vector3 &_look,Vector3 &_up);
public:
	float value[4][4];

};

#endif //end __MATRIX4X4_H__


