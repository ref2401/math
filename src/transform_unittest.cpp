#include "math/transform.h"

#include "CppUnitTest.h"

using math::float2;
using math::float3;
using math::float4;
using math::quat;
using math::float3x3;
using math::float4x4;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

template<> inline std::wstring ToString<float2>(const float2& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<float3>(const float3& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<float4>(const float4& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<quat>(const quat& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<float3x3>(const float3x3& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<float4x4>(const float4x4& t) { RETURN_WIDE_STRING(t); }

}}} // namespace Microsoft::VisualStudio::CppUnitTestFramework


namespace unittest {

TEST_CLASS(math_transform_fucns) {
public:

	TEST_METHOD(ox_oy_oz)
	{
		using math::ox;
		using math::oy;
		using math::oz;
		using math::set_ox;
		using math::set_oy;
		using math::set_oz;


		float3x3 m3(
			0, 1, 2,
			3, 4, 5,
			6, 7, 8);

		Assert::AreEqual(float3(0, 3, 6), ox(m3));
		Assert::AreEqual(float3(1, 4, 7), oy(m3));
		Assert::AreEqual(float3(2, 5, 8), oz(m3));

		set_ox(m3, float3(21, 22, 23));
		set_oy(m3, float3(24, 25, 26));
		set_oz(m3, float3(27, 28, 29));
		Assert::AreEqual(float3x3(21, 24, 27, 22, 25, 28, 23, 26, 29), m3);


		float4x4 m4(
			0, 1, 2, 3,
			4, 5, 6, 7,
			8, 9, 10, 11,
			12, 13, 14, 15);

		Assert::AreEqual(float3(0, 4, 8), ox(m4));
		Assert::AreEqual(float3(1, 5, 9), oy(m4));
		Assert::AreEqual(float3(2, 6, 10), oz(m4));

		set_ox(m4, float3(21, 22, 23));
		set_oy(m4, float3(24, 25, 26));
		set_oz(m4, float3(27, 28, 29));
		Assert::AreEqual(float4x4(21, 24, 27, 3, 22, 25, 28, 7, 23, 26, 29, 11, 12, 13, 14, 15), m4);
	}
};

} // namespace unittest
