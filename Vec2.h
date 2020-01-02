#pragma once

struct Vec2
{
	Vec2();
	Vec2(float v);
	Vec2(int v);
	Vec2(float x, float y);
	Vec2(float x, int y);
	Vec2(int x, float y);
	Vec2(int x, int y);

	float x;
	float y;

	bool operator==(const Vec2& rhs) const;
	bool operator!=(const Vec2& rhs) const;
	Vec2 operator+(const Vec2& rhs) const;
	Vec2 operator-(const Vec2& rhs) const;
	Vec2 operator*(const Vec2& rhs) const;
	Vec2 operator*(const float& rhs) const;
	Vec2 operator/(const Vec2& rhs) const;
	Vec2 operator/(const float& rhs) const;
	Vec2& operator+=(const Vec2& rhs);
	Vec2& operator-=(const Vec2& rhs);
	Vec2& operator*=(const Vec2& rhs);
	Vec2& operator*=(const float& rhs);
	Vec2& operator/=(const Vec2& rhs);
	Vec2& operator/=(const float& rhs);

	float Length() const;
	Vec2& Normalize();
	Vec2 Normalized() const;
	float Dot(Vec2& vec) const;
	static float Dot(Vec2& a, Vec2& b);

	float Distance(const Vec2& vec) const;
	static float Distance(const Vec2& vecA, const Vec2& vecB);

	Vec2& Lerp(const Vec2& target, const float mix);
	static Vec2 Lerp(const Vec2& a, const Vec2& b, const float mix);

	static Vec2 ZERO;
};
