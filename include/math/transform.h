#ifndef MATH_TRANSFORM_H_
#define MATH_TRANSFORM_H_

#include "math/math_traits.h"
#include "math/matrix.h"


namespace math {

// Create a quaternion from the axis-angle respresentation.
//	Params:
//		axis:	a unit vector indicates direction of a rotation axis.
//		angle:	(In radians) describes the magnitude of the rotation about the axis.
quat from_axis_angle_rotation(const float3& axis, float angle) noexcept;

// Construct a unit quaternion from the specified rotation matrix.
// In the case of M is mat4 translation and perspective components are ignored.
template<typename M>
quat from_rotation_matrix(const M& m) noexcept;

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

// Creates a right-handed DirectX compatible orthographic projection matrix.
// right = -left, top = -bottom, near < far.
float4x4 orthographic_matrix_directx(float width, float height, float near_z, float far_z) noexcept;

// Creates a right-handed, off screen scenter DirectX compatible orthographic projection matrix.
// left < right, bottom < top, near < far.
float4x4 orthographic_matrix_directx(float left, float right, float bottom, float top, float near_z, float far_z) noexcept;

// Creates a right-handed OpenGL compatible orthographic projection matrix. 
// right = -left, top = -bottom, near < far.
float4x4 orthographic_matrix_opengl(float width, float height, float near_z, float far_z) noexcept;

// Creates a right-handed, off screen scenter OpenGL compatible orthographic projection matrix.
// left < right, bottom < top, near < far.
float4x4 orthographic_matrix_opengl(float left, float right, float bottom, float top, float near_z, float far_z) noexcept;

// Computes a right-handed, off screen scenter DirectX compatible projection matrix for general frustum.
// left < right, bottom < top, 0 < near < far.
float4x4 perspective_matrix_directx(float left, float right, float bottom, float top, float near_z, float far_z) noexcept;

// Computes a right-handed DirectX compatible symmetric perspective projection matrix based on a field of view.
// 0 < vert_Fov < cg::pi, 0 < near < far.
//	Params:
//		vert_fov = Vertical field of view in radians.
//		wh_ratio = The ratio of the width to the height of the near clipping plane.
//		near = the distance between a viewer and the near clipping plane.
//		far = the distance between a viewer and the far clipping plane.
float4x4 perspective_matrix_directx(float vert_fov, float wh_ratio, float near_z, float far_z) noexcept;

// Computes a right-handed, off screen scenter OpenGL compatible projection matrix for general frustum.
// left < right, bottom < top, 0 < near < far.
float4x4 perspective_matrix_opengl(float left, float right, float bottom, float top, float near_z, float far_z) noexcept;

// Computes a right-handed OpenGL compatible symmetric perspective projection matrix based on a field of view.
// 0 < vert_Fov < cg::pi, 0 < near < far.
//	Params:
//		vert_fov = Vertical field of view in radians.
//		wh_ratio = The ratio of the width to the height of the near clipping plane.
//		near = the distance between a viewer and the near clipping plane.
//		far = the distance between a viewer and the far clipping plane.
float4x4 perspective_matrix_opengl(float vert_fov, float wh_ratio, float near_z, float far_z) noexcept;

// Returns the position component of the specified matrix.
inline float3 position(const float4x4& m) noexcept
{
	return float3(m.m03, m.m13, m.m23);
}

// Sets the position component of the specifiend matrix.
inline void set_position(float4x4& m, const float3& p) noexcept
{
	m.m03 = p.x;
	m.m13 = p.y;
	m.m23 = p.z;
}

// Rotate position p by a quaternion q.
// Usually rotation q is specified as a rotation around an arbitrary axis by some angle.
inline float3 rotate(const quat& q, const float3& p) noexcept
{
	assert(is_normalized(q));

	const quat pq = quat(p.x, p.y, p.z, 1.0f);
	const quat res = q * pq * conjugate(q);
	return float3(res.x, res.y, res.z);
}

// Constructs rotation matrix from (possibly non-unit) quaternion.
template<typename M>
M rotation_matrix(const quat& q) noexcept;

// Composes a rotatiom matrix that rotates a vector by angle about an arbitrary axis.
// The rotation is conter-clockwise.
//	Params:
//		axis:	 a unit vector indicates the direction of a rotation axis.
//		angle:	 (In radians) describes the magnitude in radians of the rotation about the axis.
template<typename M>
M rotation_matrix(const float3& axis, float angle) noexcept;

// Composes a look at rotation matrix. Translation component is not set.
// Use tr_matrix to consturct a look at rotation and translation to position chain.
//	Params:
//		position:	is eye/object position.
//		target:		point of interest.v The point we want to look at.
//		up:			the direction that is considered to be upward.
template<typename M>
M rotation_matrix(const float3& position, const float3& target, const float3& up = float3::unit_y) noexcept;

// Composes a rotatiom matrix about ox axis.
//	Params:
//		angle:	describes the magnitude in radians of the rotation about ox.
template<typename M>
M rotation_matrix_ox(float angle) noexcept;

// Composes a rotatiom matrix about oy axis.
//	Params:
//		angle:	describes the magnitude in radians of the rotation about oy.
template<typename M>
M rotation_matrix_oy(float angle) noexcept;

// Composes a rotatiom matrix about oz axis.
//	Params:
//		angle:	describes the magnitude in radians of the rotation about oz.
template<typename M>
M rotation_matrix_oz(float angle) noexcept;

// Returns a matrix which can be used to scale vectors s.
template<typename M>
M scale_matrix(const float3& s) noexcept;

// Returns a matrix that is a concatenation of translation by p and rotation by q.
// The result is equal to translation_matrix(p) * rotation_matrix(q).
inline float4x4 tr_matrix(const float3& p, const quat& q) noexcept
{
	float4x4 m = rotation_matrix<float4x4>(q);
	set_position(m, p);
	return m;
}

// Returns a matrix that is a concatentation of traslation by p and a look at rotation.
inline float4x4 tr_matrix(const float3& position, const float3& target, const float3& up = float3::unit_y) noexcept
{
	float4x4 m = rotation_matrix<float4x4>(position, target, up);
	set_position(m, position);
	return m;
}

// Returns a matrix which can be used to translate vectors to the position p.
inline float4x4 translation_matrix(const float3& p) noexcept
{
	float4x4 m = float4x4::identity;
	set_position(m, p);
	return m;
}

// Return a matrix that is a concatenation of translation by p, rotation by q and scale by s.
// The result is equal to translation_matrix(p) * rotation_matrix(q) * scale_matrix(s).
inline float4x4 trs_matrix(const float3& p, const quat& q, const float3& s) noexcept
{
	return tr_matrix(p, q) * scale_matrix<float4x4>(s);
}

// Returns a matrix that is a concatentation of traslation by p and scale by s.
inline float4x4 ts_matrix(const float3& p, const float3& s) noexcept
{
	float4x4 m = scale_matrix<float4x4>(s);
	set_position(m, p);
	return m;
}

// Composes a matrix that cam be used to transform from world space to view space.
//	Params:
//		position:	an origin, where eye(camera) is situated.
//		target:		a point of interest.
//		up:			the direction that is considered to be upward.
float4x4 view_matrix(const float3& position, const float3& target, const float3& up = float3::unit_y) noexcept;



} // namespace math

#endif // MATH_TRANSFORM_H_
