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

	explicit operator float2() const noexcept 
	{
		return float2(x, y);
	}


	float x;
	float y;
	float z;
};

struct float4 final {
	static const float4 unit_x;
	static const float4 unit_y;
	static const float4 unit_z;
	static const float4 unit_w;
	static const float4 unit_xyzw;
	static const float4 zero;


	float4() noexcept : x(0), y(0), z(0), w(0) {}

	explicit float4(float val) noexcept : x(val), y(val), z(val), w(val) {}

	explicit float4(const float3& v3, float w = 1.f) noexcept : x(v3.x), y(v3.y), z(v3.z), w(w) {}

	float4(float x, float y, float z, float w) noexcept : x(x), y(y), z(z), w(w) {}


	float4& operator+=(float val) noexcept
	{
		x += val;
		y += val;
		z += val;
		w += val;
		return *this;
	}

	float4& operator+=(const float4& v) noexcept
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	float4& operator-=(float val) noexcept
	{
		x -= val;
		y -= val;
		z -= val;
		w -= val;
		return *this;
	}

	float4& operator-=(const float4& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	float4& operator*=(float val) noexcept
	{
		x *= val;
		y *= val;
		z *= val;
		w *= val;
		return *this;
	}

	float4& operator/=(float val) noexcept
	{
		assert(!approx_equal(val, 0.0f));

		x /= val;
		y /= val;
		z /= val;
		w /= val;
		return *this;
	}

	explicit operator float2() const noexcept
	{
		return float2(x, y);
	}

	explicit operator float3() const noexcept
	{
		return float3(x, y, z);
	}


	float x;
	float y;
	float z;
	float w;
};

// In mathematics, the quaternions are a number system that extends the complex numbers.
// Quaternions extends a rotation in three dimensions to a rotation in four dimensions.
// This avoids "gimbal lock" and allows for smooth continuous rotation.
// q = xi + yj + zk + a1, where x, y, z, a are real numbers and i, j, k are imaginary units.
// For any quaternion 'a' is called scalar part and 'xi + yj + zk' is called its vector part.
struct quat final {
	static const quat i;
	static const quat j;
	static const quat k;
	static const quat identity;
	static const quat zero;


	quat() noexcept : x(0), y(0), z(0), a(0) {}

	quat(float x, float y, float z, float a) noexcept : x(x), y(y), z(z), a(a) {}

	quat(const float3& v, float a) noexcept : x(v.x), y(v.y), z(v.z), a(a) {}


	quat& operator+=(const quat& q) noexcept
	{
		x += q.x;
		y += q.y;
		z += q.z;
		a += q.a;
		return *this;
	}

	quat& operator-=(const quat& q) noexcept
	{
		x -= q.x;
		y -= q.y;
		z -= q.z;
		a -= q.a;
		return *this;
	}

	quat& operator*=(float val) noexcept
	{
		x *= val;
		y *= val;
		z *= val;
		a *= val;

		return *this;
	}

	// Calculates the Hamilton product of this and the specified quaterions.
	// Stores the result in this quaternion.
	quat& operator*=(const quat& q) noexcept
	{
		float xp = (a * q.x) + (x * q.a) + (y * q.z) - (z * q.y);
		float yp = (a * q.y) + (y * q.a) + (z * q.x) - (x * q.z);
		float zp = (a * q.z) + (z * q.a) + (x * q.y) - (y * q.x);
		float ap = (a * q.a) - (x * q.x) - (y * q.y) - (z * q.z);

		x = xp;
		y = yp;
		z = zp;
		a = ap;
		return *this;
	}

	quat& operator/=(float val) noexcept
	{
		assert(!approx_equal(val, 0.0f));

		x /= val;
		y /= val;
		z /= val;
		a /= val;
		return *this;
	}


	float x, y, z, a;
};

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

inline bool operator==(const float4& l, const float4& r) noexcept
{
	return (l.x == r.x)
		&& (l.y == r.y)
		&& (l.z == r.z)
		&& (l.w == r.w);
}

inline bool operator!=(const float4& l, const float4& r) noexcept
{
	return !(l == r);
}

inline bool operator==(const quat& l, const quat& r)
{
	return (l.x == r.x)
		&& (l.y == r.y)
		&& (l.z == r.z)
		&& (l.a == r.a);
}

inline bool operator!=(const quat& lhs, const quat& rhs)
{
	return !(lhs == rhs);
}

inline bool operator<(const float2& v, float val) noexcept
{
	return (v.x < val) && (v.y < val);
}

inline bool operator>(const float2& v, float val) noexcept
{
	return (v.x > val) && (v.y > val);
}

inline bool operator<=(const float2& v, float val) noexcept
{
	return (v.x <= val) && (v.y <= val);
}

inline bool operator>=(const float2& v, float val) noexcept
{
	return (v.x >= val) && (v.y >= val);
}

inline bool operator<(const float3& v, float val) noexcept
{
	return (v.x < val) && (v.y < val) && (v.z < val);
}

inline bool operator>(const float3& v, float val) noexcept
{
	return (v.x > val) && (v.y > val) && (v.z > val);
}

inline bool operator<=(const float3& v, float val) noexcept
{
	return (v.x <= val) && (v.y <= val) && (v.z <= val);
}

inline bool operator>=(const float3& v, float val) noexcept
{
	return (v.x >= val) && (v.y >= val) && (v.z >= val);
}

inline bool operator<(const float4& v, float val) noexcept
{
	return (v.x < val) && (v.y < val) && (v.z < val) && (v.w < val);
}

inline bool operator>(const float4& v, float val) noexcept
{
	return (v.x > val) && (v.y > val) && (v.z > val) && (v.w > val);
}

inline bool operator<=(const float4& v, float val) noexcept
{
	return (v.x <= val) && (v.y <= val) && (v.z <= val) && (v.w <= val);
}

inline bool operator>=(const float4& v, float val) noexcept
{
	return (v.x >= val) && (v.y >= val) && (v.z >= val) && (v.w >= val);
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

inline float4 operator+(const float4& v, float val) noexcept
{
	return float4(v.x + val, v.y + val, v.z + val, v.w + val);
}

inline float4 operator+(float val, const float4& v) noexcept
{
	return float4(v.x + val, v.y + val, v.z + val, v.w + val);
}

inline float4 operator+(const float4& l, const float4& r) noexcept
{
	return float4(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);
}

inline quat operator+(const quat& l, const quat& r) noexcept
{
	return quat(l.x + r.x, l.y + r.y, l.z + r.z, l.a + r.a);
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

inline float4 operator-(const float4& v, float val) noexcept
{
	return float4(v.x - val, v.y - val, v.z - val, v.w - val);
}

inline float4 operator-(float val, const float4& v) noexcept
{
	return float4(val - v.x, val - v.y, val - v.z, val - v.w);
}

inline float4 operator-(const float4& l, const float4& r) noexcept
{
	return float4(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w);
}

inline float4 operator-(const float4& v) noexcept
{
	return float4(-v.x, -v.y, -v.z, -v.w);
}

inline quat operator-(const quat& l, const quat& r) noexcept
{
	return quat(l.x - r.x, l.y - r.y, l.z - r.z, l.a - r.a);
}

inline quat operator-(const quat& q) noexcept
{
	return quat(-q.x, -q.y, -q.z, -q.a);
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

inline float4 operator*(const float4& v, float val) noexcept
{
	return float4(v.x * val, v.y * val, v.z * val, v.w * val);
}

inline float4 operator*(float val, const float4& v) noexcept
{
	return float4(v.x * val, v.y * val, v.z * val, v.w * val);
}

inline float4 operator*(const float4& l, const float4& r) noexcept
{
	return float4(l.x * r.x, l.y * r.y, l.z * r.z, l.w * r.w);
}

inline quat operator*(const quat& q, float val) noexcept
{
	return quat(q.x * val, q.y * val, q.z * val, q.a * val);
}

inline quat operator*(float val, const quat& q) noexcept
{
	return quat(q.x * val, q.y * val, q.z * val, q.a * val);
}

// Calculates the Hamilton product of lsh and rhs quaternions.
inline quat operator*(const quat& l, const quat& r) noexcept
{
	return quat(
		(l.a * r.x) + (l.x * r.a) + (l.y * r.z) - (l.z * r.y),
		(l.a * r.y) + (l.y * r.a) + (l.z * r.x) - (l.x * r.z),
		(l.a * r.z) + (l.z * r.a) + (l.x * r.y) - (l.y * r.x),
		(l.a * r.a) - (l.x * r.x) - (l.y * r.y) - (l.z * r.z)
	);
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
	assert(!approx_equal(v.x, 0.0f));
	assert(!approx_equal(v.y, 0.0f));
	assert(!approx_equal(v.z, 0.0f));

	return float3(val / v.x, val / v.y, val / v.z);
}

inline float3 operator/(const float3& l, const float3& r) noexcept
{
	assert(!approx_equal(r.x, 0.0f));
	assert(!approx_equal(r.y, 0.0f));
	assert(!approx_equal(r.z, 0.0f));

	return float3(l.x / r.x, l.y / r.y, l.z / r.z);
}

inline float4 operator/(const float4& v, float val) noexcept
{
	assert(!approx_equal(val, 0.0f));

	return float4(v.x / val, v.y / val, v.z / val, v.w / val);
}

inline float4 operator/(float val, const float4& v) noexcept
{
	assert(!approx_equal(v.x, 0.0f));
	assert(!approx_equal(v.y, 0.0f));
	assert(!approx_equal(v.z, 0.0f));
	assert(!approx_equal(v.w, 0.0f));

	return float4(val / v.x, val / v.y, val / v.z, val / v.w);
}

inline float4 operator/(const float4& l, const float4& r) noexcept
{
	assert(!approx_equal(r.x, 0.0f));
	assert(!approx_equal(r.y, 0.0f));
	assert(!approx_equal(r.z, 0.0f));
	assert(!approx_equal(r.w, 0.0f));

	return float4(l.x / r.x, l.y / r.y, l.z / r.z, l.w / r.w);
}

inline quat operator/(const quat& q, float val) noexcept
{
	assert(!approx_equal(val, 0.0f));

	return quat(q.x / val, q.y / val, q.z / val, q.a / val);
}

inline quat operator/(float val, const quat& q) noexcept
{
	assert(!approx_equal(q.x, 0.0f));
	assert(!approx_equal(q.y, 0.0f));
	assert(!approx_equal(q.z, 0.0f));
	assert(!approx_equal(q.a, 0.0f));

	return quat(val / q.x, val / q.y, val / q.z, val / q.a);
}

std::ostream& operator<<(std::ostream& out, const float2& v);

std::wostream& operator<<(std::wostream& out, const float2& v);

std::ostream& operator<<(std::ostream& out, const float3& v);

std::wostream& operator<<(std::wostream& out, const float3& v);

std::ostream& operator<<(std::ostream& out, const float4& v);

std::wostream& operator<<(std::wostream& out, const float4& v);

std::ostream& operator<<(std::ostream& out, const quat& q);

std::wostream& operator<<(std::wostream& out, const quat& q);


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

// Returns true if the (abs(l - r) <= max_abs_diff) condition is true for every comopnent of l and r.
inline bool approx_equal(const float4& l, const float4& r, float max_abs_diff = 1e-5f) noexcept
{
	return approx_equal(l.x, r.x, max_abs_diff)
		&& approx_equal(l.y, r.y, max_abs_diff)
		&& approx_equal(l.z, r.z, max_abs_diff)
		&& approx_equal(l.w, r.w, max_abs_diff);
}

// Returns true if the (abs(l - r) <= max_abs_diff) condition is true for every comopnent of l and r.
inline bool approx_equal(const quat& l, const quat& r, float max_abs_diff = 1e-5f) noexcept
{
	return approx_equal(l.x, r.x, max_abs_diff)
		&& approx_equal(l.y, r.y, max_abs_diff)
		&& approx_equal(l.z, r.z, max_abs_diff)
		&& approx_equal(l.a, r.a, max_abs_diff);
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

// Constrains vector v to lie between two further vectors.
// The function processes each component of the vector separately.
// Params:
//		v =		The value to constrain
//		lo =	The lower end of the range into which to constrain v.
//		hi =	The upper end of the range into which to constrain v.
inline float4 clamp(const float4& v, const float4& lo = float4::zero,
	const float4& hi = float4::unit_xyzw) noexcept
{
	return float4(
		clamp(v.x, lo.x, hi.x),
		clamp(v.y, lo.y, hi.y),
		clamp(v.z, lo.z, hi.z),
		clamp(v.w, lo.w, hi.w)
	);
}

// Gets the conjugation result of the given quaternion.
inline quat conjugate(const quat& q) noexcept
{
	return quat(-q.x, -q.y, -q.z, q.a);
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

// Calculates the dot product of the given vectors.
inline float dot(const float4& l, const float4& r) noexcept
{
	return (l.x * r.x) + (l.y * r.y) + (l.z * r.z) + (l.w * r.w);
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

// Calculates the squared length of v.
inline float len_squared(const float4& v) noexcept
{
	return (v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w);
}

// Calculates the squared length of q.
inline float len_squared(const quat& q) noexcept
{
	return (q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.a * q.a);
}

// Computes the inverse(reciprocal) of the given quaternion. q* / (|q|^2)
inline quat inverse(const quat& q) noexcept
{
	const float l2 = len_squared(q);
	assert(!approx_equal(l2, 0.0f)); // A quaternion with len = 0 isn't invertible.

	const float scalar = 1.0f / l2;
	return conjugate(q) * scalar;
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

// Checks whether the specified vector is normalized.
inline bool is_normalized(const float4& v, float max_abs_diff = 1e-2f) noexcept
{
	return approx_equal(len_squared(v), 1.0f, max_abs_diff);
}

// Checks whether the specified quaternion is normalized.
inline bool is_normalized(const quat& q, float max_abs_diff = 1e-2f) noexcept
{
	return approx_equal(len_squared(q), 1.0f, max_abs_diff);
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

// Calculates the length of v.
inline float len(const float4& v) noexcept
{
	return std::sqrt(len_squared(v));
}

// Calculates the length of q.
inline float len(const quat& q) noexcept
{
	return std::sqrt(len_squared(q));
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

// Linearly interpolates between two values.
// Params:
// -	l:		The start of the range in which to interpolate.
// -	r:		The end of the range in which to interpolate.
// -	factor:	The value to use to interpolate between lhs & rhs.
//				Factor has to lie within the range [0 .. 1].
inline float4 lerp(const float4& l, const float4& r, float factor) noexcept
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

// Returns new vector which is normalized(unit length) copy of the given one.
inline float4 normalize(const float4& v) noexcept
{
	float l2 = len_squared(v);
	if (approx_equal(l2, 0.0f) || approx_equal(l2, 1.0f)) return v;

	float factor = 1.0f / sqrt(l2);
	return v * factor;
}

// Returns a new quaternion which is normalized(unit length) copy of the given quaternion.
inline quat normalize(const quat& q) noexcept
{
	const float l2 = len_squared(q);
	if (approx_equal(l2, 0.0f) || approx_equal(l2, 1.0f)) return q;

	const float factor = 1.0f / sqrt(l2);
	return q * factor;
}

// Applies std::round to each component of the specified vector.
inline float4 round(const float4& v) noexcept
{
	return float4(std::round(v.x), std::round(v.y), std::round(v.z), std::round(v.w));
}

// Performs spherical-interpolation between unit quaternions (geometrical slerp).
quat slerp(const quat& q, const quat& r, float factor);


} // namespace math

#endif // MATH_VECTOR_FLOAT_H_
