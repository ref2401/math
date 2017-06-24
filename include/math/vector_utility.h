#ifndef MATH_VECTOR_UTILITY_H_
#define MATH_VECTOR_UTILITY_H_

#include "math/vector_float.h"


namespace math {

namespace intrinsic {

#pragma warning(push)
#pragma warning(disable:4201) // Warning C4201 nonstandard extension used : nameless struct / union

struct int_10_10_10_2 final {

	int_10_10_10_2() noexcept = default;

	explicit int_10_10_10_2(uint32_t raw) noexcept : raw_data(raw) {}

	explicit int_10_10_10_2(const float4& v) noexcept
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

#pragma warning(pop)

} // namesace intrinsic



inline float3 unpack_unorm_8_8_8(uint32_t val) noexcept
{
	// (31 .. 24) bytes are ignored.
	// red: (23 .. 16) bytes. 
	// green: (15 .. 8) bytes. 
	// blue: (7 .. 1) bytes.

	return float3(
		((val >> 16) & 0xFF) / 255.0f,
		((val >> 8) & 0xFF) / 255.0f,
		(val & 0xFF) / 255.0f
	);
}

inline float4 unpack_unorm_8_8_8_8(uint32_t val) noexcept
{
	// red: (32..24) bytes, 
	// green : (23..16) bytes,
	// blue : (15..8) bytes,
	// alpha : (7..0) bytes

	return float4(
		((val >> 24) & 0xFF) / 255.0f,
		((val >> 16) & 0xFF) / 255.0f,
		((val >> 8) & 0xFF) / 255.0f,
		(val & 0xFF) / 255.0f
	);
}

inline uint32_t pack_snorm_10_10_10_2(const float4& vo) noexcept
{
	const float4 v = float4(511.0f, 511.0f, 511.0f, 1.0f) 
		* clamp(vo, -float4::unit_xyzw, float4::unit_xyzw);

	const intrinsic::int_10_10_10_2 packed(round(v));
	return packed.raw_data;
}

inline float4 unpack_snorm_10_10_10_2(uint32_t p) noexcept
{
	const intrinsic::int_10_10_10_2 packed(p);
	return float4(1.0f / 511.0f, 1.0f / 511.0f, 1.0f / 511.0f, 1.0f) 
		* float4(float(packed.x), float(packed.y), float(packed.z), float(packed.w));
}

} // namespace math

#endif // MATH_VECTOR_UTILITY_H_
