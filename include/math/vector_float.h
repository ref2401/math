#ifndef MATH_VECTOR_FLOAT_H_
#define MATH_VECTOR_FLOAT_H_

#include <ostream>
#include "math/utility.h"


namespace math {

struct float2 final {

	static const float2 unit_x;
	static const float2 unit_y;
	static const float2 unit_xy;
	static const float2 zero;


	float2() noexcept : x(0), y(0) {}

	explicit float2(float val) noexcept : x(val), y(val) {}

	float2(float x, float y) noexcept : x(x), y(y) {}


	float2& operator+=(float val) noexcept
	{
		x += val;
		y += val;
		return *this;
	}

	float2& operator+=(const float2& v) noexcept
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	float2& operator-=(float val) noexcept
	{
		x -= val;
		y -= val;
		return *this;
	}

	float2& operator-=(const float2& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	float2& operator*=(float val) noexcept
	{
		x *= val;
		y *= val;
		return *this;
	}

	float2& operator/=(float val) noexcept
	{
		assert(!approx_equal(val, 0.0f));

		x /= val;
		y /= val;
		return *this;
	}


	float x;
	float y;
};

struct float3 final {};

struct float4 final {};



inline bool operator==(const float2& l, const float2& r) noexcept
{
	return (l.x == r.x) && (l.y == r.y);
}

inline bool operator!=(const float2& l, const float2& r) noexcept
{
	return !(l == r);
}

//inline bool approx_equal(const float2& l, const float2& r) noexcept
//{
//
//}

} // namespace math

#endif // MATH_VECTOR_FLOAT_H_
