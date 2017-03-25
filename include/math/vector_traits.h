#ifndef MATH_VECTOR_TRAITS_H_
#define MATH_VECTOR_TRAITS_H_

#include <type_traits>
#include "math/vector_float.h"

namespace math {

// Checks whether Vec is a floating - point vector type.
template<typename Vec, bool is_vec = std::is_same<Vec, float2>::value
	|| std::is_same<Vec, float3>::value || std::is_same<Vec, float4>::value>
struct is_floating_point_vector;
template<typename Vec> struct is_floating_point_vector<Vec, true> : std::true_type {};
template<typename Vec> struct is_floating_point_vector<Vec, false> : std::false_type {};


} // namespace math

#endif // MATH_VECTOR_TRAITS_H_
