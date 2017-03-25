#ifndef MATH_UTILITY_H_
#define MATH_UTILITY_H_

#include <cassert>
#include <cmath>
#include <type_traits>


namespace math {

template<typename Numeric>
inline bool approx_equal(const Numeric& lhs, const Numeric& rhs, const Numeric& max_abs_diff = Numeric(1e-5)) noexcept
{
	static_assert(std::is_same<Numeric, float>::value || std::is_same<Numeric, double>::value,
		"Numeric must be float or double.");

	assert(std::isfinite(lhs));
	assert(std::isfinite(rhs));
	assert(std::isfinite(max_abs_diff));

	return std::abs(lhs - rhs) <= max_abs_diff;
}

} // namesace math

#endif // MATH_UTILITY_H_
