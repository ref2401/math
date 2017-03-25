#ifndef MATH_UTILITY_H_
#define MATH_UTILITY_H_

#include <cassert>
#include <cmath>
#include <algorithm>
#include <type_traits>


namespace math {

// Determines whether lhs is approximately equal to rhs 
// admitting a maximum absolute difference max_abs.
// If Numeric is an integral value then max_abs doesn't matter.
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

} // namesace math

#endif // MATH_UTILITY_H_
