#ifndef MATH_TRANSFORM_H_
#define MATH_TRANSFORM_H_

#include "math/matrix.h"


namespace math {

// Returns ox vectoc of a 3D space basis.
inline float3 ox(const float3x3& m) noexcept
{
	return float3(m.m00, m.m10, m.m20);
}

// ditto
inline float3 ox(const float4x4& m) noexcept
{
	return float3(m.m00, m.m10, m.m20);
}

// Sets the ox vector of a 3D space basis.
inline void set_ox(float3x3& m, const float3& v) noexcept
{
	m.m00 = v.x;
	m.m10 = v.y;
	m.m20 = v.z;
}

// ditto
inline void set_ox(float4x4& m, const float3& v) noexcept
{
	m.m00 = v.x;
	m.m10 = v.y;
	m.m20 = v.z;
}

// Returns oy vectoc of a 3D space basis.
inline float3 oy(const float3x3& m) noexcept
{
	return float3(m.m01, m.m11, m.m21);
}

// ditto
inline float3 oy(const float4x4& m) noexcept
{
	return float3(m.m01, m.m11, m.m21);
}

// Sets the oy vector of a 3D space basis.
inline void set_oy(float3x3& m, const float3& v) noexcept
{
	m.m01 = v.x;
	m.m11 = v.y;
	m.m21 = v.z;
}

// ditto
inline void set_oy(float4x4& m, const float3& v) noexcept
{
	m.m01 = v.x;
	m.m11 = v.y;
	m.m21 = v.z;
}

// Returns oz vectoc of a 3D space basis.
inline float3 oz(const float3x3& m) noexcept
{
	return float3(m.m02, m.m12, m.m22);
}

// ditto
inline float3 oz(const float4x4& m) noexcept
{
	return float3(m.m02, m.m12, m.m22);
}

// Sets the oz vector of a 3D space basis.
inline void set_oz(float3x3&m, const float3& v) noexcept
{
	m.m02 = v.x;
	m.m12 = v.y;
	m.m22 = v.z;
}

// ditto
inline void set_oz(float4x4&m, const float3& v) noexcept
{
	m.m02 = v.x;
	m.m12 = v.y;
	m.m22 = v.z;
}

} // namespace math

#endif // MATH_TRANSFORM_H_
