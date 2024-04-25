#pragma once
#include <raylib.h>

template <typename T>
class Vec2
{
public:
	Vec2() = default;
	constexpr Vec2(T x, T y)
		:
		x(x),
		y(y)
	{}
	constexpr T GetX() const { return this->x; };
	constexpr T GetY() const { return this->y; };
	constexpr void SetX(T x) { this->x = x; };
	constexpr void SetY(T y) { this->y = y; };
public:
	constexpr bool operator==(const Vec2& rhs) const
	{
		return (this->x == rhs.x && this->y == rhs.y);
	}
	constexpr bool operator!=(const Vec2& rhs) const
	{
		return !(*this == rhs);
	}
	constexpr Vec2 operator+(const Vec2& rhs) const
	{
		return { this->x + rhs.x, this->y + rhs.y };
	}
	constexpr Vec2 operator+(const int rhs) const
	{
		return { this->x + rhs, this->y + rhs };
	}
	constexpr Vec2& operator+=(const Vec2& rhs)
	{
		return *this = *this + rhs;
	}
	constexpr Vec2 operator-(const Vec2& rhs) const
	{
		return { this->x - rhs.x, this->y - rhs.y };
	}
	constexpr Vec2 operator-(const int rhs) const
	{
		return { this->x - rhs, this->y - rhs };
	}
	constexpr Vec2& operator-=(const Vec2& rhs)
	{
		return *this = *this - rhs;
	}
	constexpr Vec2 operator*(const Vec2& rhs) const
	{
		return { this->x * rhs.x, this->y * rhs.y };
	}
	constexpr Vec2 operator*(const int rhs) const
	{
		return { this->x * rhs, this->y * rhs };
	}
	constexpr Vec2& operator*=(const Vec2& rhs)
	{
		return *this = *this * rhs;
	}
	constexpr Vec2 operator/(const int rhs) const
	{
		return { this->x / rhs, this->y / rhs };
	}
	constexpr operator Vector2() const {
		return { (float)x,(float)y };
	}

private:
	T x;
	T y;
};