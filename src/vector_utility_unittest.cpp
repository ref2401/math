#include "math/vector_utility.h"

#include <type_traits>
#include "CppUnitTest.h"


using math::float3;
using math::float4;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

template<> inline std::wstring ToString<math::float3>(const math::float3& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<math::float4>(const math::float4& t) { RETURN_WIDE_STRING(t); }

}}} // namespace Microsoft::VisualStudio::CppUnitTestFramework


namespace unittest {

TEST_CLASS(math_vector_utility_funcs) {
public:

	TEST_METHOD(unpack_unorm_8_8_8)
	{
		using math::unpack_unorm_8_8_8;

		Assert::AreEqual(float3::zero, unpack_unorm_8_8_8(0));
		Assert::AreEqual(float3::unit_x, unpack_unorm_8_8_8(0xff'00'00));
		Assert::AreEqual(float3::unit_y, unpack_unorm_8_8_8(0x00'ff'00));
		Assert::AreEqual(float3::unit_z, unpack_unorm_8_8_8(0x00'00'ff));
		Assert::AreEqual(float3::unit_xyz, unpack_unorm_8_8_8(0xffffff));

		Assert::AreEqual(float3(0xa1 / 255.0f, 0xb2 / 255.0f, 0xe3 / 255.0f), unpack_unorm_8_8_8(0xa1'b2'e3));
	}

	TEST_METHOD(unpack_unorm_8_8_8_8)
	{
		using math::unpack_unorm_8_8_8_8;

		Assert::AreEqual(float4::zero, unpack_unorm_8_8_8_8(0));
		Assert::AreEqual(float4::unit_x, unpack_unorm_8_8_8_8(0xff'00'00'00));
		Assert::AreEqual(float4::unit_y, unpack_unorm_8_8_8_8(0x00'ff'00'00));
		Assert::AreEqual(float4::unit_z, unpack_unorm_8_8_8_8(0x00'00'ff'00));
		Assert::AreEqual(float4::unit_w, unpack_unorm_8_8_8_8(0x00'00'00'ff));
		Assert::AreEqual(float4::unit_xyzw, unpack_unorm_8_8_8_8(0xffffffff));

		Assert::AreEqual(float4(0xA1 / 255.0f, 0xB2 / 255.0f, 0xE3 / 255.0f, 0x18 / 255.0f), unpack_unorm_8_8_8_8(0xa1'b2'e3'18));
	}

	TEST_METHOD(pack_unpack_snorm_10_10_10_2)
	{
		using math::approx_equal;
		using math::clamp;
		using math::pack_snorm_10_10_10_2;
		using math::unpack_snorm_10_10_10_2;


		const float4 vectors[4] = {
			float4::zero,
			-float4::unit_xyzw,
			float4::unit_xyzw,
			float4 (-0.7f, 0.0f, 0.4f, 1.0f)
		};
		
		for (size_t i = 0; i < std::extent<decltype(vectors)>::value; ++i) {
			const float4 v = vectors[i];
			
			const uint32_t packed = pack_snorm_10_10_10_2(v);
			const float4 vu = unpack_snorm_10_10_10_2(packed);

			Assert::IsTrue(approx_equal(v, vu, 0.01f));
		}


		// The original vector's components are out of range [-1.0f, 1.0f]
		const float4 v(-10.0f, 10.0f, 0.0f, 10.0f);
		const float4 v_expected = clamp(v, -float4::unit_xyzw, float4::unit_xyzw);
		const uint32_t packed = pack_snorm_10_10_10_2(v);
		const float4 vu = unpack_snorm_10_10_10_2(packed);
		Assert::IsTrue(approx_equal(v_expected, vu, 0.01f));
	}
};

} // namespace unittest
