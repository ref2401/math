#include "math/transform.h"


namespace math {

quat from_axis_angle_rotation(const float3& axis, float angle) noexcept
{
	assert(is_normalized(axis));

	if (approx_equal(angle, 0.0f)) return quat::identity; // no angle - no rotation

	const float half_angle = angle * 0.5f;
	const float c = std::cos(half_angle);
	const float s = std::sin(half_angle);
	return quat(axis.x * s, axis.y * s, axis.z * s, c);
}

template<typename M>
quat from_rotation_matrix(const M& m) noexcept
{
	static_assert(is_matrix<M>::value, "M must be a matrix.");

	if (m == M::zero) return quat::zero;
	assert(is_orthogonal(m));

	// NOTE(ref2401): see Ken Shoemake: Quaternions.
	quat res;
	const float u = m.m00 + m.m11 + m.m22;

	if (u >= 0.f) {
		float s = std::sqrt(u + 1.f);
		res.a = 0.5f * s;

		s = 0.5f / s;
		res.x = (m.m21 - m.m12) * s;
		res.y = (m.m02 - m.m20) * s;
		res.z = (m.m10 - m.m01) * s;
	}
	else if (m.m00 > m.m11 && m.m00 > m.m22) {
		float s = sqrt(m.m00 - m.m11 - m.m22 + 1.f);
		res.x = 0.5f * s;

		s = 0.5f / s;
		res.y = (m.m10 + m.m01) * s;
		res.z = (m.m02 + m.m20) * s;
		res.a = (m.m21 - m.m12) * s;
	}
	else if (m.m11 > m.m22) {
		float s = sqrt(m.m11 - m.m00 - m.m22 + 1.f);
		res.y = 0.5f * s;

		s = 0.5f / s;
		res.x = (m.m10 + m.m01) * s;
		res.z = (m.m21 + m.m12) * s;
		res.a = (m.m02 - m.m20) * s;
	}
	else {
		float s = std::sqrt(m.m22 - m.m00 - m.m11 + 1.f);
		res.z = 0.5f * s;

		s = 0.5f / s;
		res.a = (m.m10 - m.m01) * s;
		res.x = (m.m02 + m.m20) * s;
		res.y = (m.m21 + m.m12) * s;
	}

	return res;
}

template quat from_rotation_matrix(const float3x3& m) noexcept;
template quat from_rotation_matrix(const float4x4& m) noexcept;

float4x4 orthographic_matrix_directx(float width, float height, float near_z, float far_z) noexcept
{
	assert(width > 0);
	assert(height > 0);
	assert(near_z < far_z);

	const float far_minus_near = far_z - near_z;
	const float right = width * 0.5f;
	const float top = height * 0.5f;

	return float4x4(
		1.0f / right, 0, 0, 0,
		0, 1.0f / top, 0, 0,
		0, 0, -1.0f / far_minus_near, -near_z / far_minus_near,
		0, 0, 0, 1
	);
}

float4x4 orthographic_matrix_directx(float left, float right, float bottom, float top, float near_z, float far_z) noexcept
{
	assert(left < right);
	assert(bottom < top);
	assert(near_z < far_z);

	const float far_minus_near = far_z - near_z;
	const float right_minus_left = right - left;
	const float top_minus_bottom = top - bottom;

	return float4x4(
		2.0f / right_minus_left, 0, 0, -(right + left) / right_minus_left,
		0, 2.0f / top_minus_bottom, 0, -(top + bottom) / top_minus_bottom,
		0, 0, -1.0f / far_minus_near, -near_z / far_minus_near,
		0, 0, 0, 1
	);
}

float4x4 orthographic_matrix_opengl(float width, float height, float near_z, float far_z) noexcept
{
	assert(width > 0);
	assert(height > 0);
	assert(near_z < far_z);

	const float far_minus_near = far_z - near_z;
	const float right = width * 0.5f;
	const float top = height * 0.5f;

	return float4x4(
		1.0f / right, 0, 0, 0,
		0, 1.0f / top, 0, 0,
		0, 0, -2.0f / far_minus_near, -(far_z + near_z) / far_minus_near,
		0, 0, 0, 1
	);
}

float4x4 orthographic_matrix_opengl(float left, float right, float bottom, float top, float near_z, float far_z) noexcept
{
	assert(left < right);
	assert(bottom < top);
	assert(near_z < far_z);

	const float far_minus_near = far_z - near_z;
	const float right_minus_left = right - left;
	const float top_minus_bottom = top - bottom;

	return float4x4(
		2.0f / right_minus_left, 0, 0, -(right + left) / right_minus_left,
		0, 2.0f / top_minus_bottom, 0, -(top + bottom) / top_minus_bottom,
		0, 0, -2.0f / far_minus_near, -(far_z + near_z) / far_minus_near,
		0, 0, 0, 1
	);
}

float4x4 perspective_matrix_directx(float left, float right, float bottom, float top, float near_z, float far_z) noexcept
{
	const float doubled_near = 2.0f * near_z;
	const float far_minus_near = far_z - near_z;
	const float right_minus_left = right - left;
	const float top_minus_bottom = top - bottom;


	return float4x4(
		doubled_near / right_minus_left, 0, (right + left) / right_minus_left, 0,
		0, doubled_near / top_minus_bottom, (top + bottom) / top_minus_bottom, 0,
		0, 0, -far_z / far_minus_near, -near_z * far_z / far_minus_near,
		0, 0, -1, 0
	);
}

float4x4 perspective_matrix_directx(float vert_fov, float wh_ratio, float near_z, float far_z) noexcept
{
	assert(0 < vert_fov && vert_fov < pi);
	assert(0 < near_z && near_z < far_z);

	const float fat_minus_near = far_z - near_z;
	const float rev_tangent = 1.0f / std::tan(vert_fov * 0.5f);

	return float4x4(
		(1.0f / wh_ratio) * rev_tangent, 0, 0, 0,
		0, rev_tangent, 0, 0,
		0, 0, -far_z / fat_minus_near, -near_z * far_z / fat_minus_near,
		0, 0, -1, 0
	);
}

float4x4 perspective_matrix_opengl(float left, float right, float bottom, float top, float near_z, float far_z) noexcept
{
	const float doubled_near = 2.0f * near_z;
	const float far_minus_near = far_z - near_z;
	const float right_minus_left = right - left;
	const float top_minus_bottom = top - bottom;


	return float4x4(
		doubled_near / right_minus_left, 0, (right + left) / right_minus_left, 0,
		0, doubled_near / top_minus_bottom, (top + bottom) / top_minus_bottom, 0,
		0, 0, -(far_z + near_z) / far_minus_near, -doubled_near * far_z / far_minus_near,
		0, 0, -1, 0
	);
}

float4x4 perspective_matrix_opengl(float vert_fov, float wh_ratio, float near_z, float far_z) noexcept
{
	assert(0 < vert_fov && vert_fov < pi);
	assert(0 < near_z && near_z < far_z);

	const float fat_minus_near = far_z - near_z;
	const float rev_tangent = 1.0f / std::tan(vert_fov * 0.5f);

	/*
	* TAN = tan(vert_fov / 2.0f)
	* top = near * TAN
	* right = top * wh_ratio = wh_ratio * near * TAN
	*
	* 2near / (right - (-rigth)) = 2near / 2right = near / right =
	* near / (wh_ratio * near * TAN) = 1 / (wh_ratio * TAN)
	*
	* 2near / (top - (-top)) = 2near / 2top = neat / top =
	* near / (near * TAN) = 1 / TAN */

	return float4x4(
		(1.0f / wh_ratio) * rev_tangent, 0, 0, 0,
		0, rev_tangent, 0, 0,
		0, 0, -(far_z + near_z) / fat_minus_near, -2.0f * near_z * far_z / fat_minus_near,
		0, 0, -1, 0
	);
}

template<typename M>
M rotation_matrix(const quat& q) noexcept
{
	static_assert(is_matrix<M>::value, "M must be a matrix.");

	const float l = len(q);
	if (approx_equal(l, 0.0f)) return M::zero;

	const float s = 2.0f / l;
	const float xx = q.x * q.x;
	const float yy = q.y * q.y;
	const float zz = q.z * q.z;
	const float ax = q.a * q.x;
	const float ay = q.a * q.y;
	const float az = q.a * q.z;
	const float xy = q.x * q.y;
	const float xz = q.x * q.z;
	const float yz = q.y * q.z;

	M rot = M::identity;
	rot.m00 = 1.0f - s * (yy + zz);
	rot.m01 = s * (xy - az);
	rot.m02 = s * (xz + ay);

	rot.m10 = s * (xy + az);
	rot.m11 = 1.0f - s * (xx + zz);
	rot.m12 = s * (yz - ax);

	rot.m20 = s * (xz - ay);
	rot.m21 = s * (yz + ax);
	rot.m22 = 1.0f - s * (xx + yy);

	return rot;
}

template float3x3 rotation_matrix(const quat& q) noexcept;
template float4x4 rotation_matrix(const quat& q) noexcept;

template<typename M>
M rotation_matrix(const float3& axis, float angle) noexcept
{
	static_assert(is_matrix<M>::value, "M must be a matrix.");
	assert(is_normalized(axis));

	const float cos_a = std::cos(angle);
	const float sin_a = std::sin(angle);
	const float one_minus_cos_a = (1.f - cos_a);
	const float xx = axis.x * axis.x;
	const float xy = axis.x * axis.y;
	const float xz = axis.x * axis.z;
	const float yy = axis.y * axis.y;
	const float yz = axis.y * axis.z;
	const float zz = axis.z * axis.z;

	M rot = M::identity;
	rot.m00 = cos_a + one_minus_cos_a * xx;
	rot.m01 = one_minus_cos_a * xy - axis.z * sin_a;
	rot.m02 = one_minus_cos_a * xz + axis.y * sin_a;

	rot.m10 = one_minus_cos_a * xy + axis.z * sin_a;
	rot.m11 = cos_a + one_minus_cos_a * yy;
	rot.m12 = one_minus_cos_a * yz - axis.x * sin_a;

	rot.m20 = one_minus_cos_a * xz - axis.y * sin_a;
	rot.m21 = one_minus_cos_a * yz + axis.x * sin_a;
	rot.m22 = cos_a + one_minus_cos_a * zz;

	return rot;
}

template float3x3 rotation_matrix(const float3& axis, float angle) noexcept;
template float4x4 rotation_matrix(const float3& axis, float angle) noexcept;

template<typename M>
M rotation_matrix(const float3& position, const float3& target, const float3& up) noexcept
{
	static_assert(is_matrix<M>::value, "M must be a matrix.");
	assert(position != target);
	assert(is_normalized(up));

	const float3 forward = normalize(target - position);
	const float3 right = normalize(cross(up, forward));
	const float3 new_up = normalize(cross(forward, right));

	M r = M::identity;
	set_ox(r, right);
	set_oy(r, new_up);
	set_oz(r, forward);

	return r;
}
template float3x3 rotation_matrix(const float3& position, const float3& target, const float3& up) noexcept;
template float4x4 rotation_matrix(const float3& position, const float3& target, const float3& up) noexcept;

template<typename M>
M rotation_matrix_ox(float angle) noexcept
{
	static_assert(is_matrix<M>::value, "M must be a matrix.");

	if (approx_equal(angle, 0.0f)) return M::identity;

	const float cos_a = std::cos(angle);
	const float sin_a = std::sin(angle);

	M r = M::identity;
	r.m11 = cos_a;
	r.m21 = sin_a;
	r.m12 = -sin_a;
	r.m22 = cos_a;

	return r;
}

template float3x3 rotation_matrix_ox(float angle) noexcept;
template float4x4 rotation_matrix_ox(float angle) noexcept;

template<typename M>
M rotation_matrix_oy(float angle) noexcept
{
	static_assert(is_matrix<M>::value, "M must be a matrix");

	if (approx_equal(angle, 0.0f)) return M::identity;

	const float cos_a = std::cos(angle);
	const float sin_a = std::sin(angle);

	M r = M::identity;
	r.m00 = cos_a;
	r.m20 = -sin_a;
	r.m02 = sin_a;
	r.m22 = cos_a;

	return r;
}

template float3x3 rotation_matrix_oy(float angle) noexcept;
template float4x4 rotation_matrix_oy(float angle) noexcept;

template<typename M>
M rotation_matrix_oz(float angle) noexcept
{
	static_assert(is_matrix<M>::value, "TRetMat must be a matrix.");

	if (approx_equal(angle, 0.0f)) return M::identity;

	const float cos_a = std::cos(angle);
	const float sin_a = std::sin(angle);

	M r = M::identity;
	r.m00 = cos_a;
	r.m10 = sin_a;
	r.m01 = -sin_a;
	r.m11 = cos_a;

	return r;
}

template float3x3 rotation_matrix_oz(float angle) noexcept;
template float4x4 rotation_matrix_oz(float angle) noexcept;

template<typename M>
M scale_matrix(const float3& s) noexcept
{
	static_assert(is_matrix<M>::value, "M must be a matrix.");
	assert(s > 0);

	M m = M::identity;
	m.m00 = s.x;
	m.m11 = s.y;
	m.m22 = s.z;
	return m;
}

template float3x3 scale_matrix(const float3& s) noexcept;
template float4x4 scale_matrix(const float3& s) noexcept;

float4x4 view_matrix(const float3& position, const float3& target, const float3& up) noexcept
{
	assert(position != target);
	assert(is_normalized(up));

	const float3 forward = normalize(target - position);
	const float3 right = normalize(cross(forward, up));
	const float3 new_up = normalize(cross(right, forward));

	float4x4 r = float4x4::identity;
	r.m00 = right.x;	r.m01 = right.y;	r.m02 = right.z;	r.m03 = dot(right, -position);
	r.m10 = new_up.x;	r.m11 = new_up.y;	r.m12 = new_up.z;	r.m13 = dot(new_up, -position);
	r.m20 = -forward.x;	r.m21 = -forward.y;	r.m22 = -forward.z;	r.m23 = dot(forward, position);

	return r;
}


} // namespace math
