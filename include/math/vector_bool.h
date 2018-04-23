#ifndef MATH_VECTOR_BOOL_H_
#define MATH_VECTOR_BOOL_H_

#include <iostream>


namespace math {

struct bool2 final {
	constexpr bool2() = default;

	constexpr explicit bool2(bool v) : x(v), y(v) {}

	constexpr bool2(bool x, bool y) : x(x), y(y) {}


	bool x = false;
	bool y = false;
};

struct bool3 final {
	constexpr bool3() = default;

	constexpr explicit bool3(bool v) : x(v), y(v), z(v) {}

	constexpr explicit bool3(const bool2& v, bool z = false) : x(v.x), y(v.y), z(z) {}

	constexpr bool3(bool x, bool y, bool z) : x(x), y(y), z(z) {}


	bool x = false;
	bool y = false;
	bool z = false;
};

struct bool4 final {
	constexpr bool4() = default;

	constexpr explicit bool4(bool v) : x(v), y(v), z(v), w(v) {}

	constexpr explicit bool4(const bool2& v, bool z = false, bool w = true) : x(v.x), y(v.y), z(z), w(w) {}

	constexpr explicit bool4(const bool3& v, bool w = true) : x(v.x), y(v.y), z(v.z), w(w) {}

	constexpr bool4(bool x, bool y, bool z, bool w) : x(x), y(y), z(z), w(w) {}


	bool x = false;
	bool y = false;
	bool z = false;
	bool w = false;
};


constexpr bool operator==(const bool2& v0, const bool2& v1) noexcept
{
	return (v0.x == v1.x)
		&& (v0.y == v1.y);
}

constexpr bool operator!=(const bool2& v0, const bool2& v1) noexcept
{
	return !(v0 == v1);
}

constexpr bool operator==(const bool3& v0, const bool3& v1) noexcept
{
	return (v0.x == v1.x)
		&& (v0.y == v1.y)
		&& (v0.z == v1.z);
}

constexpr bool operator!=(const bool3& v0, const bool3& v1) noexcept
{
	return !(v0 == v1);
}

constexpr bool operator==(const bool4& v0, const bool4& v1) noexcept
{
	return (v0.x == v1.x)
		&& (v0.y == v1.y)
		&& (v0.z == v1.z)
		&& (v0.w == v1.w);
}

constexpr bool operator!=(const bool4& v0, const bool4& v1) noexcept
{
	return !(v0 == v1);
}

std::ostream& operator<<(std::ostream& out, const bool2& v);

std::wostream& operator<<(std::wostream& out, const bool2& v);

std::ostream& operator<<(std::ostream& out, const bool3& v);

std::wostream& operator<<(std::wostream& out, const bool3& v);

std::ostream& operator<<(std::ostream& out, const bool4& v);

std::wostream& operator<<(std::wostream& out, const bool4& v);

constexpr bool all(const bool2& v) noexcept
{
	return (v.x && v.y);
}

constexpr bool all(const bool3& v) noexcept
{
	return (v.x && v.y && v.z);
}

constexpr bool all(const bool4& v) noexcept
{
	return (v.x && v.y && v.z && v.w);
}

constexpr bool any(const bool2& v) noexcept
{
	return (v.x || v.y);
}

constexpr bool any(const bool3& v) noexcept
{
	return (v.x || v.y || v.z);
}

constexpr bool any(const bool4& v) noexcept
{
	return (v.x || v.y || v.z || v.w);
}

constexpr bool2 not(const bool2& v) noexcept
{
	return bool2(!v.x, !v.y);
}

constexpr bool3 not(const bool3& v) noexcept
{
	return bool3(!v.x, !v.y, !v.z);
}

constexpr bool4 not(const bool4& v) noexcept
{
	return bool4(!v.x, !v.y, !v.z, !v.w);
}

constexpr bool2 xy(const bool3& v) noexcept
{
	return bool2(v.x, v.y);
}

constexpr bool2 xy(const bool4& v) noexcept
{
	return bool2(v.x, v.y);
}

constexpr bool3 xyz(const bool4& v) noexcept
{
	return bool3(v.x, v.y, v.z);
}
 
} // namesapce math

#endif // MATH_VECTOR_BOOL_H_
