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
	TEST_METHOD(min_vec2_limits)
	{
		using math::min;

		{
			constexpr auto small = std::numeric_limits<float>::min();
			constexpr auto big = std::numeric_limits<float>::max();

			Assert::IsTrue(min<math::float2>({ small, big}, {big, small}) == math::float2{small, small});
			Assert::IsTrue(min<math::float2>({ big, small}, {small, big}) == math::float2{small, small});

			Assert::IsTrue(min<math::float2>({ small, small}, {small, small}) == math::float2{small, small});
			Assert::IsTrue(min<math::float2>({ big, big}, {big, big}) == math::float2{big, big});
		}

		{
			constexpr auto small = std::numeric_limits<int>::min();
			constexpr auto big = std::numeric_limits<int>::max();

			Assert::IsTrue(min<math::int2>({ small, big }, { big, small }) == math::int2{ small, small });
			Assert::IsTrue(min<math::int2>({ big, small }, { small, big }) == math::int2{ small, small });

			Assert::IsTrue(min<math::int2>({ small, small }, { small, small }) == math::int2{ small, small });
			Assert::IsTrue(min<math::int2>({ big, big }, { big, big }) == math::int2{ big, big });
		}
	}

	TEST_METHOD(min_vec2_usual_values)
	{
		using math::min;

		{
			constexpr auto small = -5.0f;
			constexpr auto big = 300.0f;

			Assert::IsTrue(min<math::float2>({ small, big }, { big, small }) == math::float2{ small, small });
			Assert::IsTrue(min<math::float2>({ big, small }, { small, big }) == math::float2{ small, small });

			Assert::IsTrue(min<math::float2>({ small, small }, { small, small }) == math::float2{ small, small });
			Assert::IsTrue(min<math::float2>({ big, big }, { big, big }) == math::float2{ big, big });
		}

		{
			constexpr auto small = -5;
			constexpr auto big = 300;

			Assert::IsTrue(min<math::int2>({ small, big }, { big, small }) == math::int2{ small, small });
			Assert::IsTrue(min<math::int2>({ big, small }, { small, big }) == math::int2{ small, small });

			Assert::IsTrue(min<math::int2>({ small, small }, { small, small }) == math::int2{ small, small });
			Assert::IsTrue(min<math::int2>({ big, big }, { big, big }) == math::int2{ big, big });
		}
	}

	TEST_METHOD(min_vec3_limits)
	{
		using math::min;

		{
			constexpr auto small = std::numeric_limits<float>::min();
			constexpr auto big = std::numeric_limits<float>::max();

			Assert::IsTrue(min<math::float3>({ small, big, big }, { big, small, small }) == math::float3{ small, small, small });
			Assert::IsTrue(min<math::float3>({ big, small, big }, { small, big, small }) == math::float3{ small, small, small });
			Assert::IsTrue(min<math::float3>({ big, big, small }, { small, small, big }) == math::float3{ small, small, small });

			Assert::IsTrue(min<math::float3>({ small, small, small }, { small, small, small }) == math::float3{ small, small, small });
			Assert::IsTrue(min<math::float3>({ big, big, big }, { big, big, big }) == math::float3{ big, big, big });
		}

		{
			constexpr auto small = std::numeric_limits<int>::min();
			constexpr auto big = std::numeric_limits<int>::max();

			Assert::IsTrue(min<math::int3>({ small, big, big }, { big, small, small }) == math::int3{ small, small, small });
			Assert::IsTrue(min<math::int3>({ big, small, big }, { small, big, small }) == math::int3{ small, small, small });
			Assert::IsTrue(min<math::int3>({ big, big, small }, { small, small, big }) == math::int3{ small, small, small });
	
			Assert::IsTrue(min<math::int3>({ small, small, small }, { small, small, small }) == math::int3{ small, small, small });
			Assert::IsTrue(min<math::int3>({ big, big, big }, { big, big, big }) == math::int3{ big, big, big });
		}
	}

	TEST_METHOD(min_vec3_usual_values)
	{
		using math::min;

		{
			constexpr auto small = -5.0f;
			constexpr auto big = 300.0f;

			Assert::IsTrue(min<math::float3>({ small, big, big }, { big, small, small }) == math::float3{ small, small, small });
			Assert::IsTrue(min<math::float3>({ big, small, big }, { small, big, small }) == math::float3{ small, small, small });
			Assert::IsTrue(min<math::float3>({ big, big, small }, { small, small, big }) == math::float3{ small, small, small });

			Assert::IsTrue(min<math::float3>({ small, small, small }, { small, small, small }) == math::float3{ small, small, small });
			Assert::IsTrue(min<math::float3>({ big, big, big }, { big, big, big }) == math::float3{ big, big, big });
		}

		{
			constexpr auto small = -5;
			constexpr auto big = 300;

			Assert::IsTrue(min<math::float3>({ small, big, big }, { big, small, small }) == math::float3{ small, small, small });
			Assert::IsTrue(min<math::float3>({ big, small, big }, { small, big, small }) == math::float3{ small, small, small });
			Assert::IsTrue(min<math::float3>({ big, big, small }, { small, small, big }) == math::float3{ small, small, small });

			Assert::IsTrue(min<math::float3>({ small, small, small }, { small, small, small }) == math::float3{ small, small, small });
			Assert::IsTrue(min<math::float3>({ big, big, big }, { big, big, big }) == math::float3{ big, big, big });
		}
	}

	TEST_METHOD(min_vec4_limits)
	{
		using math::min;

		{
			constexpr auto small = std::numeric_limits<float>::min();
			constexpr auto big = std::numeric_limits<float>::max();

			Assert::IsTrue(min<math::float4>({ small, big, big, big }, { big, small, small, small }) == math::float4{ small, small, small, small });
			Assert::IsTrue(min<math::float4>({ big, small, big, big }, { small, big, small, small }) == math::float4{ small, small, small, small });
			Assert::IsTrue(min<math::float4>({ big, big, small, big }, { small, small, big, small }) == math::float4{ small, small, small, small });
			Assert::IsTrue(min<math::float4>({ big, big, big, small }, { small, small, small, big }) == math::float4{ small, small, small, small });

			Assert::IsTrue(min<math::float4>({ small, small, small, small }, { small, small, small, small }) == math::float4{ small, small, small, small });
			Assert::IsTrue(min<math::float4>({ big, big, big, big }, { big, big, big, big }) == math::float4{ big, big, big, big });
		}

		{
			constexpr auto small = std::numeric_limits<int>::min();
			constexpr auto big = std::numeric_limits<int>::max();

			Assert::IsTrue(min<math::int4>({ small, big, big, big }, { big, small, small, small }) == math::int4{ small, small, small, small });
			Assert::IsTrue(min<math::int4>({ big, small, big, big }, { small, big, small, small }) == math::int4{ small, small, small, small });
			Assert::IsTrue(min<math::int4>({ big, big, small, big }, { small, small, big, small }) == math::int4{ small, small, small, small });
			Assert::IsTrue(min<math::int4>({ big, big, big, small }, { small, small, small, big }) == math::int4{ small, small, small, small });

			Assert::IsTrue(min<math::int4>({ small, small, small, small }, { small, small, small, small }) == math::int4{ small, small, small, small });
			Assert::IsTrue(min<math::int4>({ big, big, big, big }, { big, big, big, big }) == math::int4{ big, big, big, big });
		}
	}

	TEST_METHOD(min_vec4_usual_values)
	{
		using math::min;

		{
			constexpr auto small = -5.0f;
			constexpr auto big = 300.0f;

			Assert::IsTrue(min<math::float4>({ small, big, big, big }, { big, small, small, small }) == math::float4{ small, small, small, small });
			Assert::IsTrue(min<math::float4>({ big, small, big, big }, { small, big, small, small }) == math::float4{ small, small, small, small });
			Assert::IsTrue(min<math::float4>({ big, big, small, big }, { small, small, big, small }) == math::float4{ small, small, small, small });
			Assert::IsTrue(min<math::float4>({ big, big, big, small }, { small, small, small, big }) == math::float4{ small, small, small, small });

			Assert::IsTrue(min<math::float4>({ small, small, small, small }, { small, small, small, small }) == math::float4{ small, small, small, small });
			Assert::IsTrue(min<math::float4>({ big, big, big, big }, { big, big, big, big }) == math::float4{ big, big, big, big });
		}

		{
			constexpr auto small = -5;
			constexpr auto big = 300;

			Assert::IsTrue(min<math::int4>({ small, big, big, big }, { big, small, small, small }) == math::int4{ small, small, small, small });
			Assert::IsTrue(min<math::int4>({ big, small, big, big }, { small, big, small, small }) == math::int4{ small, small, small, small });
			Assert::IsTrue(min<math::int4>({ big, big, small, big }, { small, small, big, small }) == math::int4{ small, small, small, small });
			Assert::IsTrue(min<math::int4>({ big, big, big, small }, { small, small, small, big }) == math::int4{ small, small, small, small });

			Assert::IsTrue(min<math::int4>({ small, small, small, small }, { small, small, small, small }) == math::int4{ small, small, small, small });
			Assert::IsTrue(min<math::int4>({ big, big, big, big }, { big, big, big, big }) == math::int4{ big, big, big, big });
		}
	}

};

} // namespace unittest
