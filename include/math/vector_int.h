#ifndef MATH_VECTOR_INT_H_
#define MATH_VECTOR_INT_H_

#include <cassert>
#include <cstdint>
#include <iostream>
#include <type_traits>


namespace math {

template<typename T>
struct vec_int_2 final {

	static_assert(std::is_integral<T>::value, "T must be an integral type.");

	static const vec_int_2<T> unit_x;
	static const vec_int_2<T> unit_y;
	static const vec_int_2<T> unit_xy;
	static const vec_int_2<T> zero;


	vec_int_2() noexcept = default;

	explicit vec_int_2(T v) noexcept : x(v), y(v) {}

	vec_int_2(T x, T y) noexcept : x(x), y(y) {}


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
		assert(x >= val);
		assert(y >= val);

		x -= val;
		y -= val;
		return *this;
	}

	vec_int_2<T>& operator-=(const vec_int_2<T>& v) noexcept
	{
		assert(x >= v.x);
		assert(y >= v.y);

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
struct vec_int_4 final {

	static_assert(std::is_integral<T>::value, "T must be an integral type.");

	static const vec_int_4<T> unit_x;
	static const vec_int_4<T> unit_y;
	static const vec_int_4<T> unit_z;
	static const vec_int_4<T> unit_w;
	static const vec_int_4<T> unit_xyzw;
	static const vec_int_4<T> zero;


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


template<typename T> const vec_int_2<T> vec_int_2<T>::unit_x(1, 0);
template<typename T> const vec_int_2<T> vec_int_2<T>::unit_y(0, 1);
template<typename T> const vec_int_2<T> vec_int_2<T>::unit_xy(1, 1);
template<typename T> const vec_int_2<T> vec_int_2<T>::zero(0, 0);
template<typename T> const vec_int_4<T> vec_int_4<T>::unit_x(1, 0, 0, 0);
template<typename T> const vec_int_4<T> vec_int_4<T>::unit_y(0, 1, 0, 0);
template<typename T> const vec_int_4<T> vec_int_4<T>::unit_z(0, 0, 1, 0);
template<typename T> const vec_int_4<T> vec_int_4<T>::unit_w(0, 0, 0, 1);
template<typename T> const vec_int_4<T> vec_int_4<T>::unit_xyzw(1, 1, 1, 1);
template<typename T> const vec_int_4<T> vec_int_4<T>::zero(0, 0, 0, 0);

using int2 = vec_int_2<int32_t>;
using int4 = vec_int_4<int32_t>;
using ubyte4 = vec_int_4<uint8_t>;
using uint2 = vec_int_2<uint32_t>;
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
	assert(v.x >= val);
	assert(v.y >= val);
	return vec_int_2<T>(v.x - val, v.y - val);
}

template<typename T>
inline vec_int_2<T> operator-(T val, const vec_int_2<T>& v) noexcept
{
	assert(val >= v.x);
	assert(val >= v.y);
	return vec_int_2<T>(val - v.x, val - v.y);
}

template<typename T>
inline vec_int_2<T> operator-(const vec_int_2<T>& l, const vec_int_2<T>& r) noexcept
{
	assert(l.x >= r.x);
	assert(l.y >= r.y);
	return vec_int_2<T>(l.x - r.x, l.y - r.y);
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
inline
typename std::enable_if<std::is_signed<T>::value, vec_int_2<T>>::type
operator-(const const vec_int_2<T>& v) noexcept
{
	return vec_int_2<T>(-v.x, -v.y);
}

template<typename T>
inline 
typename std::enable_if<std::is_signed<T>::value, vec_int_4<T>>::type 
operator-(const const vec_int_4<T>& v) noexcept
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
inline vec_int_2<T> operator/(const vec_int_2<T>& v, T val) noexcept
{
	assert(val != 0);
	return vec_int_2<T>(v.x / val, v.y / val, v.z / val, v.w / val);
}

template<typename T>
inline vec_int_2<T> operator/(T val, const vec_int_2<T>& v) noexcept
{
	assert(v.x != 0);
	assert(v.y != 0);
	assert(v.z != 0);
	assert(v.w != 0);
	return vec_int_2<T>(val / v.x, val / v.y, val / v.z, val / v.w);
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
inline bool operator<(const vec_int_2<T>& l, T val) noexcept
{
	return (l.x < val) && (l.y < val);
}

template<typename T>
inline bool operator>(const vec_int_2<T>& l, T val) noexcept
{
	return (l.x > val) && (l.y > val);
}

template<typename T>
inline bool operator<=(const vec_int_2<T>& l, T val) noexcept
{
	return (l.x <= val) && (l.y <= val);
}

template<typename T>
inline bool operator>=(const vec_int_2<T>& l, T val) noexcept
{
	return (l.x >= val) && (l.y >= val);
}

template<typename T>
inline bool operator<(const vec_int_4<T>& l, T val) noexcept
{
	return (l.x < val) && (l.y < val) && (l.z < val) && (l.w < val);
}

template<typename T>
inline bool operator>(const vec_int_4<T>& l, T val) noexcept
{
	return (l.x > val) && (l.y > val) && (l.z > val) && (l.w > val);
}

template<typename T>
inline bool operator<=(const vec_int_4<T>& l, T val) noexcept
{
	return (l.x <= val) && (l.y <= val) && (l.z <= val) && (l.w <= val);
}

template<typename T>
inline bool operator>=(const vec_int_4<T>& l, T val) noexcept
{
	return (l.x >= val) && (l.y >= val) && (l.z >= val) && (l.w >= val);
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


} // namespace math

#endif // MATH_VECTOR_INT_H_
