#ifndef MATH_VECTOR_UTILITY_H_
#define MATH_VECTOR_UTILITY_H_

#include <cassert>
#include "math/vector_float.h"
#include "math/vector_int.h"


namespace math {

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

template<typename T>
inline vec_int_3<T> unpack_unorm_8_8_8(uint32_t val) noexcept
{
	static_assert(std::is_same<T, uint8_t>:: value || std::is_same<T, uint32_t>::value,
		"T may be uint8_t or uint32_t");

	return vec_int_3<T>(
		T((val >> 16) & 0xFF),
		T((val >> 8) & 0xFF),
		T(val & 0xFF));
}

template<typename T>
inline vec_int_4<T> unpack_unorm_8_8_8_8(uint32_t val) noexcept
{
	static_assert(std::is_same<T, uint8_t>::value || std::is_same<T, uint32_t>::value,
		"T may be uint8_t or uint32_t");

	return vec_int_4<T>(
		T((val >> 24) & 0xFF),
		T((val >> 16) & 0xFF),
		T((val >> 8) & 0xFF),
		T(val & 0xFF)
	);
}

uint32_t pack_snorm_10_10_10_2(const float4& vo) noexcept;

uint32_t pack_unorm_10_10_10_2(const float4& vo) noexcept;

float4 unpack_snorm_10_10_10_2(uint32_t p) noexcept;

float4 unpack_unorm_10_10_10_2(uint32_t p) noexcept;

} // namespace math

#endif // MATH_VECTOR_UTILITY_H_
