#include "math/vector_traits.h"

#include <type_traits>
#include "CppUnitTest.h"

using math::float2;
using math::float3;
using math::float4;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace unittest {

TEST_CLASS(math_vector_traits_funcs) {
public:

	TEST_METHOD(is_floating_point_vector)
	{
		using math::is_floating_point_vector;

		Assert::IsTrue(is_floating_point_vector<float2>::value);
		Assert::IsTrue(is_floating_point_vector<float3>::value);
		Assert::IsTrue(is_floating_point_vector<float4>::value);
	}

	TEST_METHOD(vector_traits_floating_point_vector)
	{
		using math::vector_traits;
		using float2_traits = vector_traits<float2>;
		using float3_traits = vector_traits<float3>;
		using float4_traits = vector_traits<float4>;

		// float2
		Assert::AreEqual<size_t>(2, float2_traits::component_count);
		Assert::IsTrue(std::is_same<float, float2_traits::component_type>::value);
		// float3
		Assert::AreEqual<size_t>(3, float3_traits::component_count);
		Assert::IsTrue(std::is_same<float, float3_traits::component_type>::value);
		// float4
		Assert::AreEqual<size_t>(4, float4_traits::component_count);
		Assert::IsTrue(std::is_same<float, float4_traits::component_type>::value);
	}

};

} // namespace unittest