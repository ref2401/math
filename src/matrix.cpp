#include "math/matrix.h"


namespace math {

const float4x4 float4x4::identity(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
const float4x4 float4x4::zero;


// ----- mat4 -----

float4x4& float4x4::operator*=(const float4x4& m) noexcept
{
	float mp00, mp01, mp02, mp03;
	float mp10, mp11, mp12, mp13;
	float mp20, mp21, mp22, mp23;
	float mp30, mp31, mp32, mp33;

	mp00 = m00 * m.m00 + m01 * m.m10 + m02 * m.m20 + m03 * m.m30;
	mp01 = m00 * m.m01 + m01 * m.m11 + m02 * m.m21 + m03 * m.m31;
	mp02 = m00 * m.m02 + m01 * m.m12 + m02 * m.m22 + m03 * m.m32;
	mp03 = m00 * m.m03 + m01 * m.m13 + m02 * m.m23 + m03 * m.m33;

	mp10 = m10 * m.m00 + m11 * m.m10 + m12 * m.m20 + m13 * m.m30;
	mp11 = m10 * m.m01 + m11 * m.m11 + m12 * m.m21 + m13 * m.m31;
	mp12 = m10 * m.m02 + m11 * m.m12 + m12 * m.m22 + m13 * m.m32;
	mp13 = m10 * m.m03 + m11 * m.m13 + m12 * m.m23 + m13 * m.m33;

	mp20 = m20 * m.m00 + m21 * m.m10 + m22 * m.m20 + m23 * m.m30;
	mp21 = m20 * m.m01 + m21 * m.m11 + m22 * m.m21 + m23 * m.m31;
	mp22 = m20 * m.m02 + m21 * m.m12 + m22 * m.m22 + m23 * m.m32;
	mp23 = m20 * m.m03 + m21 * m.m13 + m22 * m.m23 + m23 * m.m33;

	mp30 = m30 * m.m00 + m31 * m.m10 + m32 * m.m20 + m33 * m.m30;
	mp31 = m30 * m.m01 + m31 * m.m11 + m32 * m.m21 + m33 * m.m31;
	mp32 = m30 * m.m02 + m31 * m.m12 + m32 * m.m22 + m33 * m.m32;
	mp33 = m30 * m.m03 + m31 * m.m13 + m32 * m.m23 + m33 * m.m33;

	m00 = mp00; m01 = mp01; m02 = mp02; m03 = mp03;
	m10 = mp10; m11 = mp11; m12 = mp12; m13 = mp13;
	m20 = mp20; m21 = mp21; m22 = mp22; m23 = mp23;
	m30 = mp30; m31 = mp31; m32 = mp32; m33 = mp33;

	return *this;
}

// ----- funcs -----

bool operator==(const float4x4& l, const float4x4& r) noexcept
{
	return approx_equal(l.m00, r.m00)
		&& approx_equal(l.m10, r.m10)
		&& approx_equal(l.m20, r.m20)
		&& approx_equal(l.m30, r.m30)

		&& approx_equal(l.m01, r.m01)
		&& approx_equal(l.m11, r.m11)
		&& approx_equal(l.m21, r.m21)
		&& approx_equal(l.m31, r.m31)

		&& approx_equal(l.m02, r.m02)
		&& approx_equal(l.m12, r.m12)
		&& approx_equal(l.m22, r.m22)
		&& approx_equal(l.m32, r.m32)

		&& approx_equal(l.m03, r.m03)
		&& approx_equal(l.m13, r.m13)
		&& approx_equal(l.m23, r.m23)
		&& approx_equal(l.m33, r.m33);
}

float4x4 operator*(const float4x4& l, const float4x4& r) noexcept
{
	float4x4 product = float4x4::zero;

	product.m00 = l.m00 * r.m00 + l.m01 * r.m10 + l.m02 * r.m20 + l.m03 * r.m30;
	product.m01 = l.m00 * r.m01 + l.m01 * r.m11 + l.m02 * r.m21 + l.m03 * r.m31;
	product.m02 = l.m00 * r.m02 + l.m01 * r.m12 + l.m02 * r.m22 + l.m03 * r.m32;
	product.m03 = l.m00 * r.m03 + l.m01 * r.m13 + l.m02 * r.m23 + l.m03 * r.m33;
	product.m10 = l.m10 * r.m00 + l.m11 * r.m10 + l.m12 * r.m20 + l.m13 * r.m30;
	product.m11 = l.m10 * r.m01 + l.m11 * r.m11 + l.m12 * r.m21 + l.m13 * r.m31;
	product.m12 = l.m10 * r.m02 + l.m11 * r.m12 + l.m12 * r.m22 + l.m13 * r.m32;
	product.m13 = l.m10 * r.m03 + l.m11 * r.m13 + l.m12 * r.m23 + l.m13 * r.m33;
	product.m20 = l.m20 * r.m00 + l.m21 * r.m10 + l.m22 * r.m20 + l.m23 * r.m30;
	product.m21 = l.m20 * r.m01 + l.m21 * r.m11 + l.m22 * r.m21 + l.m23 * r.m31;
	product.m22 = l.m20 * r.m02 + l.m21 * r.m12 + l.m22 * r.m22 + l.m23 * r.m32;
	product.m23 = l.m20 * r.m03 + l.m21 * r.m13 + l.m22 * r.m23 + l.m23 * r.m33;
	product.m30 = l.m30 * r.m00 + l.m31 * r.m10 + l.m32 * r.m20 + l.m33 * r.m30;
	product.m31 = l.m30 * r.m01 + l.m31 * r.m11 + l.m32 * r.m21 + l.m33 * r.m31;
	product.m32 = l.m30 * r.m02 + l.m31 * r.m12 + l.m32 * r.m22 + l.m33 * r.m32;
	product.m33 = l.m30 * r.m03 + l.m31 * r.m13 + l.m32 * r.m23 + l.m33 * r.m33;

	return product;
}

std::ostream& operator<<(std::ostream& out, const float4x4& m)
{
	out << "float4x4("
		<< m.m00 << ", " << m.m01 << ", " << m.m02 << ", " << m.m03 << ",  "
		<< m.m10 << ", " << m.m11 << ", " << m.m12 << ", " << m.m13 << ",  "
		<< m.m20 << ", " << m.m21 << ", " << m.m22 << ", " << m.m23 << ",  "
		<< m.m30 << ", " << m.m31 << ", " << m.m32 << ", " << m.m33 << ")";

	return out;
}

std::wostream& operator<<(std::wostream& out, const float4x4& m)
{
	out << "float4x4("
		<< m.m00 << ", " << m.m01 << ", " << m.m02 << ", " << m.m03 << ",  "
		<< m.m10 << ", " << m.m11 << ", " << m.m12 << ", " << m.m13 << ",  "
		<< m.m20 << ", " << m.m21 << ", " << m.m22 << ", " << m.m23 << ",  "
		<< m.m30 << ", " << m.m31 << ", " << m.m32 << ", " << m.m33 << ")";

	return out;
}

float det(const float4x4& m) noexcept
{
	// find all the required first minors of m.
	const float minor00 = m.m11*m.m22*m.m33 + m.m12*m.m23*m.m31 + m.m13*m.m21*m.m32
		- m.m13*m.m22*m.m31 - m.m12*m.m21*m.m33 - m.m11*m.m23*m.m32;
	const float minor01 = m.m10*m.m22*m.m33 + m.m12*m.m23*m.m30 + m.m13*m.m20*m.m32
		- m.m13*m.m22*m.m30 - m.m12*m.m20*m.m33 - m.m10*m.m23*m.m32;
	const float minor02 = m.m10*m.m21*m.m33 + m.m11*m.m23*m.m30 + m.m13*m.m20*m.m31
		- m.m13*m.m21*m.m30 - m.m11*m.m20*m.m33 - m.m10*m.m23*m.m31;
	const float minor03 = m.m10*m.m21*m.m32 + m.m11*m.m22*m.m30 + m.m12*m.m20*m.m31
		- m.m12*m.m21*m.m30 - m.m11*m.m20*m.m32 - m.m10*m.m22*m.m31;

	return m.m00 * minor00 - m.m01 * minor01 + m.m02 * minor02 - m.m03 * minor03;
}

float4x4 inverse(const float4x4& m) noexcept
{
	// inverse is found by Cramer’s rule.

	// Check whether m is a singular matix
	const float d = det(m);
	assert(!approx_equal(d, 0.0f));


	// construct the adjugate matrix.
	// cofactor00 cofactor10 cofactor20 cofactor30
	// cofactor01 cofactor11 cofactor21 cofactor31
	// cofactor02 cofactor12 cofactor22 cofactor32
	// cofactor03 cofactor13 cofactor23 cofactor33
	float4x4 adj;
	adj.m00 = m.m11*m.m22*m.m33 + m.m12*m.m23*m.m31 + m.m13*m.m21*m.m32 - m.m13*m.m22*m.m31 - m.m12*m.m21*m.m33 - m.m11*m.m23*m.m32;
	adj.m01 = -(m.m01*m.m22*m.m33 + m.m02*m.m23*m.m31 + m.m03*m.m21*m.m32 - m.m03*m.m22*m.m31 - m.m02*m.m21*m.m33 - m.m01*m.m23*m.m32);
	adj.m02 = m.m01*m.m12*m.m33 + m.m02*m.m13*m.m31 + m.m03*m.m11*m.m32 - m.m03*m.m12*m.m31 - m.m02*m.m11*m.m33 - m.m01*m.m13*m.m32;
	adj.m03 = -(m.m01*m.m12*m.m23 + m.m02*m.m13*m.m21 + m.m03*m.m11*m.m22 - m.m03*m.m12*m.m21 - m.m02*m.m11*m.m23 - m.m01*m.m13*m.m22);

	adj.m10 = -(m.m10*m.m22*m.m33 + m.m12*m.m23*m.m30 + m.m13*m.m20*m.m32 - m.m13*m.m22*m.m30 - m.m12*m.m20*m.m33 - m.m10*m.m23*m.m32);
	adj.m11 = m.m00*m.m22*m.m33 + m.m02*m.m23*m.m30 + m.m03*m.m20*m.m32 - m.m03*m.m22*m.m30 - m.m02*m.m20*m.m33 - m.m00*m.m23*m.m32;
	adj.m12 = -(m.m00*m.m12*m.m33 + m.m02*m.m13*m.m30 + m.m03*m.m10*m.m32 - m.m03*m.m12*m.m30 - m.m02*m.m10*m.m33 - m.m00*m.m13*m.m32);
	adj.m13 = m.m00*m.m12*m.m23 + m.m02*m.m13*m.m20 + m.m03*m.m10*m.m22 - m.m03*m.m12*m.m20 - m.m02*m.m10*m.m23 - m.m00*m.m13*m.m22;

	adj.m20 = m.m10*m.m21*m.m33 + m.m11*m.m23*m.m30 + m.m13*m.m20*m.m31 - m.m13*m.m21*m.m30 - m.m11*m.m20*m.m33 - m.m10*m.m23*m.m31;
	adj.m21 = -(m.m00*m.m21*m.m33 + m.m01*m.m23*m.m30 + m.m03*m.m20*m.m31 - m.m03*m.m21*m.m30 - m.m01*m.m20*m.m33 - m.m00*m.m23*m.m31);
	adj.m22 = m.m00*m.m11*m.m33 + m.m01*m.m13*m.m30 + m.m03*m.m10*m.m31 - m.m03*m.m11*m.m30 - m.m01*m.m10*m.m33 - m.m00*m.m13*m.m31;
	adj.m23 = -(m.m00*m.m11*m.m23 + m.m01*m.m13*m.m20 + m.m03*m.m10*m.m21 - m.m03*m.m11*m.m20 - m.m01*m.m10*m.m23 - m.m00*m.m13*m.m21);

	adj.m30 = -(m.m10*m.m21*m.m32 + m.m11*m.m22*m.m30 + m.m12*m.m20*m.m31 - m.m12*m.m21*m.m30 - m.m11*m.m20*m.m32 - m.m10*m.m22*m.m31);
	adj.m31 = m.m00*m.m21*m.m32 + m.m01*m.m22*m.m30 + m.m02*m.m20*m.m31 - m.m02*m.m21*m.m30 - m.m01*m.m20*m.m32 - m.m00*m.m22*m.m31;
	adj.m32 = -(m.m00*m.m11*m.m32 + m.m01*m.m12*m.m30 + m.m02*m.m10*m.m31 - m.m02*m.m11*m.m30 - m.m01*m.m10*m.m32 - m.m00*m.m12*m.m31);
	adj.m33 = m.m00*m.m11*m.m22 + m.m01*m.m12*m.m20 + m.m02*m.m10*m.m21 - m.m02*m.m11*m.m20 - m.m01*m.m10*m.m22 - m.m00*m.m12*m.m21;

	const float inv_d = 1.0f / d;
	return adj * inv_d;
}

} // namespace math
