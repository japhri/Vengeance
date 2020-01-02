#include "Vec2.h"
#include <cmath>

Vec2::Vec2() : x(0.0f), y(0.0f) {}
Vec2::Vec2(float v) : x(v), y(v) {}
Vec2::Vec2(int v) : x(static_cast<float>(v)), y(static_cast<float>(v)) {}
Vec2::Vec2(float x_, float y_) : x(x_), y(y_) {}
Vec2::Vec2(float x_, int y_) : x(x_), y(static_cast<float>(y_)) {}
Vec2::Vec2(int x_, float y_) : x(static_cast<float>(x_)), y(y_) {}
Vec2::Vec2(int x_, int y_) : x(static_cast<float>(x_)), y(static_cast<float>(y_)) {}

bool Vec2::operator==(const Vec2& rhs) const
{
	return x == rhs.x && y == rhs.y;
}

bool Vec2::operator!=(const Vec2& rhs) const
{
	return x != rhs.x || y != rhs.y;
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const Vec2& rhs) const
{
	return Vec2(x * rhs.x, y * rhs.y);
}

Vec2 Vec2::operator*(const float& rhs) const
{
	return Vec2(x * rhs, y * rhs);
}

Vec2 Vec2::operator/(const Vec2& rhs) const
{
	return Vec2(x / rhs.x, y / rhs.y);
}

Vec2 Vec2::operator/(const float& rhs) const
{
	return Vec2(x / rhs, y / rhs);
}

Vec2& Vec2::operator+=(const Vec2& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vec2& Vec2::operator-=(const Vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vec2& Vec2::operator*=(const Vec2& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}

Vec2& Vec2::operator*=(const float& rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}

Vec2& Vec2::operator/=(const Vec2& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}

Vec2& Vec2::operator/=(const float& rhs)
{
	x /= rhs;
	y /= rhs;
	return *this;
}

float Vec2::Length() const
{
	return sqrt(x * x + y * y);
}

Vec2& Vec2::Normalize()
{
	float length = Length();

	if (length <= 0.0f)
		return *this;

	x /= length;
	y /= length;

	return *this;
}

Vec2 Vec2::Normalized() const
{
	float length = Length();

	if (length <= 0.0f)
		return Vec2(0, 0);

	return Vec2(x / length, y / length);
}

float Vec2::Dot(Vec2& vec) const
{
	return x * vec.x + y * vec.y;
}

float Vec2::Dot(Vec2& a, Vec2& b)
{
	return a.x * b.x + a.y * b.y;
}


float Vec2::Distance(const Vec2& vec) const
{
	float dx = vec.x - x;
	float dy = vec.y - y;
	return sqrt(dx * dx + dy * dy);
}

float Vec2::Distance(const Vec2& vecA, const Vec2& vecB)
{
	float dx = vecB.x - vecA.x;
	float dy = vecB.y - vecA.y;
	return sqrt(dx * dx + dy * dy);
}


Vec2& Vec2::Lerp(const Vec2& target, const float mix)
{
	x = x * (1.0f - mix) + target.x * mix;
	y = y * (1.0f - mix) + target.y * mix;

	return *this;
}

Vec2 Vec2::Lerp(const Vec2& a, const Vec2& b, const float mix)
{
	return Vec2(a.x * (1.0f - mix) + b.x * mix, a.y * (1.0f - mix) + b.y * mix);
}

Vec2 Vec2::ZERO = Vec2(0, 0);
