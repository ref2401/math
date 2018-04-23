#ifndef MATH_UTILITY_H_
#define MATH_UTILITY_H_

#include <cassert>
#include <cmath>
#include <algorithm>
#include <type_traits>


namespace math {

constexpr float pi = 3.1415926535897932384626433832f;
constexpr float pi_2 = pi / 2.0f;
constexpr float pi_3 = pi / 3.0f;
constexpr float pi_4 = pi / 4.0f;
constexpr float pi_8 = pi / 8.0f;
constexpr float pi_16 = pi / 16.0f;
constexpr float pi_32 = pi / 32.0f;
constexpr float pi_64 = pi / 64.0f;
constexpr float pi_128 = pi / 128.0f;


// Determines whether l is approximately equal to r admitting a maximum absolute difference max_abs_diff.
template<typename Numeric>
inline bool approx_equal(const Numeric& l, const Numeric& r, const Numeric& max_abs_diff = Numeric(1e-5)) noexcept
{
	static_assert(std::is_floating_point<Numeric>::value, "Numeric must be a floating point value.");

	assert(std::isfinite(l));
	assert(std::isfinite(r));
	assert(std::isfinite(max_abs_diff));

	return std::abs(l - r) <= max_abs_diff;
}

// Clamps v into the given bounds [lo, hi].
template<typename Numeric>
inline Numeric clamp(const Numeric& v, const Numeric& lo, const Numeric& hi) noexcept
{
	static_assert(std::is_integral<Numeric>::value || std::is_floating_point<Numeric>::value,
		"Numeric type must be an integer or a floating point value.");
	assert(lo <= hi);

	return std::min(hi, std::max(lo, v));
}

// Linearly interpolates between two values.
// Params:
// -	l:		The start of the range in which to interpolate.
// -	rh:		The end of the range in which to interpolate.
// -	factor:	The value to use to interpolate between lhs & rhs.
//				Factor has to lie within the range [0 .. 1].
template<typename Numeric>
inline Numeric lerp(const Numeric& l, const Numeric& r, const Numeric& factor) noexcept
{
	static_assert(std::is_floating_point<Numeric>::value, "Numeric must be a floating point value.");

	assert(0 <= factor && factor <= 1);
	return l + factor * (r - l);
}

// Clamps v into the [0, 1] bounds.
template<typename Numeric>
inline Numeric saturate(const Numeric& val) noexcept
{
	static_assert(std::is_integral<Numeric>::value || std::is_floating_point<Numeric>::value,
		"Numeric type must be an integer or a floating point value.");

	return std::min<Numeric>(1, std::max<Numeric>(0, val));
}

template<typename Numeric>
inline Numeric sign(const Numeric& s) noexcept
{
    static_assert(std::is_signed<Numeric>::value
			 && std::is_arithmetic<Numeric>::value, "Numeric must be a signed arithmetic value.");

    return Numeric((Numeric(0) < s) - (s < Numeric(0)));
}

} // namespace math

#endif // MATH_UTILITY_H_
