#include "tp_math.h"


Matrix4x4::Matrix4x4()
{
	value[0][0] = 1; value[0][1] = 0; value[0][2] = 0; value[0][3] = 0;
	value[1][0] = 0; value[1][1] = 1; value[1][2] = 0; value[1][3] = 0;
	value[2][0] = 0; value[2][1] = 0; value[2][2] = 1; value[2][3] = 0;
	value[3][0] = 0; value[3][1] = 0; value[3][2] = 0; value[3][3] = 1;

}


Matrix4x4::~Matrix4x4()
{
	value[0][0] = 1; value[0][1] = 0; value[0][2] = 0; value[0][3] = 0;
	value[1][0] = 0; value[1][1] = 1; value[1][2] = 0; value[1][3] = 0;
	value[2][0] = 0; value[2][1] = 0; value[2][2] = 1; value[2][3] = 0;
	value[3][0] = 0; value[3][1] = 0; value[3][2] = 0; value[3][3] = 1;
}

/**
*矩阵单位化
*/
void Matrix4x4::identity()
{
	value[0][0] = 1; value[0][1] = 0; value[0][2] = 0; value[0][3] = 0;
	value[1][0] = 0; value[1][1] = 1; value[1][2] = 0; value[1][3] = 0;
	value[2][0] = 0; value[2][1] = 0; value[2][2] = 1; value[2][3] = 0;
	value[3][0] = 0; value[3][1] = 0; value[3][2] = 0; value[3][3] = 1;
}
/**
*矩阵缩放
*/
void Matrix4x4::scale(const Vector3& vec)
{
	value[0][0] = vec.x; value[0][1] = 0;     value[0][2] = 0;     value[0][3] = 0;
	value[1][0] = 0;     value[1][1] = vec.y; value[1][2] = 0;     value[1][3] = 0;
	value[2][0] = 0;     value[2][1] = 0;     value[2][2] = vec.z; value[2][3] = 0;
	value[3][0] = 0;     value[3][1] = 0;     value[3][2] = 0;     value[3][3] = 1;
}

/**
*旋转矩阵
*/
void Matrix4x4::rotate(const Vector3& dir, float angle)
{
	float _angle = angle * (float) PI / 180;
	float _c = cosf(_angle);
	float _s = sinf(_angle);

	if (dir.x == 1)
	{
		value[0][0] = 1;     value[0][1] = 0;  value[0][2] = 0;    value[0][3] = 0;
		value[1][0] = 0;     value[1][1] = _c; value[1][2] = -_s;  value[1][3] = 0;
		value[2][0] = 0;     value[2][1] = _s; value[2][2] = _c;  value[2][3] = 0;
		value[3][0] = 0;     value[3][1] = 0;  value[3][2] = 0;    value[3][3] = 1;
	}
	else if (dir.y == 1)
	{
		value[0][0] = _c; value[0][1] = 0;     value[0][2] = _s;     value[0][3] = 0;
		value[1][0] = 0;  value[1][1] = 1;     value[1][2] =  0;     value[1][3] = 0;
		value[2][0] = -_s;value[2][1] = 0;     value[2][2] = _c;     value[2][3] = 0;
		value[3][0] = 0;  value[3][1] = 0;     value[3][2] = 0;      value[3][3] = 1;
	}
	else if (dir.z == 1)
	{
		value[0][0] = _c; value[0][1] = -_s;   value[0][2] = 0;     value[0][3] = 0;
		value[1][0] = _s; value[1][1] = _c;    value[1][2] = 0;     value[1][3] = 0;
		value[2][0] = 0;  value[2][1] = 0;     value[2][2] = 1;     value[2][3] = 0;
		value[3][0] = 0;  value[3][1] = 0;     value[3][2] = 0;     value[3][3] = 1;
	}
}

/**
*齐次矩阵
*/
void Matrix4x4::project(const Vector3& vec)
{
	value[0][0] = 1; value[0][1] = 0; value[0][2] = 0; value[0][3] = 0;
	value[1][0] = 0; value[1][1] = 1; value[1][2] = 0; value[1][3] = 0;
	value[2][0] = 0; value[2][1] = 0; value[2][2] = 1; value[2][3] = 0;
	value[3][0] = vec.x; value[3][1] = vec.y; value[3][2] = vec.z; value[3][3] = 1;
}

/**
*平移
*/
Vector3& Matrix4x4::operator *(const Vector3& vec)
{
	Vector3 result;

	result.x = value[0][0] * vec.x + value[0][1] * vec.y + value[0][2] * vec.z;
	result.y = value[1][0] * vec.x + value[1][1] * vec.y + value[1][2] * vec.z;
	result.z = value[2][0] * vec.x + value[2][1] * vec.y + value[2][2] * vec.z;

	return result;
}

/**
*矩阵乘法
*/
Matrix4x4& Matrix4x4::operator *(const Matrix4x4& mat)
{
	Matrix4x4 result;
	//1行
	result.value[0][0] = value[0][0] * mat.value[0][0] + value[0][1] * mat.value[1][0] + value[0][2] * mat.value[2][0] + value[0][3] * mat.value[3][0];
	result.value[0][1] = value[0][0] * mat.value[0][1] + value[0][1] * mat.value[1][1] + value[0][2] * mat.value[2][1] + value[0][3] * mat.value[3][1];
	result.value[0][2] = value[0][0] * mat.value[0][2] + value[0][1] * mat.value[1][2] + value[0][2] * mat.value[2][2] + value[0][3] * mat.value[3][2];
	result.value[0][3] = value[0][0] * mat.value[0][3] + value[0][1] * mat.value[1][3] + value[0][2] * mat.value[2][3] + value[0][3] * mat.value[3][3];
	//2行
	result.value[1][0] = value[1][0] * mat.value[0][0] + value[1][1] * mat.value[1][0] + value[1][2] * mat.value[2][0] + value[1][3] * mat.value[3][0];
	result.value[1][1] = value[1][0] * mat.value[0][1] + value[1][1] * mat.value[1][1] + value[1][2] * mat.value[2][1] + value[1][3] * mat.value[3][1];
	result.value[1][2] = value[1][0] * mat.value[0][2] + value[1][1] * mat.value[1][2] + value[1][2] * mat.value[2][2] + value[1][3] * mat.value[3][2];
	result.value[1][3] = value[1][0] * mat.value[0][3] + value[1][1] * mat.value[1][3] + value[1][2] * mat.value[2][3] + value[1][3] * mat.value[3][3];
	//3行
	result.value[2][0] = value[2][0] * mat.value[0][0] + value[2][1] * mat.value[1][0] + value[2][2] * mat.value[2][0] + value[2][3] * mat.value[3][0];
	result.value[2][1] = value[2][0] * mat.value[0][1] + value[2][1] * mat.value[1][1] + value[2][2] * mat.value[2][1] + value[2][3] * mat.value[3][1];
	result.value[2][2] = value[2][0] * mat.value[0][2] + value[2][1] * mat.value[1][2] + value[2][2] * mat.value[2][2] + value[2][3] * mat.value[3][2];
	result.value[2][3] = value[2][0] * mat.value[0][3] + value[2][1] * mat.value[1][3] + value[2][2] * mat.value[2][3] + value[2][3] * mat.value[3][3];
	//4行
	result.value[3][0] = value[3][0] * mat.value[0][0] + value[3][1] * mat.value[1][0] + value[3][2] * mat.value[2][0] + value[3][3] * mat.value[3][0];
	result.value[3][1] = value[3][0] * mat.value[0][1] + value[3][1] * mat.value[1][1] + value[3][2] * mat.value[2][1] + value[3][3] * mat.value[3][1];
	result.value[3][2] = value[3][0] * mat.value[0][2] + value[3][1] * mat.value[1][2] + value[3][2] * mat.value[2][2] + value[3][3] * mat.value[3][2];
	result.value[3][3] = value[3][0] * mat.value[0][3] + value[3][1] * mat.value[1][3] + value[3][2] * mat.value[2][3] + value[3][3] * mat.value[3][3];

	//copy
	value[0][0] = result.value[0][0]; value[0][1] = result.value[0][1]; value[0][2] = result.value[0][2]; value[0][3] = result.value[0][3];
	value[1][0] = result.value[1][0]; value[1][1] = result.value[1][1]; value[1][2] = result.value[1][2]; value[1][3] = result.value[1][3];
	value[2][0] = result.value[2][0]; value[2][1] = result.value[2][1]; value[2][2] = result.value[2][2]; value[2][3] = result.value[2][3];
	value[3][0] = result.value[3][0]; value[3][1] = result.value[3][1]; value[3][2] = result.value[3][2]; value[3][3] = result.value[3][3];

	return *this;
}

void Matrix4x4::ortho(float left, float right, float bottom, float top, float zNear,
	float zFar)
{
	//矩阵单位化
	identity();
	value[0][0] = float(2)  / (right - left);
	value[1][1] = float(2)  / (top - bottom);
	value[2][2] = -float(2) / (zFar - zNear);
	value[3][0] = -(right + left) / (right - left);
	value[3][1] = -(top + bottom) / (top - bottom);
	value[3][2] = -(zFar + zNear) / (zFar - zNear);
}

void Matrix4x4::perspective(float fovy, float aspect, float zNear, float zFar)
{
	identity();
	float range = (float)tan(fovy * float(DEG2RAD(0.5))) * zNear;
	float left = -range * aspect;
	float right = range * aspect;
	float bottom = -range;
	float top = range;

	value[0][0] = (float(2) * zNear) / (right - left);
	value[1][1] = (float(2) * zNear) / (top - bottom);
	value[2][2] = -(zFar + zNear) / (zFar - zNear);
	value[2][3] = -float(1);
	value[3][2] = -(float(2) * zFar * zNear) / (zFar - zNear);
}

void Matrix4x4::lookAt(Vector3 &_eye,Vector3 &_center,Vector3 &_up)
{
	Vector3 f = _center - _eye;
	f.normailze();
	Vector3 u  = _up;
	u.normailze();
	Vector3 s = f.cross(u);
	s.normailze();
	u = s.cross(f);

	//矩阵单位化
	identity();
	value[0][0] = s.x;
	value[1][0] = s.y;
	value[2][0] = s.z;
	value[0][1] = u.x;
	value[1][1] = u.y;
	value[2][1] = u.z;
	value[0][2] = -f.x;
	value[1][2] = -f.y;
	value[2][2] = -f.z;
	value[3][0] = -(s * _eye);
	value[3][1] = -(u * _eye);
	value[3][2] =  f * _eye;
}

