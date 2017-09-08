#include "math/math_traits.h"

#include <type_traits>
#include "CppUnitTest.h"

using math::float2;
using math::float3;
using math::float4;
using math::float3x3;
using math::float4x4;
using math::int2;
using math::int3;
using math::int4;
using math::ubyte4;
using math::uint2;
using math::uint3;
using math::uint4;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace unittest {

TEST_CLASS(math_vector_traits_funcs) {
public:

	TEST_METHOD(is_floating_point_vector)
	{
		using math::is_floating_point_vector;

		Assert::IsTrue(is_floating_point_vector<float2>());
		Assert::IsTrue(is_floating_point_vector<float3>());
		Assert::IsTrue(is_floating_point_vector<float4>());

		Assert::IsFalse(is_floating_point_vector<int>());
		Assert::IsFalse(is_floating_point_vector<float>());
	}

	TEST_METHOD(is_integral_vector)
	{
		using math::is_integral_vector;

		Assert::IsTrue(is_integral_vector<int2>());
		Assert::IsTrue(is_integral_vector<int4>());
		Assert::IsTrue(is_integral_vector<ubyte4>());
		Assert::IsTrue(is_integral_vector<uint2>());
		Assert::IsTrue(is_integral_vector<uint4>());

		Assert::IsFalse(is_integral_vector<int>());
		Assert::IsFalse(is_integral_vector<float>());
	}

	TEST_METHOD(is_matrix)
	{
		using math::is_matrix;

		Assert::IsTrue(is_matrix<float3x3>());
		Assert::IsTrue(is_matrix<float4x4>());

		Assert::IsFalse(is_matrix<int>());
		Assert::IsFalse(is_matrix<float3>());
	}

	TEST_METHOD(vector_traits_floating_point_vector)
	{
		using math::vector_traits;
		
		// float2
		using float2_traits = vector_traits<float2>;
		Assert::IsTrue(std::is_same<float, float2_traits::component_type>::value);
		Assert::AreEqual<size_t>(2, float2_traits::component_count);
		Assert::AreEqual<size_t>(2 * sizeof(float), float2_traits::byte_count);

		// float3
		using float3_traits = vector_traits<float3>;
		Assert::IsTrue(std::is_same<float, float3_traits::component_type>::value);
		Assert::AreEqual<size_t>(3, float3_traits::component_count);
		Assert::AreEqual<size_t>(3 * sizeof(float), float3_traits::byte_count);

		// float4
		using float4_traits = vector_traits<float4>;
		Assert::IsTrue(std::is_same<float, float4_traits::component_type>::value);
		Assert::AreEqual<size_t>(4, float4_traits::component_count);
		Assert::AreEqual<size_t>(4 * sizeof(float), float4_traits::byte_count);
	}

	TEST_METHOD(vector_traits_integer_vector)
	{
		using math::vector_traits;

		// int2
		using int2_traits = vector_traits<int2>;
		Assert::IsTrue(std::is_same<int32_t, int2_traits::component_type>::value);
		Assert::AreEqual<size_t>(2, int2_traits::component_count);
		Assert::AreEqual<size_t>(2 * sizeof(int32_t), int2_traits::byte_count);

		// int3
		using int3_traits = vector_traits<int3>;
		Assert::IsTrue(std::is_same<int32_t, int3_traits::component_type>::value);
		Assert::AreEqual<size_t>(3, int3_traits::component_count);
		Assert::AreEqual<size_t>(3 * sizeof(int32_t), int3_traits::byte_count);
		
		// int4
		using int4_traits = vector_traits<int4>;
		Assert::IsTrue(std::is_same<int32_t, int4_traits::component_type>::value);
		Assert::AreEqual<size_t>(4, int4_traits::component_count);
		Assert::AreEqual<size_t>(4 * sizeof(int32_t), int4_traits::byte_count);

		// ubyte
		using ubyte4_traits = vector_traits<ubyte4>;
		Assert::IsTrue(std::is_same<uint8_t, ubyte4_traits::component_type>::value);
		Assert::AreEqual<size_t>(4, ubyte4_traits::component_count);
		Assert::AreEqual<size_t>(4 * sizeof(uint8_t), ubyte4_traits::byte_count);

		// uint2
		using uint2_traits = vector_traits<uint2>;
		Assert::IsTrue(std::is_same<uint32_t, uint2_traits::component_type>::value);
		Assert::AreEqual<size_t>(2, uint2_traits::component_count);
		Assert::AreEqual<size_t>(2 * sizeof(uint32_t), uint2_traits::byte_count);

		// uint3
		using uint3_traits = vector_traits<uint3>;
		Assert::IsTrue(std::is_same<uint32_t, uint3_traits::component_type>::value);
		Assert::AreEqual<size_t>(3, uint3_traits::component_count);
		Assert::AreEqual<size_t>(3 * sizeof(uint32_t), uint3_traits::byte_count);

		// uint4
		using uint4_traits = vector_traits<uint4>;
		Assert::IsTrue(std::is_same<uint32_t, uint4_traits::component_type>::value);
		Assert::AreEqual<size_t>(4, uint4_traits::component_count);
		Assert::AreEqual<size_t>(4 * sizeof(uint32_t), uint4_traits::byte_count);
	}

};

} // namespace unittest