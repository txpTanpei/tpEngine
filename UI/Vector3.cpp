#include"tp_math.h"

Vector3& Vector3::operator + (const Vector3& v)
{
	Vector3 result;

	result.x = x + v.x;
	result.y = y + v.y;
	result.z = z + v.z;

	return result;
}
Vector3& Vector3::operator - (const Vector3& v)
{
	Vector3 result;

	result.x = x - v.x;
	result.y = y - v.y;
	result.z = z - v.z;

	return result;
}

Vector3& Vector3::operator * (float value)
{
	Vector3 result;
	result.x = x * value;
	result.y = y * value;
	result.z = z * value;
	return result;
}
Vector3& Vector3::operator / (float value)
{
	Vector3 result;
	result.x = x / value;
	result.y = y / value;
	result.z = z / value;
	return result;
}

Vector3& Vector3::operator +=(const Vector3& v1)
{
	Vector3 result;
	result.x +=v1.x;
	result.y +=v1.y;
	result.z +=v1.z;
	return result;
}

Vector3& Vector3::operator -=(const Vector3& v1)
{
	Vector3 result;
	result.x -= v1.x;
	result.y -= v1.y;
	result.z -= v1.z;
	return result;
}

void Vector3::normailze()
{
	float flag = x * x + y * y + z * z;
	float _v = flag / sqrtf(flag);
	x = x * _v;
	y = y * _v;
	z = z * _v;
}

Vector3& Vector3::cross(Vector3& v1)
{
	Vector3 result;
	result.x = x * v1.z - v1.y * z;
	result.y = z * v1.x - v1.z * x;
	result.z = x * v1.y - v1.x * y;
	return result;
}

float Vector3::operator * (Vector3& v1)
{
	return x * v1.x + y * v1.y + z * v1.z;
}
