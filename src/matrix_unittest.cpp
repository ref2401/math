#include "math/matrix.h"

#include <Windows.h>
#include "CppUnitTest.h"

using math::float2;
using math::float3;
using math::float4;
using math::float3x3;
using math::float4x4;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

template<> inline std::wstring ToString<float3>(const float3& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<float4>(const float4& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<float3x3>(const float3x3& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<float4x4>(const float4x4& t) { RETURN_WIDE_STRING(t); }

}}} // namespace Microsoft::VisualStudio::CppUnitTestFramework


namespace unittest {

TEST_CLASS(math_matrix_float3x3) {
public:

	TEST_METHOD(approx_equal)
	{
		using math::approx_equal;

		float3x3 m(0, 1, 2, 3, 4, 5, 6, 7, 8);

		Assert::IsFalse(approx_equal(m, float3x3(100, 1, 2, 3, 4, 5, 6, 7, 8)));
		Assert::IsFalse(approx_equal(m, float3x3(0, 100, 2, 3, 4, 5, 6, 7, 8)));
		Assert::IsFalse(approx_equal(m, float3x3(0, 1, 100, 3, 4, 5, 6, 7, 8)));
		Assert::IsFalse(approx_equal(m, float3x3(0, 1, 2, 100, 4, 5, 6, 7, 8)));
		Assert::IsFalse(approx_equal(m, float3x3(0, 1, 2, 3, 100, 5, 6, 7, 8)));
		Assert::IsFalse(approx_equal(m, float3x3(0, 1, 2, 3, 4, 100, 6, 7, 8)));
		Assert::IsFalse(approx_equal(m, float3x3(0, 1, 2, 3, 4, 5, 100, 7, 8)));
		Assert::IsFalse(approx_equal(m, float3x3(0, 1, 2, 3, 4, 5, 6, 100, 8)));
		Assert::IsFalse(approx_equal(m, float3x3(0, 1, 2, 3, 4, 5, 6, 7, 100)));
		
		Assert::IsTrue(approx_equal(m, float3x3(0, 1, 2, 3, 4, 5, 6, 7, 8)));
		Assert::IsTrue(approx_equal(m, float3x3(0, 1, 2, 3, 4, 5, 6, 7, 8), 0.0f));

		Assert::IsFalse(approx_equal(m, float3x3(0.0001f, 1, 2, 3, 4, 5, 6, 7, 8), 0.0f));
		Assert::IsFalse(approx_equal(m, float3x3(0, 1.0001f, 2, 3, 4, 5, 6, 7, 8), 0.0f));
		Assert::IsFalse(approx_equal(m, float3x3(0, 1, 2.0001f, 3, 4, 5, 6, 7, 8), 0.0f));
		Assert::IsFalse(approx_equal(m, float3x3(0, 1, 2, 3.0001f, 4, 5, 6, 7, 8), 0.0f));
		Assert::IsFalse(approx_equal(m, float3x3(0, 1, 2, 3, 4.0001f, 5, 6, 7, 8), 0.0f));
		Assert::IsFalse(approx_equal(m, float3x3(0, 1, 2, 3, 4, 5.0001f, 6, 7, 8), 0.0f));
		Assert::IsFalse(approx_equal(m, float3x3(0, 1, 2, 3, 4, 5, 6.0001f, 7, 8), 0.0f));
		Assert::IsFalse(approx_equal(m, float3x3(0, 1, 2, 3, 4, 5, 6, 7.0001f, 8), 0.0f));
		Assert::IsFalse(approx_equal(m, float3x3(0, 1, 2, 3, 4, 5, 6, 7, 8.0001f), 0.0f));
	}

	TEST_METHOD(assignments)
	{
		float3x3 m(0, 1, 2, 3, 4, 5, 6, 7, 8);

		// copy assignment
		float3x3 mc = m;
		Assert::IsTrue(mc.m00 == m.m00 && mc.m01 == m.m01 && mc.m02 == m.m02);
		Assert::IsTrue(mc.m10 == m.m10 && mc.m11 == m.m11 && mc.m12 == m.m12);
		Assert::IsTrue(mc.m20 == m.m20 && mc.m21 == m.m21 && mc.m22 == m.m22);

		// move assignment

		float3x3 mv;
		mv = std::move(mc);
		Assert::IsTrue(mv.m00 == m.m00 && mv.m01 == m.m01 && mv.m02 == m.m02);
		Assert::IsTrue(mv.m10 == m.m10 && mv.m11 == m.m11 && mv.m12 == m.m12);
		Assert::IsTrue(mv.m20 == m.m20 && mv.m21 == m.m21 && mv.m22 == m.m22);
	}

	TEST_METHOD(binary_operators)
	{
		float3x3 m(0, 1, 2, 3, 4, 5, 6, 7, 8);
		float3x3 l(5, 7, -9, 0, 3, 4, 4, 3, 9);
		float3x3 n(4, 5, 6, 7, 9, 8, -7, 6, 1);

		Assert::AreEqual(m + l, float3x3(5, 8, -7, 3, 7, 9, 10, 10, 17));
		Assert::AreEqual(m - l, float3x3(-5, -6, 11, 3, 1, 1, 2, 4, -1));

		Assert::AreEqual(m + l, l + m);
		Assert::AreEqual((m + l) + n, m + (l + n));
		Assert::AreEqual(m, m + float3x3::zero);
		Assert::AreEqual(float3x3::zero, m - m);

		Assert::AreEqual(m * 2, float3x3(0, 2, 4, 6, 8, 10, 12, 14, 16));
		Assert::AreEqual(2 * m, float3x3(0, 2, 4, 6, 8, 10, 12, 14, 16));
		Assert::AreEqual(m / 2, float3x3(0, 0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 4));

		// matrix product
		Assert::AreEqual(m * float3x3::identity, float3x3::identity * m);
		Assert::AreEqual(float3x3::zero, m * float3x3::zero);
		Assert::AreEqual((l * m) * n, l * (m * n));
		Assert::AreEqual((l + m) * n, (l * n) + (m * n));
		Assert::AreEqual(l * (m + n), (l * m) + (l * n));

		float3x3 mA(1, 2, 3, 4, 5, 6, 7, 8, 9);
		float3x3 mB(80, 81, 82, 83, 84, 85, 86, 87, 88);
		float3x3 expectedAB(504, 510, 516, 1251, 1266, 1281, 1998, 2022, 2046);
		Assert::AreEqual(expectedAB, mA * mB);
	}

	TEST_METHOD(compound_assignment_operators)
	{
		float3x3 m(0, 1, 2, 3, 4, 5, 6, 7, 8);
		float3x3 r(5, 6, 7, 8, 9, 10, 11, 12, 13);

		(m += r) += r;
		Assert::AreEqual(m, float3x3(
			0 + 5 + 5, 1 + 6 + 6, 2 + 7 + 7,
			3 + 8 + 8, 4 + 9 + 9, 5 + 10 + 10,
			6 + 11 + 11, 7 + 12 + 12, 8 + 13 + 13));

		(m -= r) -= r;
		Assert::AreEqual(m, float3x3(0, 1, 2, 3, 4, 5, 6, 7, 8));

		(m *= 2) *= 3;
		Assert::AreEqual(m, float3x3(
			0, 1 * 6, 2 * 6,
			3 * 6, 4 * 6, 5 * 6,
			6 * 6, 7 * 6, 8 * 6));

		(m /= 3) /= 2;
		Assert::AreEqual(m, float3x3(0, 1, 2, 3, 4, 5, 6, 7, 8));

		// matrix product
		float3x3 mA(1, 2, 3, 4, 5, 6, 7, 8, 9);
		float3x3 mB(80, 81, 82, 83, 84, 85, 86, 87, 88);
		float3x3 expectedAB(504, 510, 516, 1251, 1266, 1281, 1998, 2022, 2046);
		Assert::AreEqual(expectedAB, (mA *= mB));
	}

	TEST_METHOD(ctors)
	{
		float3x3 m;
		Assert::IsTrue(m.m00 == 0 && m.m01 == 0 && m.m02 == 0);
		Assert::IsTrue(m.m10 == 0 && m.m11 == 0 && m.m12 == 0);
		Assert::IsTrue(m.m20 == 0 && m.m21 == 0 && m.m22 == 0);

		float3x3 m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
		Assert::IsTrue(m1.m00 == 1 && m1.m01 == 2 && m1.m02 == 3);
		Assert::IsTrue(m1.m10 == 4 && m1.m11 == 5 && m1.m12 == 6);
		Assert::IsTrue(m1.m20 == 7 && m1.m21 == 8 && m1.m22 == 9);

		// copy ctor
		float3x3 m2 = m1;
		Assert::IsTrue(m2.m00 == m1.m00 && m2.m01 == m1.m01 && m2.m02 == m1.m02);
		Assert::IsTrue(m2.m10 == m1.m10 && m2.m11 == m1.m11 && m2.m12 == m1.m12);
		Assert::IsTrue(m2.m20 == m1.m20 && m2.m21 == m1.m21 && m2.m22 == m1.m22);

		// move ctor
		float3x3 mm = std::move(m2);
		Assert::IsTrue(mm.m00 == m1.m00 && mm.m01 == m1.m01 && mm.m02 == m1.m02);
		Assert::IsTrue(mm.m10 == m1.m10 && mm.m11 == m1.m11 && mm.m12 == m1.m12);
		Assert::IsTrue(mm.m20 == m1.m20 && mm.m21 == m1.m21 && mm.m22 == m1.m22);
	}

	TEST_METHOD(det)
	{
		using math::det;
		using math::transpose;

		Assert::AreEqual(0.f, det(float3x3::zero));
		Assert::AreEqual(1.f, det(float3x3::identity));
		Assert::AreEqual(0.f, det(float3x3(1, 2, 3, 4, 5, 6, 7, 8, 9)));
		Assert::AreEqual(170.f, det(float3x3(8, 9, 10, 2, 13, 4, -1, 8, 2)));

		float3x3 m(1, 2, 3, 9, -3, 1, 0, 8, -2);
		float3x3 n(0, -3, 4, 5, 6, 7, -1, 9, 2);

		Assert::AreEqual(det(m * n), det(m) * det(n));
		Assert::AreEqual(det(5.f * m), std::pow(5.f, 3)* det(m), L"|aM| = a^3 * |M|");
		Assert::AreEqual(det(m), det(transpose(m)));
	}

	TEST_METHOD(equal_operator)
	{
		float3x3 m(0, 1, 2, 3, 4, 5, 6, 7, 8);

		Assert::IsTrue(m != float3x3(100, 1, 2, 3, 4, 5, 6, 7, 8));
		Assert::IsTrue(m != float3x3(0, 100, 2, 3, 4, 5, 6, 7, 8));
		Assert::IsTrue(m != float3x3(0, 1, 100, 3, 4, 5, 6, 7, 8));
		Assert::IsTrue(m != float3x3(0, 1, 2, 100, 4, 5, 6, 7, 8));
		Assert::IsTrue(m != float3x3(0, 1, 2, 3, 100, 5, 6, 7, 8));
		Assert::IsTrue(m != float3x3(0, 1, 2, 3, 4, 100, 6, 7, 8));
		Assert::IsTrue(m != float3x3(0, 1, 2, 3, 4, 5, 100, 7, 8));
		Assert::IsTrue(m != float3x3(0, 1, 2, 3, 4, 5, 6, 100, 8));
		Assert::IsTrue(m != float3x3(0, 1, 2, 3, 4, 5, 6, 7, 100));

		Assert::IsTrue(m == float3x3(0, 1, 2, 3, 4, 5, 6, 7, 8));
	}

	TEST_METHOD(inverse)
	{
		using math::approx_equal;
		using math::inverse;
		using math::transpose;

		Assert::IsTrue(approx_equal(float3x3::identity, inverse(float3x3::identity)));

		float3x3 m(5, 7, -9, 0, 3, 4, 4, 3, 9);
		float3x3 n(4, 5, 6, 7, 9, 8, -7, 6, 1);

		Assert::IsTrue(approx_equal(float3x3::identity, m * inverse(m)));
		Assert::IsTrue(approx_equal(m, inverse(inverse(m))));
		Assert::IsTrue(approx_equal(transpose(inverse(m)), inverse(transpose(m))));
		Assert::IsTrue(approx_equal(inverse(m * n), inverse(n) * inverse(m)));
	}

	TEST_METHOD(is_orthogonal)
	{
		using math::is_orthogonal;

		Assert::IsTrue(is_orthogonal(float3x3::identity));
		Assert::IsFalse(is_orthogonal(float3x3::zero));

		// NOTE(ref2401): The tests are not convincing at all. Try harder...
	}

	TEST_METHOD(mul)
	{
		using math::mul;


		float3x3 m(4, 5, 6, 7, 9, 8, -7, 6, 1);
		float3x3 n(5, 7, -9, 0, 3, 4, 4, 3, 9);
		float3 v(1, 2, 3);

		Assert::AreEqual(float3::zero, mul(float3x3::zero, v));
		Assert::AreEqual(v, mul(float3x3::identity, v));
		Assert::AreEqual(mul(m * n, v), mul(m, mul(n, v)), L"(MN)u == M(Nu)");
		Assert::AreEqual(mul(m + n, v), mul(m, v) + mul(n, v), L"(M + N)u == Mu + Nu");

		float3 v1 = -5.f * mul(m, v);
		float3 v2 = mul(-5.f * m, v);
		float3 v3 = mul(m, -5.f * v);
		Assert::IsTrue(v1 == v2 && v2 == v3);

		float2 u = static_cast<float2>(v);
		Assert::AreEqual(mul(m, v), mul(m, u, v.z));
	}

	TEST_METHOD(ox_oy_oz_and_setters)
	{
		// test getters
		float3x3 m(
			0, 1, 2,
			3, 4, 5,
			6, 7, 8);

		Assert::AreEqual(float3(0, 3, 6), ox(m));
		Assert::AreEqual(float3(1, 4, 7), oy(m));
		Assert::AreEqual(float3(2, 5, 8), oz(m));

		// test setters
		const float3x3 expected_m(
			21, 24, 27,
			22, 25, 28,
			23, 26, 29);

		set_ox(m, float3(21, 22, 23));
		set_oy(m, float3(24, 25, 26));
		set_oz(m, float3(27, 28, 29));
		Assert::AreEqual(expected_m, m);
	}

	TEST_METHOD(static_members)
	{
		Assert::AreEqual(float3x3(1, 0, 0, 0, 1, 0, 0, 0, 1), float3x3::identity);
		Assert::AreEqual(float3x3(), float3x3::zero);
	}

	TEST_METHOD(to_array_column_major_row_major_order)
	{
		using math::to_array_column_major_order;
		using math::to_array_row_major_order;

		float3x3 m(0, 1, 2,
			3, 4, 5,
			6, 7, 8);

		float *p, arr[9];
		constexpr size_t count = std::extent<decltype(arr)>::value;

		// column-major order
		float col[count] = { 0, 3, 6,  1, 4, 7,  2, 5, 8 };

		p = to_array_column_major_order(m, arr);
		Assert::AreEqual<float*>(p, arr);
		Assert::IsTrue(std::equal(col, col + count - 1, arr));

		// row-major order
		float row[count] = { 0, 1, 2,  3, 4, 5,  6, 7, 8 };

		p = to_array_row_major_order(m, arr);
		Assert::AreEqual<float*>(p, arr);
		Assert::IsTrue(std::equal(row, row + count - 1, arr));
	}

	TEST_METHOD(trace)
	{
		using math::trace;
		using math::transpose;

		Assert::AreEqual(0.f, trace(float3x3::zero));
		Assert::AreEqual(3.f, trace(float3x3::identity));

		float3x3 m(0, 1, 2, 3, 4, 5, 6, 7, 8);
		float3x3 l(5, 7, -9, 0, 3, 4, 4, 3, 9);

		Assert::AreEqual(0.f + 4 + 8, trace(m));

		Assert::AreEqual(trace(m * l), trace(l * m));
		Assert::AreEqual(trace(m), trace(transpose(m)));
	}

	TEST_METHOD(transpose)
	{
		using math::transpose;

		Assert::AreEqual(float3x3::zero, transpose(float3x3::zero));
		Assert::AreEqual(float3x3::zero, transpose(float3x3::zero));

		float3x3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
		float3x3 n(4, 5, 6, 7, 9, 8, -7, 6, 1);
		float3x3 mt(1, 4, 7, 2, 5, 8, 3, 6, 9);

		Assert::AreEqual(mt, transpose(m));
		Assert::AreEqual(m, transpose(transpose(m)));

		// transpose properties
		Assert::AreEqual(transpose(5.0f * m), 5.0f * transpose(m));
		Assert::AreEqual(transpose(m + n), transpose(m) + transpose(n));
		Assert::AreEqual(transpose(m * n), transpose(n) * transpose(m), L"(MN)^T == (N)^T * (M)^T");
	}
};

TEST_CLASS(math_matrix_float4x4) {
public:

	TEST_METHOD(approx_equal)
	{
		using math::approx_equal;

		float4x4 m(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);

		Assert::IsFalse(approx_equal(m, float4x4(100, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)));
		Assert::IsFalse(approx_equal(m, float4x4(0, 100, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 100, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 100, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 100, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 100, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 100, 7, 8, 9, 10, 11, 12, 13, 14, 15)));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 100, 8, 9, 10, 11, 12, 13, 14, 15)));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 100, 9, 10, 11, 12, 13, 14, 15)));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 100, 10, 11, 12, 13, 14, 15)));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 100, 11, 12, 13, 14, 15)));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 100, 12, 13, 14, 15)));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 100, 13, 14, 15)));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 100, 14, 15)));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 100, 15)));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 100)));

		Assert::IsTrue(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)));
		Assert::IsTrue(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), 0.0f));

		Assert::IsFalse(approx_equal(m, float4x4(0.0001f, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), 0.0f));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1.0001f, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), 0.0f));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2.0001f, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), 0.0f));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3.0001f, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), 0.0f));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4.0001f, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), 0.0f));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5.0001f, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), 0.0f));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6.0001f, 7, 8, 9, 10, 11, 12, 13, 14, 15), 0.0f));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7.0001f, 8, 9, 10, 11, 12, 13, 14, 15), 0.0f));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8.0001f, 9, 10, 11, 12, 13, 14, 15), 0.0f));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9.0001f, 10, 11, 12, 13, 14, 15), 0.0f));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10.0001f, 11, 12, 13, 14, 15), 0.0f));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11.0001f, 12, 13, 14, 15), 0.0f));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12.0001f, 13, 14, 15), 0.0f));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13.0001f, 14, 15), 0.0f));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14.0001f, 15), 0.0f));
		Assert::IsFalse(approx_equal(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15.0001f), 0.0f));
	}

	TEST_METHOD(assignments)
	{
		float4x4 m(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);

		// copy assignment
		float4x4 mc = m;
		Assert::IsTrue(mc.m00 == m.m00 && mc.m01 == m.m01 && mc.m02 == m.m02 && mc.m03 == m.m03);
		Assert::IsTrue(mc.m10 == m.m10 && mc.m11 == m.m11 && mc.m12 == m.m12 && mc.m13 == m.m13);
		Assert::IsTrue(mc.m20 == m.m20 && mc.m21 == m.m21 && mc.m22 == m.m22 && mc.m23 == m.m23);
		Assert::IsTrue(mc.m30 == m.m30 && mc.m31 == m.m31 && mc.m32 == m.m32 && mc.m33 == m.m33);

		// move assignment

		float4x4 mv;
		mv = std::move(mc);
		Assert::IsTrue(mv.m00 == m.m00 && mv.m01 == m.m01 && mv.m02 == m.m02 && mv.m03 == m.m03);
		Assert::IsTrue(mv.m10 == m.m10 && mv.m11 == m.m11 && mv.m12 == m.m12 && mv.m13 == m.m13);
		Assert::IsTrue(mv.m20 == m.m20 && mv.m21 == m.m21 && mv.m22 == m.m22 && mv.m23 == m.m23);
		Assert::IsTrue(mv.m30 == m.m30 && mv.m31 == m.m31 && mv.m32 == m.m32 && mv.m33 == m.m33);
	}

	TEST_METHOD(binary_operators)
	{
		float4x4 m(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
		float4x4 l(5, 7, -9, 0, 3, 4, 4, 3, 9, 8, 7, 6, 1, 2, 1, 2);
		float4x4 n(4, 5, 6, 7, 9, 8, -7, 6, 1, 2, 3, 4, 0, 0, -3, -4);

		Assert::AreEqual(m + l, float4x4(5, 8, -7, 3, 7, 9, 10, 10, 17, 17, 17, 17, 13, 15, 15, 17));
		Assert::AreEqual(m - l, float4x4(-5, -6, 11, 3, 1, 1, 2, 4, -1, 1, 3, 5, 11, 11, 13, 13));

		Assert::AreEqual(m + l, l + m);
		Assert::AreEqual((m + l) + n, m + (l + n));
		Assert::AreEqual(m, m + float4x4::zero);
		Assert::AreEqual(float4x4::zero, m - m);

		Assert::AreEqual(m * 2, float4x4(0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30));
		Assert::AreEqual(2 * m, float4x4(0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30));
		Assert::AreEqual(m / 2, float4x4(0, 0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 4, 4.5f, 5, 5.5f, 6, 6.5f, 7, 7.5f));

		// matrix product
		Assert::AreEqual(m * float4x4::identity, float4x4::identity * m);
		Assert::AreEqual(float4x4::zero, m * float4x4::zero);
		Assert::AreEqual((l * m) * n, l * (m * n));
		Assert::AreEqual((l + m) * n, (l * n) + (m * n));
		Assert::AreEqual(l * (m + n), (l * m) + (l * n));

		float4x4 mA(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
		float4x4 mB(80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95);
		float4x4 expectedAB(880, 890, 900, 910, 2256, 2282, 2308, 2334, 3632, 3674, 3716, 3758, 5008, 5066, 5124, 5182);
		Assert::AreEqual(expectedAB, mA * mB);
	}

	TEST_METHOD(cast_operator_mat3)
	{
		float4x4 m4(
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 11, 12,
			13, 14, 15, 16);

		float3x3 expected_m3(
			1, 2, 3,
			5, 6, 7,
			9, 10, 11);

		float3x3 m3 = static_cast<float3x3>(m4);
		Assert::AreEqual(expected_m3, m3);
	}

	TEST_METHOD(ctors)
	{
		float4x4 m;
		Assert::IsTrue(m.m00 == 0 && m.m01 == 0 && m.m02 == 0 && m.m03 == 0);
		Assert::IsTrue(m.m10 == 0 && m.m11 == 0 && m.m12 == 0 && m.m13 == 0);
		Assert::IsTrue(m.m20 == 0 && m.m21 == 0 && m.m22 == 0 && m.m23 == 0);
		Assert::IsTrue(m.m30 == 0 && m.m31 == 0 && m.m32 == 0 && m.m33 == 0);

		float4x4 m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
		Assert::IsTrue(m1.m00 == 1 && m1.m01 == 2 && m1.m02 == 3 && m1.m03 == 4);
		Assert::IsTrue(m1.m10 == 5 && m1.m11 == 6 && m1.m12 == 7 && m1.m13 == 8);
		Assert::IsTrue(m1.m20 == 9 && m1.m21 == 10 && m1.m22 == 11 && m1.m23 == 12);
		Assert::IsTrue(m1.m30 == 13 && m1.m31 == 14 && m1.m32 == 15 && m1.m33 == 16);

		// copy ctor
		float4x4 m2 = m1;
		Assert::IsTrue(m2.m00 == m1.m00 && m2.m01 == m1.m01 && m2.m02 == m1.m02 && m2.m03 == m1.m03);
		Assert::IsTrue(m2.m10 == m1.m10 && m2.m11 == m1.m11 && m2.m12 == m1.m12 && m2.m13 == m1.m13);
		Assert::IsTrue(m2.m20 == m1.m20 && m2.m21 == m1.m21 && m2.m22 == m1.m22 && m2.m23 == m1.m23);
		Assert::IsTrue(m2.m30 == m1.m30 && m2.m31 == m1.m31 && m2.m32 == m1.m32 && m2.m33 == m1.m33);

		// move ctor
		float4x4 mm = std::move(m2);
		Assert::IsTrue(mm.m00 == m1.m00 && mm.m01 == m1.m01 && mm.m02 == m1.m02 && mm.m03 == m1.m03);
		Assert::IsTrue(mm.m10 == m1.m10 && mm.m11 == m1.m11 && mm.m12 == m1.m12 && mm.m13 == m1.m13);
		Assert::IsTrue(mm.m20 == m1.m20 && mm.m21 == m1.m21 && mm.m22 == m1.m22 && mm.m23 == m1.m23);
		Assert::IsTrue(mm.m30 == m1.m30 && mm.m31 == m1.m31 && mm.m32 == m1.m32 && mm.m33 == m1.m33);
	}

	TEST_METHOD(compound_assignment_operators)
	{
		// NOTE(ref2401): The test fails on Relase build (x86 & x64).

		using math::approx_equal;

		float4x4 m(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
		float4x4 r(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20);

		(m += r) += r;
		Assert::AreEqual(m, float4x4(
			0 + 5 + 5, 1 + 6 + 6, 2 + 7 + 7, 3 + 8 + 8,
			4 + 9 + 9, 5 + 10 + 10, 6 + 11 + 11, 7 + 12 + 12,
			8 + 13 + 13, 9 + 14 + 14, 10 + 15 + 15, 11 + 16 + 16,
			12 + 17 + 17, 13 + 18 + 18, 14 + 19 + 19, 15 + 20 + 20));

		(m -= r) -= r;
		Assert::AreEqual(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15));

		(m *= 2) *= 3;
		Assert::AreEqual(m, float4x4(
			0, 1 * 6, 2 * 6, 3 * 6,
			4 * 6, 5 * 6, 6 * 6, 7 * 6,
			8 * 6, 9 * 6, 10 * 6, 11 * 6,
			12 * 6, 13 * 6, 14 * 6, 15 * 6));

		(m /= 3) /= 2;
		Assert::AreEqual(m, float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15));

		// matrix product
		float4x4 mA(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
		float4x4 mB(80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95);
		float4x4 expectedAB(880, 890, 900, 910, 2256, 2282, 2308, 2334, 3632, 3674, 3716, 3758, 5008, 5066, 5124, 5182);
		Assert::AreEqual(expectedAB, (mA *= mB));
	}

	TEST_METHOD(det)
	{
		using math::det;
		using math::transpose;

		Assert::AreEqual(0.0f, det(float4x4::zero));
		Assert::AreEqual(1.0f, det(float4x4::identity));
		Assert::AreEqual(0.0f, det(float4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)));
		Assert::AreEqual(5703.0f, det(float4x4(5, 3, -5, 2, 18, 7, -3, 6, 24, -2, 9, 4, 2, 3, 4, 11)));

		float4x4 m(1, 2, 3, 9, -3, 1, 0, 8, -2, 7, -3, 6, 5, 3, -5, 2);
		float4x4 n(0, -3, 4, 5, 6, 7, -1, 9, 2, -16, 4, 9, -1, 0, 5, 8);

		Assert::AreEqual(det(m * n), det(m) * det(n));
		Assert::AreEqual(det(5.0f * m), std::pow(5.0f, 4) * det(m), L"|aM| = a^4 * |M|");
		Assert::AreEqual(det(m), det(transpose(m)));
	}

	TEST_METHOD(equal_operator)
	{
		float4x4 m(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);

		Assert::IsTrue(m != float4x4(100, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15));
		Assert::IsTrue(m != float4x4(0, 100, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15));
		Assert::IsTrue(m != float4x4(0, 1, 100, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15));
		Assert::IsTrue(m != float4x4(0, 1, 2, 100, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15));
		Assert::IsTrue(m != float4x4(0, 1, 2, 3, 100, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15));
		Assert::IsTrue(m != float4x4(0, 1, 2, 3, 4, 100, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15));
		Assert::IsTrue(m != float4x4(0, 1, 2, 3, 4, 5, 100, 7, 8, 9, 10, 11, 12, 13, 14, 15));
		Assert::IsTrue(m != float4x4(0, 1, 2, 3, 4, 5, 6, 100, 8, 9, 10, 11, 12, 13, 14, 15));
		Assert::IsTrue(m != float4x4(0, 1, 2, 3, 4, 5, 6, 7, 100, 9, 10, 11, 12, 13, 14, 15));
		Assert::IsTrue(m != float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 100, 10, 11, 12, 13, 14, 15));
		Assert::IsTrue(m != float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 100, 11, 12, 13, 14, 15));
		Assert::IsTrue(m != float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 100, 12, 13, 14, 15));
		Assert::IsTrue(m != float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 100, 13, 14, 15));
		Assert::IsTrue(m != float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 100, 14, 15));
		Assert::IsTrue(m != float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 100, 15));
		Assert::IsTrue(m != float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 100));

		Assert::IsTrue(m == float4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15));
	}

	TEST_METHOD(inverse)
	{
		using math::approx_equal;
		using math::inverse;
		using math::transpose;

		Assert::IsTrue(approx_equal(float4x4::identity, inverse(float4x4::identity)));

		float4x4 m(5, 7, -9, 0, 3, 4, 4, 3, 9, 8, 7, 6, 1, 2, 1, 2);
		float4x4 n(4, 5, 6, 7, 9, 8, -7, 6, 1, 2, 3, 4, 0, 0, -3, -4);

		Assert::IsTrue(approx_equal(float4x4::identity, m * inverse(m)));
		Assert::IsTrue(approx_equal(m, inverse(inverse(m))));
		Assert::IsTrue(approx_equal(transpose(inverse(m)), inverse(transpose(m))));
		Assert::IsTrue(approx_equal(inverse(m * n), inverse(n) * inverse(m)));
	}

	TEST_METHOD(is_orthogonal)
	{
		using math::is_orthogonal;

		Assert::IsTrue(is_orthogonal(float4x4::identity));
		Assert::IsFalse(is_orthogonal(float4x4::zero));

		// NOTE(ref2401): The tests are not convincing at all. Try harder...
	}

	TEST_METHOD(mul)
	{
		using math::mul;


		float4x4 m(4, 5, 6, 7, 9, 8, -7, 6, 1, 2, 3, 4, 0, 0, -3, -4);
		float4x4 n(5, 7, -9, 0, 3, 4, 4, 3, 9, 8, 7, 6, 1, 2, 1, 2);
		float4 v(1, 2, 3, 4);

		Assert::AreEqual(float4::zero, mul(float4x4::zero, v));
		Assert::AreEqual(v, mul(float4x4::identity, v));
		Assert::AreEqual(mul(m * n, v), mul(m, mul(n, v)), L"(MN)u == M(Nu)");
		Assert::AreEqual(mul(m + n, v), mul(m, v) + mul(n, v), L"(M + N)u == Mu + Nu");

		float4 v1 = -5.f * mul(m, v);
		float4 v2 = mul(-5.f * m, v);
		float4 v3 = mul(m, -5.f * v);
		Assert::IsTrue(v1 == v2 && v2 == v3);

		float2 u2 = static_cast<float2>(v);
		float3 u3 = static_cast<float3>(v);
		auto res2 = mul(m, u2, v.z, v.w);
		auto res3 = mul(m, u3, v.w);
		auto res4 = mul(m, v);
		Assert::IsTrue(res2 == res3 && res3 == res4);
	}

	TEST_METHOD(ox_oy_oz_and_setters)
	{
		// test getters
		float4x4 m(
			0, 1, 2, 3,
			4, 5, 6, 7,
			8, 9, 10, 11,
			12, 13, 14, 15);

		Assert::AreEqual(float3(0, 4, 8), ox(m));
		Assert::AreEqual(float3(1, 5, 9), oy(m));
		Assert::AreEqual(float3(2, 6, 10), oz(m));

		// test setters
		const float4x4 expected_m(
			21, 24, 27, 3, 
			22, 25, 28, 7, 
			23, 26, 29, 11, 
			12, 13, 14, 15);

		set_ox(m, float3(21, 22, 23));
		set_oy(m, float3(24, 25, 26));
		set_oz(m, float3(27, 28, 29));
		Assert::AreEqual(expected_m, m);
	}

	TEST_METHOD(put_in_column_major_row_major_order)
	{
		using math::to_array_column_major_order;
		using math::to_array_row_major_order;

		float4x4 m(0, 1, 2, 3,
			4, 5, 6, 7,
			8, 9, 10, 11,
			12, 13, 14, 15);

		float *p, arr[16];
		constexpr size_t count = std::extent<decltype(arr)>::value;

		// column-major order
		float col[count] = { 0, 4, 8, 12,  1, 5, 9, 13,  2, 6, 10, 14,  3, 7, 11, 15 };

		p = to_array_column_major_order(m, arr);
		Assert::AreEqual<float*>(p, arr);
		Assert::IsTrue(std::equal(col, col + count - 1, arr));

		// row-major order
		float row[count] = { 0, 1, 2, 3,  4, 5, 6, 7,  8, 9, 10, 11,  12, 13, 14, 15 };

		p = to_array_row_major_order(m, arr);
		Assert::AreEqual<float*>(p, arr);
		Assert::IsTrue(std::equal(row, row + count - 1, arr));
	}

	TEST_METHOD(static_members)
	{
		Assert::AreEqual(float4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1), float4x4::identity);
		Assert::AreEqual(float4x4(), float4x4::zero);
	}

	TEST_METHOD(trace)
	{
		using math::trace;
		using math::transpose;

		Assert::AreEqual(0.f, trace(float4x4::zero));
		Assert::AreEqual(4.f, trace(float4x4::identity));

		float4x4 m(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
		float4x4 l(5, 7, -9, 0, 3, 4, 4, 3, 9, 8, 7, 6, 1, 2, 1, 2);

		Assert::AreEqual(0.f + 5 + 10 + 15, trace(m));

		Assert::AreEqual(trace(m * l), trace(l * m));
		Assert::AreEqual(trace(m), trace(transpose(m)));
	}

	TEST_METHOD(transpose)
	{
		using math::transpose;

		Assert::AreEqual(float4x4::zero, transpose(float4x4::zero));
		Assert::AreEqual(float4x4::zero, transpose(float4x4::zero));

		float4x4 m(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
		float4x4 n(4, 5, 6, 7, 9, 8, -7, 6, 1, 2, 3, 4, 0, 0, -3, -4);
		float4x4 mt(1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16);

		Assert::AreEqual(mt, transpose(m));
		Assert::AreEqual(m, transpose(transpose(m)));

		// transpose properties
		Assert::AreEqual(transpose(5.f * m), 5.f * transpose(m));
		Assert::AreEqual(transpose(m + n), transpose(m) + transpose(n));
		Assert::AreEqual(transpose(m * n), transpose(n) * transpose(m), L"(MN)^T == (N)^T * (M)^T");
	}
};

} // namespace unittest
