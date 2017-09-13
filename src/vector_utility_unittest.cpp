#include "math/vector_utility.h"

#include <type_traits>
#include "CppUnitTest.h"


using math::float3;
using math::float4;
using math::ubyte4;
using math::uint3;
using math::uint4;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

template<> inline std::wstring ToString<math::float3>(const math::float3& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<math::float4>(const math::float4& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<math::ubyte4>(const math::ubyte4& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<math::uint3>(const math::uint3& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<math::uint4>(const math::uint4& t) { RETURN_WIDE_STRING(t); }

}}} // namespace Microsoft::VisualStudio::CppUnitTestFramework


namespace unittest {

TEST_CLASS(math_vector_utility_funcs) {
public:

	TEST_METHOD(ubyte_to_8_8_8_8_and_back)
	{
		using math::pack_into_8_8_8_8;
		using math::unpack_8_8_8_8_into_ubyte4;

		struct test_data final {
			ubyte4 unpacked;
			uint32_t packed;
		};

		constexpr size_t test_data_count = 7;
		const test_data list[test_data_count] = {
			{ ubyte4::zero,						0x00'00'00'00 },
			{ ubyte4(0xff, 0x00, 0x00, 0x00),	0xff'00'00'00 },
			{ ubyte4(0x00, 0xff, 0x00, 0x00),	0x00'ff'00'00 },
			{ ubyte4(0x00, 0x00, 0xff, 0x00),	0x00'00'ff'00 },
			{ ubyte4(0x00, 0x00, 0x00, 0xff),	0x00'00'00'ff },
			{ ubyte4(0xff, 0xff, 0xff, 0xff),	0xff'ff'ff'ff },
			{ ubyte4(0xa1, 0xb2, 0xe3, 0xf4),	0xa1'b2'e3'f4 }
		};

		for (size_t i = 0; i < test_data_count; ++i) {
			// expected
			const ubyte4	ue = list[i].unpacked;
			const uint32_t	pe = list[i].packed;
			// actual
			const uint32_t	p = pack_into_8_8_8_8(ue);
			const ubyte4	u = unpack_8_8_8_8_into_ubyte4(p);

			Assert::AreEqual(pe, p);
			Assert::AreEqual(ue, u);
		}
	}

	TEST_METHOD(unorm_to_8_8_8_8_and_back)
	{
		using math::pack_unorm_into_8_8_8_8;
		using math::unpack_8_8_8_8_into_unorm;

		struct test_data final {
			float4 unpacked;
			uint32_t packed;
		};

		const size_t test_data_count = 7;
		const test_data list[test_data_count] = {
			{ float4::zero,			0x00'00'00'00},
			{ float4::unit_x,		0xff'00'00'00 },
			{ float4::unit_y,		0x00'ff'00'00 },
			{ float4::unit_z,		0x00'00'ff'00 },
			{ float4::unit_w,		0x00'00'00'ff },
			{ float4::unit_xyzw,	0xff'ff'ff'ff },
			{ float4(0xa1 / 255.0f, 0xb2 / 255.0f, 0xe3 / 255.0f, 0x18 / 255.0f), 0xa1'b2'e3'18 }
		};
		
		for (size_t i = 0; i < test_data_count; ++i) {
			// expected
			const float4	ue = list[i].unpacked;
			const uint32_t	pe = list[i].packed;
			// actual
			const uint32_t	p = pack_unorm_into_8_8_8_8(ue);
			const float4	u = unpack_8_8_8_8_into_unorm(p);

			Assert::AreEqual(pe, p);
			Assert::AreEqual(ue, u);
		}
	}


	TEST_METHOD(unpack_unorm_8_8_8)
	{
		using math::unpack_unorm_8_8_8;

		Assert::AreEqual(float3::zero, unpack_unorm_8_8_8(0));
		Assert::AreEqual(float3::unit_x, unpack_unorm_8_8_8(0xff'00'00));
		Assert::AreEqual(float3::unit_y, unpack_unorm_8_8_8(0x00'ff'00));
		Assert::AreEqual(float3::unit_z, unpack_unorm_8_8_8(0x00'00'ff));
		Assert::AreEqual(float3::unit_xyz, unpack_unorm_8_8_8(0xffffff));

		Assert::AreEqual(float3(0xa1 / 255.0f, 0xb2 / 255.0f, 0xe3 / 255.0f), unpack_unorm_8_8_8(0xa1'b2'e3));

		Assert::AreEqual(uint3::zero, unpack_unorm_8_8_8<uint3>(0));
		Assert::AreEqual(uint3(0xff, 0, 0), unpack_unorm_8_8_8<uint3>(0xff'00'00));
		Assert::AreEqual(uint3(0, 0xff, 0), unpack_unorm_8_8_8<uint3>(0x00'ff'00));
		Assert::AreEqual(uint3(0, 0, 0xff), unpack_unorm_8_8_8<uint3>(0x00'00'ff));
		Assert::AreEqual(uint3(0xA1, 0xB2, 0xE3), unpack_unorm_8_8_8<uint3>(0xA1'B2'E3));
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


		Assert::AreEqual(ubyte4::zero, unpack_unorm_8_8_8_8<ubyte4>(0));
		Assert::AreEqual(ubyte4(0xff, 0, 0, 0), unpack_unorm_8_8_8_8<ubyte4>(0xff'00'00'00));
		Assert::AreEqual(ubyte4(0, 0xff, 0, 0), unpack_unorm_8_8_8_8<ubyte4>(0x00'ff'00'00));
		Assert::AreEqual(ubyte4(0, 0, 0xff, 0), unpack_unorm_8_8_8_8<ubyte4>(0x00'00'ff'00));
		Assert::AreEqual(ubyte4(0, 0, 0, 0xff), unpack_unorm_8_8_8_8<ubyte4>(0x00'00'00'ff));
		Assert::AreEqual(ubyte4(0xA1, 0xB2, 0xE3, 0x18), unpack_unorm_8_8_8_8<ubyte4>(0xA1'B2'E3'18));

		Assert::AreEqual(uint4::zero, unpack_unorm_8_8_8_8<uint4>(0));
		Assert::AreEqual(uint4(0xff, 0, 0, 0), unpack_unorm_8_8_8_8<uint4>(0xff'00'00'00));
		Assert::AreEqual(uint4(0, 0xff, 0, 0), unpack_unorm_8_8_8_8<uint4>(0x00'ff'00'00));
		Assert::AreEqual(uint4(0, 0, 0xff, 0), unpack_unorm_8_8_8_8<uint4>(0x00'00'ff'00));
		Assert::AreEqual(uint4(0, 0, 0, 0xff), unpack_unorm_8_8_8_8<uint4>(0x00'00'00'ff));
		Assert::AreEqual(uint4(0xA1, 0xB2, 0xE3, 0x18), unpack_unorm_8_8_8_8<uint4>(0xA1'B2'E3'18));
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

	TEST_METHOD(pack_unpack_unorm_10_10_10_2)
	{
		using math::approx_equal;
		using math::clamp;
		using math::pack_unorm_10_10_10_2;
		using math::unpack_unorm_10_10_10_2;


		const float4 vectors[4] = {
			float4::zero,
			float4::unit_xyzw,
			float4(0.7f, 0.0f, 0.4f, 1.0f)
		};

		for (size_t i = 0; i < std::extent<decltype(vectors)>::value; ++i) {
			const float4 v = vectors[i];

			const uint32_t packed = pack_unorm_10_10_10_2(v);
			const float4 vu = unpack_unorm_10_10_10_2(packed);

			Assert::IsTrue(approx_equal(v, vu, 0.01f));
		}


		// The original vector's components are out of range [0.0f, 1.0f]
		const float4 v(-10.0f, 10.0f, 0.0f, 10.0f);
		const float4 v_expected = clamp(v, float4::zero, float4::unit_xyzw);
		const uint32_t packed = pack_unorm_10_10_10_2(v);
		const float4 vu = unpack_unorm_10_10_10_2(packed);
		Assert::IsTrue(approx_equal(v_expected, vu, 0.01f));
	}
};

} // namespace unittest
