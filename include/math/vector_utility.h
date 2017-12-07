#ifndef MATH_VECTOR_UTILITY_H_
#define MATH_VECTOR_UTILITY_H_

#include <cassert>
#include "math/vector_float.h"
#include "math/vector_int.h"


namespace math {

template<typename V>
inline uint32_t pack_into_8_8_8_8(const V& v)
{
	static_assert(std::is_same<V, ubyte4>::value || std::is_same<V, uint4>::value,
		"V may be ubyte4 or uint4");

	return (uint32_t(v.x) << 24)
		| (uint32_t(v.y) << 16)
		| (uint32_t(v.z) << 8)
		| uint32_t(v.w);
}

uint32_t pack_snorm_10_10_10_2(const float4& v) noexcept;

uint32_t pack_unorm_10_10_10_2(const float4& v) noexcept;

inline uint32_t pack_unorm_16_16(const float2& v) noexcept
{
    return (uint32_t(v.x * 65535.0f) << 16) | uint32_t(v.y * 65535.0f);
}

inline uint32_t pack_unorm_8_8_8(const float3& v) noexcept
{
	return (uint32_t(v.x * 255.0f) << 16)
		| (uint32_t(v.y * 255.0f) << 8)
		| (uint32_t(v.z * 255.0f));
}

inline uint32_t pack_unorm_8_8_8_8(const float4& v) noexcept
{
	return (uint32_t(v.x * 255.0f) << 24)
		| (uint32_t(v.y * 255.0f) << 16)
		| (uint32_t(v.z * 255.0f) << 8)
		| uint32_t(v.w * 255.0f);
}

template<typename V>
inline V unpack_8_8_8_8_into(uint32_t val) noexcept
{
	return V(
		V::component_type((val >> 24) & 0xFF),
		V::component_type((val >> 16) & 0xFF),
		V::component_type((val >> 8) & 0xFF),
		V::component_type(val & 0xFF)
	);
}

float4 unpack_snorm_10_10_10_2(uint32_t p) noexcept;

float4 unpack_unorm_10_10_10_2(uint32_t p) noexcept;

inline float2 unpack_unorm_16_16(uint32_t val) noexcept
{
	return float2(
		((val >> 16) & 0xFFFF) / 65535.0f,
		(val & 0xFFFF) / 65535.0f
	);
} 

inline float3 unpack_unorm_8_8_8(uint32_t val) noexcept
{
	return float3(
		((val >> 16) & 0xFF) / 255.0f,
		((val >> 8) & 0xFF) / 255.0f,
		(val & 0xFF) / 255.0f
	);
}

inline float4 unpack_unorm_8_8_8_8(uint32_t val) noexcept
{
	return float4(
		((val >> 24) & 0xFF) / 255.0f,
		((val >> 16) & 0xFF) / 255.0f,
		((val >> 8) & 0xFF) / 255.0f,
		(val & 0xFF) / 255.0f
	);
}

} // namespace math

#endif // MATH_VECTOR_UTILITY_H_
