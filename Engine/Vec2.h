#pragma once

class Vec2
{
public:
	Vec2 operator + (const Vec2& rhs) const;
	Vec2& operator += (const Vec2& rhs);
	Vec2(float in_x, float in_y);
	float GetLengthSq();
	float GetLength();
	Vec2 GetNormalized();
	void Normalize();
public:
	float x;
	float y;
};