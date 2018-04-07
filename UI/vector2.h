#ifndef __VECTOR2_H__
#define __VECTOR2_H__

struct Vector2
{
	float x;
	float y;

	float& operator[](size_t i);
	float const & operator[](size_t  i)const;
	Vector2();
	Vector2(Vector2 const&v);
	Vector2(float const&v);

	Vector2(float const&s1, float const& s2);
	Vector2& operator = (Vector2 const &v);
}; //end struct Vector2

#endif // !__VECTOR2_H__
