#include"tp_math.h"
float& Vector2::operator[](size_t i)
{
	return (&x)[i];
}
float const & Vector2::operator[](size_t  i)const
{
	return (&x)[i];
}

Vector2::Vector2():
	x(0),
	y(0)
{
}

Vector2::Vector2(Vector2 const&v):
	x(v.x),
	y(v.y)
{
}

Vector2::Vector2(float const&v) :
	x(v),
	y(v)
{

}
Vector2::Vector2(float const&s1, float const& s2):
	x(s1),
	y(s2)
{

}

Vector2& Vector2::operator = (Vector2 const &v)
{
	this->x = v.x;
	this->y = v.y;
	return *this;
}