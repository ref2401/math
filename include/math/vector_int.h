#ifndef MATH_VECTOR_INT_H_
#define MATH_VECTOR_INT_H_

#include <cassert>
#include <cstdint>
#include <iostream>
#include <type_traits>


namespace math {

template<typename T>
struct vec_int_4 final {

	static_assert(std::is_integral<T>::value, "T must be an integral type.");


	vec_int_4() noexcept = default;

	vec_int_4(T val) noexcept : x(val), y(val), z(val), w(val) {}

	vec_int_4(T x, T y, T z, T w) noexcept : x(x), y(y), z(z), w(w) {}


	vec_int_4<T>& operator+=(T val) noexcept
	{
		x += val;
		y += val;
		z += val;
		w += val;
		return *this;
	}

	vec_int_4<T>& operator+=(const vec_int_4<T>& v) noexcept
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	vec_int_4<T>& operator-=(T val) noexcept
	{
		assert(x >= val);
		assert(y >= val);
		assert(z >= val);
		assert(w >= val);

		x -= val;
		y -= val;
		z -= val;
		w -= val;
		return *this;
	}

	vec_int_4<T>& operator-=(const vec_int_4<T>& v) noexcept
	{
		assert(x >= v.x);
		assert(y >= v.y);
		assert(z >= v.z);
		assert(w >= v.w);

		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	vec_int_4<T>& operator*=(T val) noexcept
	{
		x *= val;
		y *= val;
		z *= val;
		w *= val;
		return *this;
	}

	vec_int_4<T>& operator/=(T val) noexcept
	{
		assert(val != 0);

		x /= val;
		y /= val;
		z /= val;
		w /= val;
		return *this;
	}


	T x = 0;
	T y = 0;
	T z = 0;
	T w = 0;
};

template<typename T>
inline bool operator==(const vec_int_4<T>& l, const vec_int_4<T>& r) noexcept
{
	return (l.x == r.x)
		&& (l.y == r.y)
		&& (l.z == r.z)
		&& (l.w == r.w);
}

template<typename T>
inline bool operator!=(const vec_int_4<T>& l, const vec_int_4<T>& r) noexcept
{
	return !(l == r);
}

template<typename T>
inline vec_int_4<T> operator+(const vec_int_4<T>& v, T val) noexcept
{
	return vec_int_4<T>(v.x + val, v.y + val, v.z + val, v.w + val);
}

template<typename T>
inline vec_int_4<T> operator+(T val, const vec_int_4<T>& v) noexcept
{
	return vec_int_4<T>(v.x + val, v.y + val, v.z + val, v.w + val);
}

template<typename T>
inline vec_int_4<T> operator+(const vec_int_4<T>& l, const vec_int_4<T>& r) noexcept
{
	return vec_int_4<T>(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);
}

template<typename T>
inline vec_int_4<T> operator-(const vec_int_4<T>& v, T val) noexcept
{
	assert(v.x >= val);
	assert(v.y >= val);
	assert(v.z >= val);
	assert(v.w >= val);
	return vec_int_4<T>(v.x - val, v.y - val, v.z - val, v.w - val);
}

template<typename T>
inline vec_int_4<T> operator-(T val, const vec_int_4<T>& v) noexcept
{
	assert(val >= v.x);
	assert(val >= v.y);
	assert(val >= v.z);
	assert(val >= v.w);
	return vec_int_4<T>(val - v.x, val - v.y, val - v.z, val - v.w);
}

template<typename T>
inline vec_int_4<T> operator-(const vec_int_4<T>& l, const vec_int_4<T>& r) noexcept
{
	assert(l.x >= r.x);
	assert(l.y >= r.y);
	assert(l.z >= r.z);
	assert(l.w >= r.w);
	return vec_int_4<T>(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w);
}

template<typename T>
inline vec_int_4<T> operator*(const vec_int_4<T>& v, T val) noexcept
{
	return vec_int_4<T>(v.x * val, v.y * val, v.z * val, v.w * val);
}

template<typename T>
inline vec_int_4<T> operator*(T val, const vec_int_4<T>& v) noexcept
{
	return vec_int_4<T>(v.x * val, v.y * val, v.z * val, v.w * val);
}

template<typename T>
inline vec_int_4<T> operator/(const vec_int_4<T>& v, T val) noexcept
{
	assert(val != 0);
	return vec_int_4<T>(v.x / val, v.y / val, v.z / val, v.w / val);
}

template<typename T>
inline vec_int_4<T> operator/(T val, const vec_int_4<T>& v) noexcept
{
	assert(v.x != 0);
	assert(v.y != 0);
	assert(v.z != 0);
	assert(v.w != 0);
	return vec_int_4<T>(val / v.x, val / v.y, val / v.z, val / v.w);
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const vec_int_4<T>& v);

template<typename T>
std::wostream& operator<<(std::wostream& out, const vec_int_4<T>& v);

} // namespace math

#endif // MATH_VECTOR_INT_H_
