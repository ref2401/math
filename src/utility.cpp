#include "math/utility.h"


namespace math {

template<typename Numeric>
bool approx_equal(const Numeric& l, const Numeric& r, const Numeric& max_abs_diff) noexcept
{
	static_assert(std::is_floating_point<Numeric>::value, "Numeric must be a floating point type.");

	assert(std::isfinite(l));
	assert(std::isfinite(r));
	assert(std::isfinite(max_abs_diff));

	return std::abs(l - r) <= max_abs_diff;
}

template bool approx_equal<float>(const float& l, const float& r, const float& max_abs_diff) noexcept;
template bool approx_equal<double>(const double& l, const double& r, const double& max_abs_diff) noexcept;
template bool approx_equal<long double>(const long double& l, const long double& r, 
	const long double& max_abs_diff) noexcept;

template<typename Numeric>
Numeric clamp(const Numeric& v, const Numeric& lo, const Numeric& hi) noexcept
{
	static_assert(std::is_integral<Numeric>::value || std::is_floating_point<Numeric>::value,
		"Numeric type must be an integer or a floating point type.");
	assert(lo <= hi);

	return std::min(hi, std::max(lo, v));
}

template float clamp<float>(const float& v, const float& lo, const float& hi) noexcept;
template double clamp<double>(const double& v, const double& lo, const double& hi) noexcept;
template long double clamp<long double>(const long double& v, const long double& lo, const long double& hi) noexcept;
template int8_t clamp<int8_t>(const int8_t& v, const int8_t& lo, const int8_t& hi) noexcept;
template int32_t clamp<int32_t>(const int32_t& v, const int32_t& lo, const int32_t& hi) noexcept;
template int64_t clamp<int64_t>(const int64_t& v, const int64_t& lo, const int64_t& hi) noexcept;
template uint8_t clamp<uint8_t>(const uint8_t& v, const uint8_t& lo, const uint8_t& hi) noexcept;
template uint32_t clamp<uint32_t>(const uint32_t& v, const uint32_t& lo, const uint32_t& hi) noexcept;
template uint64_t clamp<uint64_t>(const uint64_t& v, const uint64_t& lo, const uint64_t& hi) noexcept;

template<typename Numeric>
Numeric lerp(const Numeric& l, const Numeric& r, const Numeric& factor) noexcept
{
	static_assert(std::is_floating_point<Numeric>::value, "Numeric must be a floating point type.");

	assert(0 <= factor && factor <= 1);
	return l + factor * (r - l);
}

template float lerp<float>(const float& l, const float& r, const float& factor) noexcept;
template double lerp<double>(const double& l, const double& r, const double& factor) noexcept;
template long double lerp<long double>(const long double& l, const long double& r,
	const long double& factor) noexcept;

template<typename Numeric>
Numeric saturate(const Numeric& val) noexcept
{
	static_assert(std::is_integral<Numeric>::value || std::is_floating_point<Numeric>::value,
		"Numeric type must be an integer or a floating point type.");

	return std::min<Numeric>(1, std::max<Numeric>(0, val));
}

template float saturate<float>(const float& val) noexcept;
template double saturate<double>(const double& val) noexcept;
template long double saturate<long double>(const long double& val) noexcept;
template int8_t saturate<int8_t>(const int8_t& val) noexcept;
template int32_t saturate<int32_t>(const int32_t& val) noexcept;
template int64_t saturate<int64_t>(const int64_t& val) noexcept;
template uint8_t saturate<uint8_t>(const uint8_t& val) noexcept;
template uint32_t saturate<uint32_t>(const uint32_t& val) noexcept;
template uint64_t saturate<uint64_t>(const uint64_t& val) noexcept;

template<typename Numeric>
Numeric sign(const Numeric& s) noexcept
{
	static_assert(std::is_signed<Numeric>::value
		&& std::is_arithmetic<Numeric>::value, "Numeric must be a signed arithmetic type.");

	return Numeric((Numeric(0) < s) - (s < Numeric(0)));
}

template float sign<float>(const float& s) noexcept;
template double sign<double>(const double& s) noexcept;
template long double sign<long double>(const long double& s) noexcept;
template int8_t sign<int8_t>(const int8_t& s) noexcept;
template int32_t sign<int32_t>(const int32_t& s) noexcept;
template int64_t sign<int64_t>(const int64_t& s) noexcept;

template<typename Numeric>
Numeric step(const Numeric& edge, const Numeric& x) noexcept
{
	return (x >= edge) ? Numeric(1) : Numeric(0);
}

template float step<float>(const float& edge, const float& x) noexcept;
template double step<double>(const double& edge, const double& x) noexcept;
template long double step<long double>(const long double& edge, const long double& x) noexcept;
template int8_t step<int8_t>(const int8_t& edge, const int8_t& x) noexcept;
template int32_t step<int32_t>(const int32_t& edge, const int32_t& x) noexcept;
template int64_t step<int64_t>(const int64_t& edge, const int64_t& x) noexcept;
template uint8_t step<uint8_t>(const uint8_t& edge, const uint8_t& x) noexcept;
template uint32_t step<uint32_t>(const uint32_t& edge, const uint32_t& x) noexcept;
template uint64_t step<uint64_t>(const uint64_t& edge, const uint64_t& x) noexcept;

} // namespace math