#include "Vec2.h"
#include <cmath>

Vec2 Vec2::operator+(const Vec2 & rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 & Vec2::operator+=(const Vec2 & rhs)
{
	return *this = *this + rhs;
}

Vec2::Vec2(float in_x, float in_y)
	:
	x(in_x),
	y(in_y)
{
}

float Vec2::GetLengthSq()
{
	return x*x + y*y;
}

float Vec2::GetLength()
{
	return sqrt(GetLengthSq());
}

Vec2 Vec2::GetNormalized()
{
	float length = GetLength();
	Vec2 res = { 0.0f,0.0f };
	res.x = x / length;
	res.y = y / length;
	return res;
}

void Vec2::Normalize()
{
	float length = GetLength();
	x = x / length;
	y = y / length;
}
