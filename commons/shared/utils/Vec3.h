#pragma once

template <typename T>
class Vec3
{
public:
	Vec3() = default;
	constexpr Vec3(T x, T y, T z)
		:
		x(x),
		y(y),
		z(z)
	{}
	constexpr T GetX() const { return this->x; };
	constexpr T GetY() const { return this->y; };
	constexpr T GetZ() const { return this->z; };
	constexpr void SetX(T x) { this->x = x; };
	constexpr void SetY(T y) { this->y = y; };
	constexpr void SetZ(T z) { this->z = z; };
	
	template <class C>
	constexpr Vec3<C> As() {
		return Vec3<C>{(C)x, (C)y, (C)z};
	}

	template <class C, class T>
	constexpr C CastTo() {
		return C {(T)x, (T)y, (T)z};
	}

public:
	constexpr bool operator==(const Vec3& rhs) const
	{
		return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z);
	}
	constexpr bool operator!=(const Vec3& rhs) const
	{
		return !(*this == rhs);
	}
	constexpr Vec3 operator+(const Vec3& rhs) const
	{
		return { (T)(this->x + rhs.x), (T)(this->y + rhs.y), (T)(this->z + rhs.z) };
	}
	constexpr Vec3 operator+(const T rhs) const
	{
		return { this->x + rhs, this->y + rhs, this->z + rhs.z };
	}
	constexpr Vec3& operator+=(const Vec3& rhs)
	{
		return *this = *this + rhs;
	}
	constexpr Vec3 operator-(const Vec3& rhs) const
	{
		return { this->x - rhs.x, this->y - rhs.y, this->z - rhs.z };
	}
	constexpr Vec3 operator-(const T rhs) const
	{
		return { this->x - rhs, this->y - rhs, this->z - rhs };
	}
	constexpr Vec3& operator-=(const Vec3& rhs)
	{
		return *this = *this - rhs;
	}
	constexpr Vec3 operator*(const Vec3& rhs) const
	{
		return { this->x * rhs.x, this->y * rhs.y, this->z * rhs.z };
	}
	constexpr Vec3 operator*(const T rhs) const
	{
		return { this->x * rhs, this->y * rhs, this->z * rhs };
	}
	constexpr Vec3& operator*=(const Vec3& rhs)
	{
		return *this = *this * rhs;
	}
	constexpr Vec3 operator/(const T rhs) const
	{
		return { this->x / rhs, this->y / rhs, this->z / rhs };
	}
	// Real modulo operator, returns natural numbers
	constexpr Vec3 operator% (const T rhs) const {
		return {
			(this->x % rhs) * ((this->x % rhs) >= 0) + (rhs + (this->x % rhs)) * !((this->x % rhs) >= 0),
			(this->y % rhs) * ((this->y % rhs) >= 0) + (rhs + (this->y % rhs)) * !((this->y % rhs) >= 0),
			(this->z % rhs) * ((this->z % rhs) >= 0) + (rhs + (this->z % rhs)) * !((this->z % rhs) >= 0)
		};
	}
	constexpr Vec3 operator% (const Vec3& rhs) const {
		return {
			(this->x % rhs.x) * ((this->x % rhs.x) >= 0) + (rhs.x + (this->x % rhs.x)) * !((this->x % rhs.x) >= 0),
			(this->y % rhs.y) * ((this->y % rhs.y) >= 0) + (rhs.y + (this->y % rhs.y)) * !((this->y % rhs.y) >= 0),
			(this->z % rhs.z) * ((this->z % rhs.z) >= 0) + (rhs.z + (this->z % rhs.z)) * !((this->z % rhs.z) >= 0)
		};
	}
private:
	T x;
	T y;
	T z;
};