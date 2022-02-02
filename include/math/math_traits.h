#ifndef MATH_VECTOR_TRAITS_H_
#define MATH_VECTOR_TRAITS_H_

#include <type_traits>
#include "math/matrix.h"
#include "math/vector_int.h"


namespace math {

// Checks whether M is a matrix;
template<typename M>
constexpr bool is_matrix() noexcept
{
	return std::is_same<M, float3x3>::value
		|| std::is_same<M, float4x4>::value;
}

// vector_traits provides various properties of vector types.
template<typename T>
struct vector_traits;

template<>
struct vector_traits<float2> final {
	using component_type = float;

	static constexpr size_t component_count = 2;
	static constexpr size_t byte_count		= sizeof(component_type) * component_count;
};

template<>
struct vector_traits<float3> final {
	using component_type = float;

	static constexpr size_t component_count = 3;
	static constexpr size_t byte_count		= sizeof(component_type) * component_count;
};

template<>
struct vector_traits<float4> final {
	using component_type = float;

	static constexpr size_t component_count = 4;
	static constexpr size_t byte_count		= sizeof(component_type) * component_count;
};

template<typename T>
struct vector_traits<vec_int_2<T>> final {
	using component_type = T;

	static constexpr size_t component_count = 2;
	static constexpr size_t byte_count		= sizeof(component_type) * component_count;
};

template<typename T>
struct vector_traits<vec_int_3<T>> final {
	using component_type = T;

	static constexpr size_t component_count = 3;
	static constexpr size_t byte_count		= sizeof(component_type) * component_count;
};

template<typename T>
struct vector_traits<vec_int_4<T>> final {
	using component_type = T;
	static constexpr size_t component_count = 4;
	static constexpr size_t byte_count		= sizeof(component_type) * component_count;
};


template <typename V, typename = void>
struct is_vector : std::false_type {};

template <typename V>
struct is_vector<V, std::void_t<typename vector_traits<V>::component_type>> : std::true_type {};


// Checks whether Vec is a floating-point vector type.
template<typename V>
constexpr bool is_floating_point_vector() noexcept
{
	if constexpr (is_vector<V>::value)
		return std::is_floating_point_v<typename vector_traits<V>::component_type>;

	return false;
}

// Checks whether V is an integral vector.
template<typename V>
constexpr bool is_integral_vector()
{
	if constexpr (is_vector<V>::value)
		return std::is_integral_v<typename vector_traits<V>::component_type>;

	return false;
}

// Checks whether Vec is N-dimensional vector known for math library.
// Bool vectors are not supported because they still don't have vector traits.
template<typename V, size_t N>
constexpr bool is_n_vector()
{
	if constexpr (is_vector<V>::value)
		return vector_traits<V>::component_count == N;

	return false;
}

} // namespace math

#endif // MATH_VECTOR_TRAITS_H_
