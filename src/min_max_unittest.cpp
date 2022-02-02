#include "CppUnitTest.h"
#include "math/vector_utility.h"
#include <bitset>

#include "math/vector_bool.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

	template<> inline std::wstring ToString<math::int2>(const math::int2& t) { RETURN_WIDE_STRING(t); }
	template<> inline std::wstring ToString<math::int3>(const math::int3& t) { RETURN_WIDE_STRING(t); }
	template<> inline std::wstring ToString<math::int4>(const math::int4& t) { RETURN_WIDE_STRING(t); }
	template<> inline std::wstring ToString<math::uint2>(const math::uint2& t) { RETURN_WIDE_STRING(t); }
	template<> inline std::wstring ToString<math::uint3>(const math::uint3& t) { RETURN_WIDE_STRING(t); }
	template<> inline std::wstring ToString<math::uint4>(const math::uint4& t) { RETURN_WIDE_STRING(t); }

}}} // namespace Microsoft::VisualStudio::CppUnitTestFramework


namespace unittest {

TEST_CLASS(math_vector_utility) {
public:

	TEST_METHOD(min_vec2)
	{
		test_min_impl<math::float2>(0.0f, 1.0f);
		test_min_impl<math::float2>(-1.0f, 0.0f);
		test_min_impl<math::float2>(-1.0f, 1.0f);

		test_min_impl<math::int2>(0, 1);
		test_min_impl<math::int2>(-1, 0);
		test_min_impl<math::int2>(-1, 1);

		// techically bool vectors is not vectors, because have no traits
		//test_min_impl<math::bool2>(false, true);
	}
	
	TEST_METHOD(min_vec3)
	{
		test_min_impl<math::float3>(0.0f, 1.0f);
		test_min_impl<math::float3>(-1.0f, 0.0f);
		test_min_impl<math::float3>(-1.0f, 1.0f);

		test_min_impl<math::int3>(0, 1);
		test_min_impl<math::int3>(-1, 0);
		test_min_impl<math::int3>(-1, 1);
	}

	TEST_METHOD(min_vec4)
	{
		test_min_impl<math::float4>(0.0f, 1.0f);
		test_min_impl<math::float4>(-1.0f, 0.0f);
		test_min_impl<math::float4>(-1.0f, 1.0f);

		test_min_impl<math::int4>(0, 1);
		test_min_impl<math::int4>(-1, 0);
		test_min_impl<math::int4>(-1, 1);

	}

	TEST_METHOD(max_vec2)
	{
		test_max_impl<math::float2>(0.0f, 1.0f);
		test_max_impl<math::float2>(-1.0f, 0.0f);
		test_max_impl<math::float2>(-1.0f, 1.0f);

		test_max_impl<math::int2>(0, 1);
		test_max_impl<math::int2>(-1, 0);
		test_max_impl<math::int2>(-1, 1);
	}

	TEST_METHOD(max_vec3)
	{
		test_max_impl<math::float3>(0.0f, 1.0f);
		test_max_impl<math::float3>(-1.0f, 0.0f);
		test_max_impl<math::float3>(-1.0f, 1.0f);

		test_max_impl<math::int3>(0, 1);
		test_max_impl<math::int3>(-1, 0);
		test_max_impl<math::int3>(-1, 1);
	}

	TEST_METHOD(max_vec4)
	{
		test_max_impl<math::float4>(0.0f, 1.0f);
		test_max_impl<math::float4>(-1.0f, 0.0f);
		test_max_impl<math::float4>(-1.0f, 1.0f);

		test_max_impl<math::int4>(0, 1);
		test_max_impl<math::int4>(-1, 0);
		test_max_impl<math::int4>(-1, 1);
	}


private:
	// Generates N-dimensional vector filled with just two numbers - a or b, controlled with bit mask:
	// for exampe mask 0b000 is {a, a, a}, 0b100 is {b, a, a}
	template <typename Vec, typename T = typename math::vector_traits<Vec>::component_type, size_t N = math::vector_traits<Vec>::component_count>
	static Vec generate_vector(std::bitset<N> max_mask, T a, T b)
	{
		const auto select_component = [a, b](bool take_b) { return take_b ? b : a; };

		Vec result;

		result.x = select_component(max_mask[0]);
		result.y = select_component(max_mask[1]);
		if constexpr (N >= 3)
			result.z = select_component(max_mask[2]);
		if constexpr (N == 4)
			result.w = select_component(max_mask[3]);

		return result;
	}

	// Checks all combinations of vector's components of two types (a or b), generates complementary vector (same as previous, but with inverse components - b insted of a etc), runs check function
	template <typename Vec, typename CheckFn, typename T = typename math::vector_traits<Vec>::component_type, size_t N = math::vector_traits<Vec>::component_count>
	static void do_check_fn(T a, T b, CheckFn&& fn_check)
	{
		for (size_t mask = 0; mask <= (1 << N); ++mask)
		{
			Vec vec1 = generate_vector<Vec>(std::bitset<N>{mask}, a, b),
				vec2 = generate_vector<Vec>(std::bitset<N>{mask}, b, a);

			fn_check(a, b, vec1, vec2);
		}
	}

	template <typename Vec, typename T = typename math::vector_traits<Vec>::component_type, size_t N = math::vector_traits<Vec>::component_count>
	void test_min_impl(T v1, T v2)
	{
		do_check_fn<Vec>(v1, v2, [](T v1, T v2, Vec vec_a, Vec vec_b)
			{
				Assert::IsTrue(math::min(vec_a, vec_b) == generate_vector<Vec>(std::bitset<N>{ 0 }, v1, v2));
			});
	}

	template <typename Vec, typename T = typename math::vector_traits<Vec>::component_type, size_t N = math::vector_traits<Vec>::component_count>
	void test_max_impl(T v1, T v2)
	{
		do_check_fn<Vec>(v1, v2, [](T v1, T v2, Vec vec_a, Vec vec_b)
			{
				Assert::IsTrue(math::max(vec_a, vec_b) == generate_vector<Vec>(std::bitset<N>{ 0 }, v2, v1));
			});
	}

};

} // namespace unittest
