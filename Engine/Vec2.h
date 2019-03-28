#pragma once

class Vec2
{
public:
	Vec2 operator + (const Vec2& rhs) const;
	Vec2& operator += (const Vec2& rhs);
	Vec2 operator * (float rhs) const;
	Vec2& operator *= (float rhs);
	Vec2(float in_x, float in_y);
	float GetLengthSq();
	float GetLength();
	Vec2 GetNormalized();
	Vec2& Normalize();
public:
	float x;
	float y;
};