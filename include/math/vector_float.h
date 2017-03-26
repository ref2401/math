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

struct float3 final {
	static const float3 unit_x;
	static const float3 unit_y;
	static const float3 unit_z;
	static const float3 unit_xy;
	static const float3 unit_xyz;
	static const float3 zero;


	float3() noexcept : x(0), y(0), z(0) {}

	explicit float3(float val) noexcept : x(val), y(val), z(val) {}

	float3(const float2& v, float z) : x(v.x), y(v.y), z(z) {}

	float3(float x, float y, float z) noexcept : x(x), y(y), z(z) {}


	float3& operator+=(float val) noexcept
	{
		x += val;
		y += val;
		z += val;
		return *this;
	}

	float3& operator+=(const float3& v) noexcept
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	float3& operator-=(float val) noexcept
	{
		x -= val;
		y -= val;
		z -= val;
		return *this;
	}

	float3& operator-=(const float3& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	float3& operator*=(float val) noexcept
	{
		x *= val;
		y *= val;
		z *= val;
		return *this;
	}

	float3& operator/=(float val) noexcept
	{
		assert(!approx_equal(val, 0.0f));

		x /= val;
		y /= val;
		z /= val;
		return *this;
	}


	float x;
	float y;
	float z;
};

struct float4 final {};


inline bool operator==(const float2& l, const float2& r) noexcept
{
	return (l.x == r.x) && (l.y == r.y);
}

inline bool operator!=(const float2& l, const float2& r) noexcept
{
	return !(l == r);
}

inline bool operator==(const float3& l, const float3& r) noexcept
{
	return (l.x == r.x)
		&& (l.y == r.y)
		&& (l.z == r.z);
}

inline bool operator!=(const float3& l, const float3& r) noexcept
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

inline float3 operator+(const float3& v, float val) noexcept
{
	return float3(v.x + val, v.y + val, v.z + val);
}

inline float3 operator+(float val, const float3& v) noexcept
{
	return float3(v.x + val, v.y + val, v.z + val);
}

inline float3 operator+(const float3& l, const float3& r) noexcept
{
	return float3(l.x + r.x, l.y + r.y, l.z + r.z);
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

inline float3 operator-(const float3& v, float val) noexcept
{
	return float3(v.x - val, v.y - val, v.z - val);
}

inline float3 operator-(float val, const float3& v) noexcept
{
	return float3(val - v.x, val - v.y, val - v.z);
}

inline float3 operator-(const float3& l, const float3& r) noexcept
{
	return float3(l.x - r.x, l.y - r.y, l.z - r.z);
}

inline float3 operator-(const float3& v) noexcept
{
	return float3(-v.x, -v.y, -v.z);
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

inline float3 operator*(const float3& v, float val) noexcept
{
	return float3(v.x * val, v.y * val, v.z * val);
}

inline float3 operator*(float val, const float3& v) noexcept
{
	return float3(v.x * val, v.y * val, v.z * val);
}

inline float3 operator*(const float3& l, const float3& r) noexcept
{
	return float3(l.x * r.x, l.y * r.y, l.z * r.z);
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

inline float3 operator/(const float3& v, float val) noexcept
{
	assert(!approx_equal(val, 0.0f));

	return float3(v.x / val, v.y / val, v.z / val);
}

inline float3 operator/(float val, const float3& v) noexcept
{
	return float3(val / v.x, val / v.y, val / v.z);
}

inline float3 operator/(const float3& l, const float3& r) noexcept
{
	assert(!approx_equal(r.x, 0.0f));
	assert(!approx_equal(r.y, 0.0f));
	assert(!approx_equal(r.z, 0.0f));

	return float3(l.x / r.x, l.y / r.y, l.z / r.z);
}

std::ostream& operator<<(std::ostream& out, const float2& v);

std::wostream& operator<<(std::wostream& out, const float2& v);

std::ostream& operator<<(std::ostream& out, const float3& v);

std::wostream& operator<<(std::wostream& out, const float3& v);

//std::ostream& operator<<(std::ostream& out, const float4& v);
//
//std::wostream& operator<<(std::wostream& out, const float4& v);


// Returns true if the (abs(l - r) <= max_abs_diff) condition is true for every comopnent of l and r.
inline bool approx_equal(const float2& l, const float2& r, float max_abs_diff = 1e-5f) noexcept
{
	return approx_equal(l.x, r.x, max_abs_diff) && approx_equal(l.y, r.y, max_abs_diff);
}

// Returns true if the (abs(l - r) <= max_abs_diff) condition is true for every comopnent of l and r.
inline bool approx_equal(const float3& l, const float3& r, float max_abs_diff = 1e-5f) noexcept
{
	return approx_equal(l.x, r.x, max_abs_diff) 
		&& approx_equal(l.y, r.y, max_abs_diff)
		&& approx_equal(l.z, r.z, max_abs_diff);
}

// Returns the result of v.x / v.y.
inline float aspect_ratio(const float2& v) noexcept
{
	assert(!approx_equal(v.y, 0.0f));
	return v.x / v.y;
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

// Constrains vector v to lie between two further vectors.
// The function processes each component of the vector separately.
// Params:
//		v = The value to constrain
//		lo =	The lower end of the range into which to constrain v.
//		hi = The upper end of the range into which to constrain v.
inline float3 clamp(const float3& v, const float3& lo = float3::zero,
	const float3& hi = float3::unit_xyz)  noexcept
{
	return float3(
		clamp(v.x, lo.x, hi.x),
		clamp(v.y, lo.y, hi.y),
		clamp(v.z, lo.z, hi.z)
	);
}

// Calculates the cross product of of the given vectors.
inline float3 cross(const float3& l, const float3& r) noexcept
{
	return float3(
		(l.y * r.z) - (l.z * r.y),
		(l.z * r.x) - (l.x * r.z),
		(l.x * r.y) - (l.y * r.x)
	);
}

// Calculates the dot product of the given vectors.
inline float dot(const float2& l, const float2& r) noexcept
{
	return (l.x * r.x) + (l.y * r.y);
}

// Calculates the dot product of the given vectors.
inline float dot(const float3& l, const float3& r) noexcept
{
	return (l.x * r.x) + (l.y * r.y) + (l.z * r.z);
}

// Returns true if all the components of v are greater than val.
inline bool greater_than(const float2& v, float val) noexcept
{
	return (v.x > val) && (v.y > val);
}

// Returns true if all the components of v are greater than val.
inline bool greater_than(const float3& v, float val) noexcept
{
	return (v.x > val) && (v.y > val) && (v.z > val);
}

// Calculates the squared length of v.
inline float len_squared(const float2& v) noexcept
{
	return (v.x * v.x) + (v.y * v.y);
}

// Calculates the squared length of v.
inline float len_squared(const float3& v) noexcept
{
	return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

// Checks whether the specified vector is normalized.
inline bool is_normalized(const float2& v, float max_abs_diff = 1e-2f) noexcept
{
	return approx_equal(len_squared(v), 1.0f, max_abs_diff);
}

// Checks whether the specified vector is normalized.
inline bool is_normalized(const float3& v, float max_abs_diff = 1e-2f) noexcept
{
	return approx_equal(len_squared(v), 1.0f, max_abs_diff);
}

// Calculates the length of v.
inline float len(const float2& v) noexcept
{
	return std::sqrt(len_squared(v));
}

// Calculates the length of v.
inline float len(const float3& v) noexcept
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

// Linearly interpolates between two values.
// Params:
// -	l:		The start of the range in which to interpolate.
// -	r:		The end of the range in which to interpolate.
// -	factor:	The value to use to interpolate between lhs & rhs.
//				Factor has to lie within the range [0 .. 1].
inline float3 lerp(const float3& l, const float3& r, float factor) noexcept
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

// Returns new vector which is normalized(unit length) copy of the given one.
inline float3 normalize(const float3& v) noexcept
{
	float l2 = len_squared(v);
	if (approx_equal(l2, 0.0f) || approx_equal(l2, 1.0f)) return v;

	float factor = 1.0f / sqrt(l2);
	return v * factor;
}

// Returns rgb color volor
// (31 .. 24) bytes are ignored.
// red: (23 .. 16) bytes. 
// green: (15 .. 8) bytes. 
// blue: (7 .. 1) bytes.
inline float3 rgb(uint32_t val) noexcept
{
	return float3(
		((val >> 16) & 0xFF) / 255.f,
		((val >> 8) & 0xFF) / 255.f,
		(val & 0xFF) / 255.f
	);
}

} // namespace math

#endif // MATH_VECTOR_FLOAT_H_
