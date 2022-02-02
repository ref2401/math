#ifndef MATH_VECTOR_UTILITY_H_
#define MATH_VECTOR_UTILITY_H_

#include <cassert>
#include "math/math_traits.h"


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

// Returns component-wise minimum of two vectors.
// Params:
//        a, b = input values
template <typename Vec2, std::enable_if_t<is_n_vector<Vec2, 2>(), int> = 0>
inline Vec2 min(const Vec2& a, const Vec2& b) noexcept
{
    return Vec2(
        std::min(a.x, b.x),
        std::min(a.y, b.y)
    );
}

// Returns component-wise minimum of two vectors.
// Params:
//        a, b = input values
template <typename Vec3, std::enable_if_t<is_n_vector<Vec3, 3>(), int> = 0>
inline Vec3 min(const Vec3& a, const Vec3& b) noexcept
{
    return Vec3(
        std::min(a.x, b.x),
        std::min(a.y, b.y),
        std::min(a.z, b.z)
    );
}

// Returns component-wise minimum of two vectors.
// Params:
//        a, b = input values
template <typename Vec4, std::enable_if_t<is_n_vector<Vec4, 4>(), int> = 0>
inline Vec4 min(const Vec4& a, const Vec4& b) noexcept
{
    return Vec4(
        std::min(a.x, b.x),
        std::min(a.y, b.y),
        std::min(a.z, b.z),
        std::min(a.w, b.w)
    );
}

// Returns component-wise maximum if two vectors
// Params:
//        a, b = input values
template <typename Vec2, std::enable_if_t<is_n_vector<Vec2, 2>(), int> = 0>
inline Vec2 max(const Vec2& a, const Vec2& b) noexcept
{
    return Vec2(
        std::max(a.x, b.x),
        std::max(a.y, b.y)
    );
}

// Returns component-wise maximum if two vectors
// Params:
//        a, b = input values
template <typename Vec3, std::enable_if_t<is_n_vector<Vec3, 3>(), int> = 0>
inline Vec3 max(const Vec3& a, const Vec3& b) noexcept
{
    return Vec3(
        std::max(a.x, b.x),
        std::max(a.y, b.y),
        std::max(a.z, b.z)
    );
}

// Returns component-wise maximum if two vectors
// Params:
//        a, b = input values
template <typename Vec4, std::enable_if_t<is_n_vector<Vec4, 4>(), int> = 0>
inline Vec4 max(const Vec4& a, const Vec4& b) noexcept
{
    return Vec4(
        std::max(a.x, b.x),
        std::max(a.y, b.y),
        std::max(a.z, b.z),
        std::max(a.w, b.w)
    );
}

} // namespace math

#endif // MATH_VECTOR_UTILITY_H_
