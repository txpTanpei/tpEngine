#ifndef __VECTOR3_H__
#define __VECTOR3_H__

struct Vector3
{
public:
	Vector3() : x(.0),y(.0),z(0.){}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	//方法用到在实现

	Vector3& operator + (const Vector3& v1);
	Vector3& operator - (const Vector3& v1);

	Vector3& operator * (float value);
	Vector3& operator / (float value);

	Vector3& operator +=(const Vector3& v1);
	Vector3& operator -=(const Vector3& v1);

	Vector3& cross(Vector3& v1);

	float operator * (Vector3& v1);

	void normailze();

public:
	float x;
	float y;
	float z;
};

#endif // !__VECTOR3_H__




