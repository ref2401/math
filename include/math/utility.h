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
// Numeric must be a floating point type.
template<typename Numeric>
bool approx_equal(const Numeric& l, const Numeric& r, 
	const Numeric& max_abs_diff = Numeric(1e-5)) noexcept;

// Clamps v into the given bounds [lo, hi].
// Numeric must be an integer or a floating point type.
template<typename Numeric>
Numeric clamp(const Numeric& v, const Numeric& lo, const Numeric& hi) noexcept;

// Linearly interpolates between two values.
// Numeric must be an integer or a floating point type.
// Params:
// -	l:		The start of the range in which to interpolate.
// -	rh:		The end of the range in which to interpolate.
// -	factor:	The value to use to interpolate between lhs & rhs.
//				Factor has to lie within the range [0 .. 1].
template<typename Numeric>
Numeric lerp(const Numeric& l, const Numeric& r, const Numeric& factor) noexcept;

// Clamps v into the [0, 1] bounds.
// Numeric must be an integer or a floating point type.
template<typename Numeric>
Numeric saturate(const Numeric& val) noexcept;

// The following formula is used to determine the return value (c) ? b : a;
// Numeric must be an integer or a floating point type.
template<typename Numeric>
Numeric select(const Numeric& a, const Numeric& b, bool c) noexcept;

// Returns -1 if s is less than zero; 0 if s equals zero; and 1 if s is greater than zero.
// Numeric must be a signed arithmetic type.
template<typename Numeric>
Numeric sign(const Numeric& s) noexcept;

// This function uses the following formula: (x >= y) ? 1 : 0.
// Numeric must be an integer or a floating point type.
template<typename Numeric>
Numeric step(const Numeric& edge, const Numeric& x) noexcept;

} // namespace math

#endif // MATH_UTILITY_H_
