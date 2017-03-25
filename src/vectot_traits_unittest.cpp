#include "math/vector_traits.h"
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

};

} // namespace unittest