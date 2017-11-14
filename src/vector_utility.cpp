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

struct uint_2_10_10_10 final {
	uint_2_10_10_10() noexcept = default;

	explicit uint_2_10_10_10(uint32_t raw) noexcept : raw_data(raw) {}

	explicit uint_2_10_10_10(const math::float4& v) noexcept
		: w(unsigned int(v.w)),
		x(unsigned int(v.x)),
		y(unsigned int(v.y)),
		z(unsigned int(v.z))
	{}


	union {
		struct {
			unsigned int w : 2;
			unsigned int x : 10;
			unsigned int y : 10;
			unsigned int z : 10;
		};

		uint32_t raw_data;
	};
};

struct uint_2_10_10_10_rev final {
	uint_2_10_10_10_rev() noexcept = default;

	explicit uint_2_10_10_10_rev(uint32_t raw) noexcept : raw_data(raw) {}

	explicit uint_2_10_10_10_rev(const math::float4& v) noexcept
		: w(unsigned int(v.w)),
		z(unsigned int(v.z)),
		y(unsigned int(v.y)),
		x(unsigned int(v.x))
	{}


	union {
		struct {
			unsigned int w : 2;
			unsigned int z : 10;
			unsigned int y : 10;
			unsigned int x : 10;
			
		};

		uint32_t raw_data;
	};
};

struct uint_10_10_10_2 final {
	uint_10_10_10_2() noexcept = default;

	explicit uint_10_10_10_2(uint32_t raw) noexcept : raw_data(raw) {}

	explicit uint_10_10_10_2(const math::float4& v) noexcept
		: x(unsigned int(v.x)),
		y(unsigned int(v.y)),
		z(unsigned int(v.z)),
		w(unsigned int(v.w))
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

uint32_t pack_snorm_10_10_10_2(const float4& vo) noexcept
{
	const float4 v = float4(511.0f, 511.0f, 511.0f, 1.0f)
		* clamp(vo, -float4::unit_xyzw, float4::unit_xyzw);

	const int_10_10_10_2 packed(round(v));
	return packed.raw_data;
}

uint32_t pack_unorm_2_10_10_10(const float4& vo) noexcept
{
	const float4 v = float4(1023.0f, 1023.0f, 1023.0f, 3.0f)
		* clamp(vo, float4::zero, float4::unit_xyzw);

	const uint_2_10_10_10 packed(round(v));
	return packed.raw_data;
}

uint32_t pack_unorm_2_10_10_10_rev(const float4& vo) noexcept
{
	const float4 v = float4(1023.0f, 1023.0f, 1023.0f, 3.0f)
		* clamp(vo, float4::zero, float4::unit_xyzw);

	const uint_2_10_10_10_rev packed(round(v));
	return packed.raw_data;
}

uint32_t pack_unorm_10_10_10_2(const float4& vo) noexcept
{
	const float4 v = float4(1023.0f, 1023.0f, 1023.0f, 3.0f)
		* clamp(vo, float4::zero, float4::unit_xyzw);

	const uint_10_10_10_2 packed(round(v));
	return packed.raw_data;
}

float4 unpack_snorm_10_10_10_2(uint32_t p) noexcept
{
	const int_10_10_10_2 packed(p);
	return float4(1.0f / 511.0f, 1.0f / 511.0f, 1.0f / 511.0f, 1.0f)
		* float4(float(packed.x), float(packed.y), float(packed.z), float(packed.w));
}

float4 unpack_unorm_2_10_10_10(uint32_t p) noexcept
{
	const uint_2_10_10_10 packed(p);
	return float4(1.0f / 1023.0f, 1.0f / 1023.0f, 1.0f / 1023.0f, 1.0f / 3.0f)
		* float4(float(packed.x), float(packed.y), float(packed.z), float(packed.w));
}

float4 unpack_unorm_2_10_10_10_rev(uint32_t p) noexcept
{
	const uint_2_10_10_10_rev packed(p);
	return float4(1.0f / 1023.0f, 1.0f / 1023.0f, 1.0f / 1023.0f, 1.0f / 3.0f)
		* float4(float(packed.x), float(packed.y), float(packed.z), float(packed.w));
}

float4 unpack_unorm_10_10_10_2(uint32_t p) noexcept
{
	const uint_10_10_10_2 packed(p);
	return float4(1.0f / 1023.0f, 1.0f / 1023.0f, 1.0f / 1023.0f, 1.0f / 3.0f)
		* float4(float(packed.x), float(packed.y), float(packed.z), float(packed.w));
}

} // namespace math
