#ifndef MATH_VECTOR_UTILITY_H_
#define MATH_VECTOR_UTILITY_H_

#include <cassert>
#include "math/vector_float.h"
#include "math/vector_int.h"


namespace math {

inline uint32_t pack_into_8_8_8_8(const ubyte4& v)
{
	return (uint32_t(v.x) << 24)
		| (uint32_t(v.y) << 16)
		| (uint32_t(v.z) << 8)
		| uint32_t(v.w);
}

inline uint32_t pack_unorm_into_8_8_8_8(const float4& v) noexcept
{
	return (uint32_t(v.x * 255.0f) << 24)
		| (uint32_t(v.y * 255.0f) << 16)
		| (uint32_t(v.z * 255.0f) << 8)
		| uint32_t(v.w * 255.0f);
}

inline ubyte4 unpack_8_8_8_8_into_ubyte4(uint32_t val) noexcept
{
	return ubyte4(
		((val >> 24) & 0xFF),
		((val >> 16) & 0xFF),
		((val >> 8) & 0xFF),
		(val & 0xFF)
	);
}

inline float4 unpack_8_8_8_8_into_unorm(uint32_t val) noexcept
{
	return float4(
		((val >> 24) & 0xFF) / 255.0f,
		((val >> 16) & 0xFF) / 255.0f,
		((val >> 8) & 0xFF) / 255.0f,
		(val & 0xFF) / 255.0f
	);
}


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

template<typename V>
inline V unpack_unorm_8_8_8(uint32_t val) noexcept
{
	static_assert(std::is_same<V, uint3>::value, "V may be uint3");

	return V(
		V::component_type((val >> 16) & 0xFF),
		V::component_type((val >> 8) & 0xFF),
		V::component_type(val & 0xFF));
}

template<typename V>
inline V unpack_unorm_8_8_8_8(uint32_t val) noexcept
{
	static_assert(std::is_same<V, ubyte4>::value || std::is_same<V, uint4>::value,
		"V may be ubyte4 or uint4");

	return V(
		V::component_type((val >> 24) & 0xFF),
		V::component_type((val >> 16) & 0xFF),
		V::component_type((val >> 8) & 0xFF),
		V::component_type(val & 0xFF)
	);
}

uint32_t pack_snorm_10_10_10_2(const float4& vo) noexcept;

uint32_t pack_unorm_10_10_10_2(const float4& vo) noexcept;

float4 unpack_snorm_10_10_10_2(uint32_t p) noexcept;

float4 unpack_unorm_10_10_10_2(uint32_t p) noexcept;

} // namespace math

#endif // MATH_VECTOR_UTILITY_H_
