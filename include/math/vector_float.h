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

inline float2 operator+(const float2& v, float val) noexcept
{
	return float2(v.x + val, v.y + val);
}

inline float2 operator+(float val, const float2& v) noexcept
{
	return float2(v.x + val, v.y + val);
}

inline float2 operator+(const float2& l, const float2& r) noexcept
{
	return float2(l.x + r.x, l.y + r.y);
}

inline float2 operator-(const float2& v, float val) noexcept
{
	return float2(v.x - val, v.y - val);
}

inline float2 operator-(float val, const float2& v) noexcept
{
	return float2(val - v.x, val - v.y);
}

inline float2 operator-(const float2& l, const float2& r) noexcept
{
	return float2(l.x - r.x, l.y - r.y);
}

inline float2 operator-(const float2& v) noexcept
{
	return float2(-v.x, -v.y);
}

inline float2 operator*(const float2& v, float val) noexcept
{
	return float2(v.x * val, v.y * val);
}

inline float2 operator*(float val, const float2& v) noexcept
{
	return float2(v.x * val, v.y * val);
}

inline float2 operator*(const float2& l, const float2& r) noexcept
{
	return float2(l.x * r.x, l.y * r.y);
}

inline float2 operator/(const float2& v, float val) noexcept
{
	assert(!approx_equal(val, 0.0f));

	return float2(v.x / val, v.y / val);
}

inline float2 operator/(float val, const float2& v) noexcept
{
	assert(!approx_equal(v.x, 0.0f));
	assert(!approx_equal(v.y, 0.0f));

	return float2(val / v.x, val / v.y);
}

inline float2 operator/(const float2& l, const float2& r) noexcept
{
	assert(!approx_equal(r.x, 0.0f));
	assert(!approx_equal(r.y, 0.0f));

	return float2(l.x / r.x, l.y / r.y);
}

std::ostream& operator<<(std::ostream& out, const float2& v);

std::wostream& operator<<(std::wostream& out, const float2& v);

//std::ostream& operator<<(std::ostream& out, const float3& v);
//
//std::wostream& operator<<(std::wostream& out, const float3& v);
//
//std::ostream& operator<<(std::ostream& out, const float4& v);
//
//std::wostream& operator<<(std::wostream& out, const float4& v);

inline bool approx_equal(const float2& l, const float2& r, float max_abs_diff = 1e-5f) noexcept
{
	return approx_equal(l.x, r.x, max_abs_diff) && approx_equal(l.y, r.y, max_abs_diff);
}

// Constrains vector v to lie between two further vectors.
// The function processes each component of the vector separately.
// Params:
//		v = The value to constrain
//		v_lo =	The lower end of the range into which to constrain v.
//		v_hi = The upper end of the range into which to constrain v.
inline float2 clamp(const float2& v, const float2& lo = float2::zero,
	const float2& hi = float2::unit_xy) noexcept
{
	return float2(
		clamp(v.x, lo.x, hi.x),
		clamp(v.y, lo.y, hi.y)
	);
}

// Calculates the dot product of the given vectors.
inline float dot(const float2& l, const float2& r) noexcept
{
	return (l.x * r.x) + (l.y * r.y);
}

// Returns true if all the components of v are greater than val.
inline bool greater_than_all(const float2& v, float val) noexcept
{
	return (v.x > val) && (v.y > val);
}

// Calculates the squared length of v.
inline float len_squared(const float2& v) noexcept
{
	return (v.x * v.x) + (v.y * v.y);
}

// Checks whether the specified vector is normalized.
inline bool is_normalized(const float2& v) noexcept
{
	return approx_equal(len_squared(v), 1.0f);
}

// Calculates the length of v.
inline float len(const float2& v) noexcept
{
	return std::sqrt(len_squared(v));
}

// Linearly interpolates between two values.
// Params:
// -	l:		The start of the range in which to interpolate.
// -	r:		The end of the range in which to interpolate.
// -	factor:	The value to use to interpolate between lhs & rhs.
//				Factor has to lie within the range [0 .. 1].
inline float2 lerp(const float2& l, const float2& r, float factor) noexcept
{
	assert(0.0f <= factor && factor <= 1.0f);
	return l + factor * (r - l);
}

// Returns new vector which is normalized(unit length) copy of the given one.
inline float2 normalize(const float2& v) noexcept
{
	float l2 = len_squared(v);
	if (approx_equal(l2, 0.0f) || approx_equal(l2, 1.0f)) return v;

	float factor = 1.0f / sqrt(l2);
	return v * factor;
}

} // namespace math

#endif // MATH_VECTOR_FLOAT_H_
