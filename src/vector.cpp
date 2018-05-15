#include "math/vector_bool.h"
#include "math/vector_float.h"
#include "math/vector_int.h"
#include "math/vector_utility.h"


namespace {

#pragma warning(push)
#pragma warning(disable:4201) // Warning C4201 nonstandard extension used : nameless struct / union

struct int_10_10_10_2 final {
	int_10_10_10_2() noexcept = default;

	explicit int_10_10_10_2(uint32_t raw) noexcept : raw_data(raw) {}

	explicit int_10_10_10_2(const math::float4& v) noexcept
		: x(int(v.x)), y(int(v.y)), z(int(v.z)), w(int(v.w))
	{}

	int_10_10_10_2(int x, int y, int z, int w) noexcept : x(x), y(y), z(z), w(w) {}


	union {
		struct {
			int x : 10;
			int y : 10;
			int z : 10;
			int w : 2;
		};

		uint32_t raw_data;
	};
};

struct uint_10_10_10_2 final {
	uint_10_10_10_2() noexcept = default;

	explicit uint_10_10_10_2(uint32_t raw) noexcept : raw_data(raw) {}

	explicit uint_10_10_10_2(const math::float4& v) noexcept
		: x((unsigned int)(v.x)),
		y((unsigned int)(v.y)),
		z((unsigned int)(v.z)),
		w((unsigned int)(v.w))
	{}


	union {
		struct {
			unsigned int x : 10;
			unsigned int y : 10;
			unsigned int z : 10;
			unsigned int w : 2;
		};

		uint32_t raw_data;
	};
};

#pragma warning(pop)

} // namesace


namespace math {

const float2 float2::unit_x(1, 0);
const float2 float2::unit_y(0, 1);
const float2 float2::unit_xy(1);
const float2 float2::zero(0);

const float3 float3::unit_x(1, 0, 0);
const float3 float3::unit_y(0, 1, 0);
const float3 float3::unit_z(0, 0, 1);
const float3 float3::unit_xy(1, 1, 0);
const float3 float3::unit_xyz(1);
const float3 float3::zero(0);

const float4 float4::unit_x(1, 0, 0, 0);
const float4 float4::unit_y(0, 1, 0, 0);
const float4 float4::unit_z(0, 0, 1, 0);
const float4 float4::unit_w(0, 0, 0, 1);
const float4 float4::unit_xyzw(1);
const float4 float4::zero(0);

const quat quat::i(1, 0, 0, 0);
const quat quat::j(0, 1, 0, 0);
const quat quat::k(0, 0, 1, 0);
const quat quat::identity(0, 0, 0, 1);
const quat quat::zero(0, 0, 0, 0);


std::ostream& operator<<(std::ostream& o, const bool2& v)
{
	o << "bool2(" << v.x << ", " << v.y << ")";
	return o;
}

std::wostream& operator<<(std::wostream& o, const bool2& v)
{
	o << "bool2(" << v.x << ", " << v.y << ")";
	return o;
}

std::ostream& operator<<(std::ostream& o, const bool3& v)
{
	o << "bool3(" << v.x << ", " << v.y << ", " << v.z << ")";
	return o;
}

std::wostream& operator<<(std::wostream& o, const bool3& v)
{
	o << "bool3(" << v.x << ", " << v.y << ", " << v.z << ")";
	return o;
}

std::ostream& operator<<(std::ostream& o, const bool4& v)
{
	o << "bool4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return o;
}

std::wostream& operator<<(std::wostream& o, const bool4& v)
{
	o << "bool4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return o;
}

std::ostream& operator<<(std::ostream& out, const float2& v)
{
	out << "float2(" << v.x << ", " << v.y << ")";
	return out;
}

std::wostream& operator<<(std::wostream& out, const float2& v)
{
	out << "float2(" << v.x << ", " << v.y << ")";
	return out;
}

std::ostream& operator<<(std::ostream& out, const float3& v)
{
	out << "float3(" << v.x << ", " << v.y << ", " << v.z << ")";
	return out;
}

std::wostream& operator<<(std::wostream& out, const float3& v)
{
	out << "float3(" << v.x << ", " << v.y << ", " << v.z << ")";
	return out;
}

std::ostream& operator<<(std::ostream& out, const float4& v)
{
	out << "float4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return out;
}

std::wostream& operator<<(std::wostream& out, const float4& v)
{
	out << "float4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return out;
}

std::ostream& operator<<(std::ostream& out, const quat& q)
{
	out << "quat(" << q.x << ", " << q.y << ", " << q.z << ", " << q.a << ")";
	return out;
}

std::wostream& operator<<(std::wostream& out, const quat& q)
{
	out << "quat(" << q.x << ", " << q.y << ", " << q.z << ", " << q.a << ")";
	return out;
}

quat slerp(const quat& q, const quat& r, float factor)
{
	assert(is_normalized(q));
	assert(is_normalized(r));
	assert(0.0f <= factor && factor <= 1.0f);

	float cos_omega = (q.x * r.x) + (q.y * r.y) + (q.z * r.z) + (q.a * r.a);
	quat q1 = r;
	if (cos_omega < 0) {
		cos_omega = -cos_omega;
		q1 = -q1;
	}

	float f0;
	float f1;
	if (cos_omega > 0.9999f) {
		// fallback to linear interpolation
		f0 = 1.0f - factor;
		f1 = factor;
	}
	else {
		float omega = std::acos(cos_omega);
		float inv_sin = 1.0f / std::sin(omega);
		f0 = std::sin((1.0f - factor) * omega) * inv_sin;
		f1 = std::sin(factor * omega) * inv_sin;
	}

	return normalize(f0 * q + f1 * q1);
}

uint32_t pack_snorm_10_10_10_2(const float4& vo) noexcept
{
	const float4 v = float4(511.0f, 511.0f, 511.0f, 1.0f)
		* clamp(vo, -float4::unit_xyzw, float4::unit_xyzw);

	const int_10_10_10_2 packed(round(v));
	return packed.raw_data;
}

float4 unpack_snorm_10_10_10_2(uint32_t p) noexcept
{
	const int_10_10_10_2 packed(p);
	return float4(1.0f / 511.0f, 1.0f / 511.0f, 1.0f / 511.0f, 1.0f)
		* float4(float(packed.x), float(packed.y), float(packed.z), float(packed.w));
}

uint32_t pack_unorm_10_10_10_2(const float4& vo) noexcept
{
	const float4 v = float4(1023.0f, 1023.0f, 1023.0f, 3.0f)
		* clamp(vo, float4::zero, float4::unit_xyzw);

	const uint_10_10_10_2 packed(round(v));
	return packed.raw_data;
}

float4 unpack_unorm_10_10_10_2(uint32_t p) noexcept
{
	const uint_10_10_10_2 packed(p);
	return float4(1.0f / 1023.0f, 1.0f / 1023.0f, 1.0f / 1023.0f, 1.0f / 3.0f)
		* float4(float(packed.x), float(packed.y), float(packed.z), float(packed.w));
}

} // namespace math