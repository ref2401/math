#ifndef MATH_VECTOR_INT_H_
#define MATH_VECTOR_INT_H_

#include <cassert>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include "math/utility.h"


namespace math {

template<typename T>
struct vec_int_2 final {

	static_assert(std::is_integral<T>::value, "T must be an integral type.");

	using component_type = T;


	static const vec_int_2<T> unit_x;
	static const vec_int_2<T> unit_y;
	static const vec_int_2<T> unit_xy;
	static const vec_int_2<T> zero;


	constexpr vec_int_2() noexcept = default;

	constexpr explicit vec_int_2(T v) noexcept : x(v), y(v) {}

	constexpr vec_int_2(T x, T y) noexcept : x(x), y(y) {}


	vec_int_2<T>& operator+=(T val) noexcept
	{
		x += val;
		y += val;
		return *this;
	}

	vec_int_2<T>& operator+=(const vec_int_2<T>& v) noexcept
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	vec_int_2<T>& operator-=(T val) noexcept
	{
		if (std::is_signed<T>::value) {
			assert(x >= val);
			assert(y >= val);
		}

		x -= val;
		y -= val;
		return *this;
	}

	vec_int_2<T>& operator-=(const vec_int_2<T>& v) noexcept
	{
		if (std::is_signed<T>::value) {
			assert(x >= v.x);
			assert(y >= v.y);
		}

		x -= v.x;
		y -= v.y;
		return *this;
	}

	vec_int_2<T>& operator*=(T val) noexcept
	{
		x *= val;
		y *= val;
		return *this;
	}

	vec_int_2<T>& operator/=(T val) noexcept
	{
		assert(val != 0);

		x /= val;
		y /= val;
		return *this;
	}


	T x = 0;
	T y = 0;
};

template<typename T>
struct vec_int_3 final {
	
	static_assert(std::is_integral<T>::value, "T must be an integral type.");

	using component_type = T;


	static const vec_int_3<T> unit_x;
	static const vec_int_3<T> unit_y;
	static const vec_int_3<T> unit_z;
	static const vec_int_3<T> unit_xyz;
	static const vec_int_3<T> zero;


	constexpr vec_int_3() noexcept = default;

	constexpr explicit vec_int_3(T v) noexcept : x(v), y(v), z(v) {}

	constexpr explicit vec_int_3(const vec_int_2<T>& v, T z = 0) noexcept : x(v.x), y(v.y), z(z) {}

	constexpr vec_int_3(T x, T y, T z) noexcept : x(x), y(y), z(z) {}


	vec_int_3<T>& operator+=(T val) noexcept
	{
		x += val;
		y += val;
		z += val;
		return *this;
	}

	vec_int_3<T>& operator+=(const vec_int_3<T>& v) noexcept
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vec_int_3<T>& operator-=(T val) noexcept
	{
		if (std::is_signed<T>::value) {
			assert(x >= val);
			assert(y >= val);
			assert(z >= val);
		}

		x -= val;
		y -= val;
		z -= val;
		return *this;
	}

	vec_int_3<T>& operator-=(const vec_int_3<T>& v) noexcept
	{
		if (std::is_signed<T>::value) {
			assert(x >= v.x);
			assert(y >= v.y);
			assert(z >= v.z);
		}

		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	vec_int_3<T>& operator*=(T val) noexcept
	{
		x *= val;
		y *= val;
		z *= val;
		return *this;
	}

	vec_int_3<T>& operator/=(T val) noexcept
	{
		assert(val != 0);

		x /= val;
		y /= val;
		z /= val;
		return *this;
	}

	explicit operator vec_int_2<T>() const noexcept
	{
		return vec_int_2<T>(x, y);
	}


	T x = 0;
	T y = 0;
	T z = 0;
};

template<typename T>
struct vec_int_4 final {

	static_assert(std::is_integral<T>::value, "T must be an integral type.");

	using component_type = T;


	static const vec_int_4<T> unit_x;
	static const vec_int_4<T> unit_y;
	static const vec_int_4<T> unit_z;
	static const vec_int_4<T> unit_w;
	static const vec_int_4<T> unit_xyzw;
	static const vec_int_4<T> zero;


	constexpr vec_int_4() noexcept = default;

	constexpr explicit vec_int_4(T val) noexcept : x(val), y(val), z(val), w(val) {}

	constexpr explicit vec_int_4(const vec_int_2<T>& v, T z = 0, T w = 1) noexcept 
		: x(v.x), y(v.y), z(z), w(w)
	{}

	constexpr explicit vec_int_4(const vec_int_3<T>& v, T w = 1) noexcept
		: x(v.x), y(v.y), z(v.z), w(w)
	{}

	constexpr vec_int_4(T x, T y, T z, T w) noexcept : x(x), y(y), z(z), w(w) {}


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
		if (std::is_signed<T>::value) {
			assert(x >= val);
			assert(y >= val);
			assert(z >= val);
			assert(w >= val);
		}

		x -= val;
		y -= val;
		z -= val;
		w -= val;
		return *this;
	}

	vec_int_4<T>& operator-=(const vec_int_4<T>& v) noexcept
	{
		if (std::is_signed<T>::value) {
			assert(x >= v.x);
			assert(y >= v.y);
			assert(z >= v.z);
			assert(w >= v.w);
		}

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

	explicit operator vec_int_2<T>() const noexcept
	{
		return vec_int_2<T>(x, y);
	}

	explicit operator vec_int_3<T>() const noexcept
	{
		return vec_int_3<T>(x, y, z);
	}


	T x = 0;
	T y = 0;
	T z = 0;
	T w = 0;
};


template<typename T> const vec_int_2<T> vec_int_2<T>::unit_x(1, 0);
template<typename T> const vec_int_2<T> vec_int_2<T>::unit_y(0, 1);
template<typename T> const vec_int_2<T> vec_int_2<T>::unit_xy(1, 1);
template<typename T> const vec_int_2<T> vec_int_2<T>::zero(0, 0);
template<typename T> const vec_int_3<T> vec_int_3<T>::unit_x(1, 0, 0);
template<typename T> const vec_int_3<T> vec_int_3<T>::unit_y(0, 1, 0);
template<typename T> const vec_int_3<T> vec_int_3<T>::unit_z(0, 0, 1);
template<typename T> const vec_int_3<T> vec_int_3<T>::unit_xyz(1, 1, 1);
template<typename T> const vec_int_3<T> vec_int_3<T>::zero(0, 0, 0);
template<typename T> const vec_int_4<T> vec_int_4<T>::unit_x(1, 0, 0, 0);
template<typename T> const vec_int_4<T> vec_int_4<T>::unit_y(0, 1, 0, 0);
template<typename T> const vec_int_4<T> vec_int_4<T>::unit_z(0, 0, 1, 0);
template<typename T> const vec_int_4<T> vec_int_4<T>::unit_w(0, 0, 0, 1);
template<typename T> const vec_int_4<T> vec_int_4<T>::unit_xyzw(1, 1, 1, 1);
template<typename T> const vec_int_4<T> vec_int_4<T>::zero(0, 0, 0, 0);

using int2 = vec_int_2<int32_t>;
using int3 = vec_int_3<int32_t>;
using int4 = vec_int_4<int32_t>;
using ubyte4 = vec_int_4<uint8_t>;
using uint2 = vec_int_2<uint32_t>;
using uint3 = vec_int_3<uint32_t>;
using uint4 = vec_int_4<uint32_t>;


template<typename T>
inline bool operator==(const vec_int_2<T>& l, const vec_int_2<T>& r) noexcept
{
	return (l.x == r.x) && (l.y == r.y);
}

template<typename T>
inline bool operator!=(const vec_int_2<T>& l, const vec_int_2<T>& r) noexcept
{
	return !(l == r);
}

template<typename T>
inline bool operator==(const vec_int_3<T>& l, const vec_int_3<T>& r) noexcept
{
	return (l.x == r.x)
		&& (l.y == r.y)
		&& (l.z == r.z);
}

template<typename T>
inline bool operator!=(const vec_int_3<T>& l, const vec_int_3<T>& r) noexcept
{
	return !(l == r);
}

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
inline vec_int_2<T> operator+(const vec_int_2<T>& v, T val) noexcept
{
	return vec_int_2<T>(v.x + val, v.y + val);
}

template<typename T>
inline vec_int_2<T> operator+(T val, const vec_int_2<T>& v) noexcept
{
	return vec_int_2<T>(v.x + val, v.y + val);
}

template<typename T>
inline vec_int_2<T> operator+(const vec_int_2<T>& l, const vec_int_2<T>& r) noexcept
{
	return vec_int_2<T>(l.x + r.x, l.y + r.y);
}

template<typename T>
inline vec_int_3<T> operator+(const vec_int_3<T>& v, T val) noexcept
{
	return vec_int_3<T>(v.x + val, v.y + val, v.z + val);
}

template<typename T>
inline vec_int_3<T> operator+(T val, const vec_int_3<T>& v) noexcept
{
	return vec_int_3<T>(v.x + val, v.y + val, v.z + val);
}

template<typename T>
inline vec_int_3<T> operator+(const vec_int_3<T>& l, const vec_int_3<T>& r) noexcept
{
	return vec_int_3<T>(l.x + r.x, l.y + r.y, l.z + r.z);
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
inline vec_int_2<T> operator-(const vec_int_2<T>& v, T val) noexcept
{
	if (std::is_unsigned<T>::value) {
		assert(v.x >= val);
		assert(v.y >= val);
	}

	return vec_int_2<T>(v.x - val, v.y - val);
}

template<typename T>
inline vec_int_2<T> operator-(T val, const vec_int_2<T>& v) noexcept
{
	if (std::is_unsigned<T>::value) {
		assert(val >= v.x);
		assert(val >= v.y);
	}

	return vec_int_2<T>(val - v.x, val - v.y);
}

template<typename T>
inline vec_int_2<T> operator-(const vec_int_2<T>& l, const vec_int_2<T>& r) noexcept
{
	if (std::is_unsigned<T>::value) {
		assert(l.x >= r.x);
		assert(l.y >= r.y);
	}

	return vec_int_2<T>(l.x - r.x, l.y - r.y);
}

template<typename T>
inline vec_int_3<T> operator-(const vec_int_3<T>& v, T val) noexcept
{
	if (std::is_unsigned<T>::value) {
		assert(v.x >= val);
		assert(v.y >= val);
		assert(v.z >= val);
	}

	return vec_int_3<T>(v.x - val, v.y - val, v.z - val);
}

template<typename T>
inline vec_int_3<T> operator-(T val, const vec_int_3<T>& v) noexcept
{
	if (std::is_unsigned<T>::value) {
		assert(val >= v.x);
		assert(val >= v.y);
		assert(val >= v.z);
	}

	return vec_int_3<T>(val - v.x, val - v.y, val - v.z);
}

template<typename T>
inline vec_int_3<T> operator-(const vec_int_3<T>& l, const vec_int_3<T>& r) noexcept
{
	if (std::is_unsigned<T>::value) {
		assert(l.x >= r.x);
		assert(l.y >= r.y);
		assert(l.z >= r.z);
	}

	return vec_int_3<T>(l.x - r.x, l.y - r.y, l.z - r.z);
}

template<typename T>
inline vec_int_4<T> operator-(const vec_int_4<T>& v, T val) noexcept
{
	if (std::is_unsigned<T>::value) {
		assert(v.x >= val);
		assert(v.y >= val);
		assert(v.z >= val);
		assert(v.w >= val);
	}

	return vec_int_4<T>(v.x - val, v.y - val, v.z - val, v.w - val);
}

template<typename T>
inline vec_int_4<T> operator-(T val, const vec_int_4<T>& v) noexcept
{
	if (std::is_unsigned<T>::value) {
		assert(val >= v.x);
		assert(val >= v.y);
		assert(val >= v.z);
		assert(val >= v.w);
	}

	return vec_int_4<T>(val - v.x, val - v.y, val - v.z, val - v.w);
}

template<typename T>
inline vec_int_4<T> operator-(const vec_int_4<T>& l, const vec_int_4<T>& r) noexcept
{
	if (std::is_unsigned<T>::value) {
		assert(l.x >= r.x);
		assert(l.y >= r.y);
		assert(l.z >= r.z);
		assert(l.w >= r.w);
	}

	return vec_int_4<T>(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w);
}

template<typename T>
inline
typename std::enable_if<std::is_signed<T>::value, vec_int_2<T>>::type
operator-(const vec_int_2<T>& v) noexcept
{
	return vec_int_2<T>(-v.x, -v.y);
}

template<typename T>
inline
typename std::enable_if<std::is_signed<T>::value, vec_int_3<T>>::type
operator-(const vec_int_3<T>& v) noexcept
{
	return vec_int_3<T>(-v.x, -v.y, -v.z);
}

template<typename T>
inline 
typename std::enable_if<std::is_signed<T>::value, vec_int_4<T>>::type 
operator-(const vec_int_4<T>& v) noexcept
{
	return vec_int_4<T>(-v.x, -v.y, -v.z, -v.w);
}

template<typename T>
inline vec_int_2<T> operator*(const vec_int_2<T>& v, T val) noexcept
{
	return vec_int_2<T>(v.x * val, v.y * val);
}

template<typename T>
inline vec_int_2<T> operator*(T val, const vec_int_2<T>& v) noexcept
{
	return vec_int_2<T>(v.x * val, v.y * val);
}

template<typename T>
inline vec_int_2<T> operator*(const vec_int_2<T>& l, const vec_int_2<T>& r) noexcept
{
	return vec_int_2<T>(r.x * l.x, r.y * l.y);
}

template<typename T>
inline vec_int_3<T> operator*(const vec_int_3<T>& v, T val) noexcept
{
	return vec_int_3<T>(v.x * val, v.y * val, v.z * val);
}

template<typename T>
inline vec_int_3<T> operator*(T val, const vec_int_3<T>& v) noexcept
{
	return vec_int_3<T>(v.x * val, v.y * val, v.z * val);
}

template<typename T>
inline vec_int_3<T> operator*(const vec_int_3<T>& l, const vec_int_3<T>& r) noexcept
{
	return vec_int_3<T>(r.x * l.x, r.y * l.y, r.z * l.z);
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
inline vec_int_4<T> operator*(const vec_int_4<T>& l, const vec_int_4<T>& r) noexcept
{
	return vec_int_4<T>(r.x * l.x, r.y * l.y, r.z * l.z, r.w * l.w);
}

template<typename T>
inline vec_int_2<T> operator/(const vec_int_2<T>& v, T val) noexcept
{
	assert(val != 0);
	return vec_int_2<T>(v.x / val, v.y / val);
}

template<typename T>
inline vec_int_2<T> operator/(T val, const vec_int_2<T>& v) noexcept
{
	assert(v.x != 0);
	assert(v.y != 0);
	return vec_int_2<T>(val / v.x, val / v.y);
}

template<typename T>
inline vec_int_2<T> operator/(const vec_int_2<T>& l, const vec_int_2<T>& r) noexcept
{
	assert(r.x != 0);
	assert(r.y != 0);
	return vec_int_2<T>(l.x / r.x, l.y / r.y);
}

template<typename T>
inline vec_int_3<T> operator/(const vec_int_3<T>& v, T val) noexcept
{
	assert(val != 0);
	return vec_int_3<T>(v.x / val, v.y / val, v.z / val);
}

template<typename T>
inline vec_int_3<T> operator/(T val, const vec_int_3<T>& v) noexcept
{
	assert(v.x != 0);
	assert(v.y != 0);
	assert(v.z != 0);
	return vec_int_3<T>(val / v.x, val / v.y, val / v.z);
}

template<typename T>
inline vec_int_3<T> operator/(const vec_int_3<T>& l, const vec_int_3<T>& r) noexcept
{
	assert(r.x != 0);
	assert(r.y != 0);
	assert(r.z != 0);
	return vec_int_3<T>(l.x / r.x, l.y / r.y, l.z / r.z);
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
inline vec_int_4<T> operator/(const vec_int_4<T>& l, const vec_int_4<T>& r) noexcept
{
	assert(r.x != 0);
	assert(r.y != 0);
	assert(r.z != 0);
	assert(r.w != 0);
	return vec_int_4<T>(l.x / r.x, l.y / r.y, l.z / r.z, l.w / r.w);
}

template<typename T, typename U>
inline bool operator<(const vec_int_2<T>& l, U val) noexcept
{
	static_assert(std::is_integral<U>::value, "U must be an integral type.");
	const T tmp(val);

	return (l.x < tmp) && (l.y < tmp);
}

template<typename T, typename U>
inline bool operator>(const vec_int_2<T>& l, U val) noexcept
{
	static_assert(std::is_integral<U>::value, "U must be an integral type.");
	const T tmp(val);

	return (l.x > tmp) && (l.y > tmp);
}

template<typename T, typename U>
inline bool operator<=(const vec_int_2<T>& l, U val) noexcept
{
	static_assert(std::is_integral<U>::value, "U must be an integral type.");
	const T tmp(val);

	return (l.x <= tmp) && (l.y <= tmp);
}

template<typename T, typename U>
inline bool operator>=(const vec_int_2<T>& l, U val) noexcept
{
	static_assert(std::is_integral<U>::value, "U must be an integral type.");
	const T tmp(val);

	return (l.x >= tmp) && (l.y >= tmp);
}

template<typename T, typename U>
inline bool operator<(const vec_int_3<T>& l, U val) noexcept
{
	static_assert(std::is_integral<U>::value, "U must be an integral type.");
	const T tmp(val);

	return (l.x < tmp) && (l.y < tmp) && (l.z < tmp);
}

template<typename T, typename U>
inline bool operator>(const vec_int_3<T>& l, U val) noexcept
{
	static_assert(std::is_integral<U>::value, "U must be an integral type.");
	const T tmp(val);

	return (l.x > tmp) && (l.y > tmp) && (l.z > tmp);
}

template<typename T, typename U>
inline bool operator<=(const vec_int_3<T>& l, U val) noexcept
{
	static_assert(std::is_integral<U>::value, "U must be an integral type.");
	const T tmp(val);

	return (l.x <= tmp) && (l.y <= tmp) && (l.z <= tmp);
}

template<typename T, typename U>
inline bool operator>=(const vec_int_3<T>& l, U val) noexcept
{
	static_assert(std::is_integral<U>::value, "U must be an integral type.");
	const T tmp(val);

	return (l.x >= tmp) && (l.y >= tmp) && (l.z >= tmp);
}

template<typename T, typename U>
inline bool operator<(const vec_int_4<T>& l, U val) noexcept
{
	static_assert(std::is_integral<U>::value, "U must be an integral type.");
	const T tmp(val);

	return (l.x < tmp) && (l.y < tmp) && (l.z < tmp) && (l.w < tmp);
}

template<typename T, typename U>
inline bool operator>(const vec_int_4<T>& l, U val) noexcept
{
	static_assert(std::is_integral<U>::value, "U must be an integral type.");
	const T tmp(val);

	return (l.x > tmp) && (l.y > tmp) && (l.z > tmp) && (l.w > tmp);
}

template<typename T, typename U>
inline bool operator<=(const vec_int_4<T>& l, U val) noexcept
{
	static_assert(std::is_integral<U>::value, "U must be an integral type.");
	const T tmp(val);

	return (l.x <= tmp) && (l.y <= tmp) && (l.z <= tmp) && (l.w <= tmp);
}

template<typename T, typename U>
inline bool operator>=(const vec_int_4<T>& l, U val) noexcept
{
	static_assert(std::is_integral<U>::value, "U must be an integral type.");
	const T tmp(val);

	return (l.x >= tmp) && (l.y >= tmp) && (l.z >= tmp) && (l.w >= tmp);
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const vec_int_2<T>& v)
{
	out << "vec_int_2<T>(" << v.x << ", " << v.y << ")";
	return out;
}

template<typename T>
std::wostream& operator<<(std::wostream& out, const vec_int_2<T>& v)
{
	out << "vec_int_2<T>(" << v.x << ", " << v.y << ")";
	return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const vec_int_3<T>& v)
{
	out << "vec_int_4<T>(" << v.x << ", " << v.y << ", " << v.z << ")";
	return out;
}

template<typename T>
std::wostream& operator<<(std::wostream& out, const vec_int_3<T>& v)
{
	out << "vec_int_4<T>(" << v.x << ", " << v.y << ", " << v.z << ")";
	return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const vec_int_4<T>& v)
{
	out << "vec_int_4<T>(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return out;
}

template<typename T>
std::wostream& operator<<(std::wostream& out, const vec_int_4<T>& v)
{
	out << "vec_int_4<T>(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return out;
}

template<typename T>
inline float aspect_ratio(const vec_int_2<T>& v) noexcept
{
	assert(v.y != 0);
	return float(v.x) / v.y;
}

template<typename T>
inline vec_int_2<T> clamp(const vec_int_2<T>& v, const vec_int_2<T>& lo, 
	const vec_int_2<T>& hi) noexcept
{
	return vec_int_2<T>(clamp(v.x, lo.x, hi.x), clamp(v.y, lo.y, hi.y));
}

template<typename T>
inline vec_int_3<T> clamp(const vec_int_3<T>& v, const vec_int_3<T>& lo,
	const vec_int_3<T>& hi) noexcept
{
	return vec_int_3<T>(
		clamp(v.x, lo.x, hi.x), 
		clamp(v.y, lo.y, hi.y),
		clamp(v.z, lo.z, hi.z)
	);
}

template<typename T>
inline vec_int_4<T> clamp(const vec_int_4<T>& v, const vec_int_4<T>& lo,
	const vec_int_4<T>& hi) noexcept
{
	return vec_int_4<T>(
		clamp(v.x, lo.x, hi.x), 
		clamp(v.y, lo.y, hi.y),
		clamp(v.z, lo.z, hi.z),
		clamp(v.w, lo.w, hi.w)
	);
}

template<typename T>
constexpr T area(const vec_int_2<T>& v) noexcept
{
	return v.x * v.y;
}

template<typename T>
constexpr T area(const vec_int_3<T>& v) noexcept
{
	return v.x * v.y;
}

template<typename T>
constexpr T area(const vec_int_4<T>& v) noexcept
{
	return v.x * v.y;
}

template<typename T>
[[deprecated("Use math::area() instead. To call the function 'square' was a stupid idea at the first place.")]] 
constexpr T square(const vec_int_2<T>& v) noexcept
{
	return v.x * v.y;
}

template<typename T>
[[deprecated("Use math::area() instead. To call the function 'square' was a stupid idea at the first place.")]]
constexpr T square(const vec_int_3<T>& v) noexcept
{
	return v.x * v.y;
}

template<typename T>
[[deprecated("Use math::area() instead. To call the function 'square' was a stupid idea at the first place.")]]
constexpr T square(const vec_int_4<T>& v) noexcept
{
	return v.x * v.y;
}

template<typename T>
constexpr T volume(const vec_int_3<T>& v) noexcept
{
	return v.x * v.y * v.z;
}

template<typename T>
constexpr T volume(const vec_int_4<T>& v) noexcept
{
	return v.x * v.y * v.z;
}

template<typename T>
constexpr vec_int_2<T> xy(const vec_int_3<T>& v) noexcept
{
	return vec_int_2<T>(v.x, v.y);
}

template<typename T>
constexpr vec_int_2<T> xy(const vec_int_4<T>& v) noexcept
{
	return vec_int_2<T>(v.x, v.y);
}

template<typename T>
constexpr vec_int_3<T> xyz(const vec_int_4<T>& v) noexcept
{
	return vec_int_3<T>(v.x, v.y, v.z);
}

} // namespace math

#endif // MATH_VECTOR_INT_H_
