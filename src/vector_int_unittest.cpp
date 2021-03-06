#include "math/vector_int.h"

#include <utility>
#include "CppUnitTest.h"

using math::int2;
using math::int3;
using math::int4;
using math::uint2;
using math::uint3;
using math::uint4;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

template<> inline std::wstring ToString<int2>(const int2& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<int3>(const int3& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<int4>(const int4& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<uint2>(const uint2& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<uint3>(const uint3& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<uint4>(const uint4& t) { RETURN_WIDE_STRING(t); }

}}} // namespace Microsoft::VisualStudio::CppUnitTestFramework


namespace unittest {

TEST_CLASS(math_vector_int_int2) {
public:

	TEST_METHOD(area)
	{
		using math::area;

		Assert::AreEqual<int32_t>(0, area(int2::zero));
		Assert::AreEqual<int32_t>(20, area(int2(4, 5)));
	}

	TEST_METHOD(arithmetic_operators)
	{
		int2 v(1, 2);
		int2 vo(5, 6);
		Assert::AreEqual(v + 1, int2(2, 3));
		Assert::AreEqual(1 + v, int2(2, 3));
		Assert::AreEqual(v + vo, int2(6, 8));

		Assert::AreEqual(v - 1, int2(0, 1));
		Assert::AreEqual(1 - v, int2(0, -1));
		Assert::AreEqual(v - vo, int2(-4));

		Assert::AreEqual(v * 2, int2(2, 4));
		Assert::AreEqual(2 * v, int2(2, 4));
		Assert::AreEqual(v * vo, int2(5, 12));

		Assert::AreEqual(v * 2, int2(2, 4));
		Assert::AreEqual(2 * v, int2(2, 4));
		Assert::AreEqual(v * vo, int2(5, 12));

		Assert::AreEqual(v / 2, int2(0, 1));
		Assert::AreEqual(10 / v, int2(10, 5));
		Assert::AreEqual(vo / v, int2(5, 3));
	}

	TEST_METHOD(aspect_ration)
	{
		using math::aspect_ratio;

		Assert::AreEqual(1.5f, aspect_ratio(int2(3, 2)));
	}

	TEST_METHOD(assignment_operators)
	{
		int2 v(5, 6);

		// copy assignment
		int2 vc;
		vc = v;
		Assert::IsTrue((vc.x == v.x) && (vc.y == v.y));

		// move assignment
		int2 vm;
		vm = std::move(v);
		Assert::IsTrue((vm.x == v.x) && (vm.y == v.y));
	}

	TEST_METHOD(clamp)
	{
		using math::clamp;

		int2 lo(-5, -7);
		int2 hi(5, 7);
		int2 v(2, 3);

		Assert::AreEqual(lo, clamp(int2(-9, -10), lo, hi));
		Assert::AreEqual(v, clamp(v, lo, hi));
		Assert::AreEqual(hi, clamp(int2(9, 10), lo, hi));
	}

	TEST_METHOD(compound_assignment_operators)
	{
		int2 v(1, 2);
		(v += 5) += 5;
		Assert::AreEqual(int2(11, 12), v);

		(v -= 7) -= 3;
		Assert::AreEqual(int2(1, 2), v);

		(v *= 2) *= 3;
		Assert::AreEqual(int2(6, 12), v);

		(v /= 3) /= 2;
		Assert::AreEqual(int2(1, 2), v);

		(v += v) += v;
		Assert::AreEqual(int2(4, 8), v);

		v -= v;
		Assert::AreEqual(int2::zero, v);
	}

	TEST_METHOD(ctors)
	{
		int2 v0;
		Assert::IsTrue((v0.x == 0) && (v0.y == 0));

		int2 v1(24);
		Assert::IsTrue((v1.x == 24) && (v1.y == 24));

		int2 v4(1, 2);
		Assert::IsTrue((v4.x == 1) && (v4.y == 2));

		// copy ctor
		int2 vc = v4;
		Assert::IsTrue((vc.x == v4.x) && (vc.y == v4.y));

		// move ctor
		int2 vm = std::move(v4);
		Assert::IsTrue((vm.x == vc.x) && (vm.y == vc.y));
	}

	TEST_METHOD(equal_operator)
	{
		int2 v(1, 2);

		Assert::AreNotEqual(v, int2(100, 2));
		Assert::AreNotEqual(v, int2(1, 100));

		Assert::AreEqual(v, v);
		Assert::AreEqual(v, int2(1, 2));
	}

	TEST_METHOD(rational_operators)
	{
		// operator <
		Assert::IsFalse(int2(6, 1) < 6);
		Assert::IsFalse(int2(7, 1) < 6);
		Assert::IsFalse(int2(1, 6) < 6);
		Assert::IsFalse(int2(1, 7) < 6);
		Assert::IsTrue(int2(1, 2) < 6);

		// operator <=
		Assert::IsFalse(int2(7, 1) <= 6);
		Assert::IsFalse(int2(1, 7) <= 6);
		Assert::IsTrue(int2(1, 2) <= 6);
		Assert::IsTrue(int2(6, 1) <= 6);
		Assert::IsTrue(int2(1, 6) <= 6);

		// operator >
		Assert::IsFalse(int2(0, 4) > 1);
		Assert::IsFalse(int2(1, 4) > 1);
		Assert::IsFalse(int2(4, 0) > 1);
		Assert::IsFalse(int2(4, 1) > 1);
		Assert::IsTrue(int2(4, 5) > 1);

		// operator >=
		Assert::IsFalse(int2(0, 4) >= 1);
		Assert::IsFalse(int2(4, 0) >= 1);
		Assert::IsTrue(int2(4, 5) >= 1);
		Assert::IsTrue(int2(1, 4) >= 1);
		Assert::IsTrue(int2(4, 1) >= 1);
	}

	TEST_METHOD(static_members)
	{
		Assert::AreEqual(int2(1, 0), int2::unit_x);
		Assert::AreEqual(int2(0, 1), int2::unit_y);
		Assert::AreEqual(int2(1, 1), int2::unit_xy);
		Assert::AreEqual(int2(0, 0), int2::zero);
	}

	TEST_METHOD(unary_minus_operator)
	{
		Assert::AreEqual(int2(0), -(-int2(0)));
		Assert::AreEqual(int2(1), -(-int2(1)));
		Assert::AreEqual(int2(1, -2), -int2(-1, 2));
		Assert::AreEqual(int2(-1, 2), -int2(1, -2));
	}
};

TEST_CLASS(math_vector_int_int3) {
public:

	TEST_METHOD(area)
	{
		using math::area;

		Assert::AreEqual<int32_t>(0, area(int3::zero));
		Assert::AreEqual<int32_t>(20, area(int3(4, 5, 6)));
	}

	TEST_METHOD(arithmetic_operators)
	{
		int3 v(1, 2, 3);
		int3 vo(5, 6, 7);
		Assert::AreEqual(v + 1, int3(2, 3, 4));
		Assert::AreEqual(1 + v, int3(2, 3, 4));
		Assert::AreEqual(v + vo, int3(6, 8, 10));

		Assert::AreEqual(v - 1, int3(0, 1, 2));
		Assert::AreEqual(1 - v, int3(0, -1, -2));
		Assert::AreEqual(v - vo, int3(-4));

		Assert::AreEqual(v * 2, int3(2, 4, 6));
		Assert::AreEqual(2 * v, int3(2, 4, 6));
		Assert::AreEqual(v * vo, int3(5, 12, 21));

		Assert::AreEqual(v * 2, int3(2, 4, 6));
		Assert::AreEqual(2 * v, int3(2, 4, 6));
		Assert::AreEqual(v * vo, int3(5, 12, 21));

		Assert::AreEqual(v / 2, int3(0, 1, 1));
		Assert::AreEqual(10 / v, int3(10, 5, 3));
		Assert::AreEqual(vo / v, int3(5, 3, 2));
	}

	TEST_METHOD(assignment_operators)
	{
		int3 v(5, 6, 7);

		// copy assignment
		int3 vc;
		vc = v;
		Assert::IsTrue((vc.x == v.x) && (vc.y == v.y) && (vc.z == v.z));

		// move assignment
		int3 vm;
		vm = std::move(v);
		Assert::IsTrue((vm.x == v.x) && (vm.y == v.y) && (vm.z == v.z));
	}

	TEST_METHOD(clamp)
	{
		using math::clamp;

		int3 lo(-5, -7, -9);
		int3 hi(5, 7, 9);
		int3 v(2, 3, 4);

		Assert::AreEqual(lo, clamp(int3(-9, -10, -11), lo, hi));
		Assert::AreEqual(v, clamp(v, lo, hi));
		Assert::AreEqual(hi, clamp(int3(9, 10, 11), lo, hi));
	}

	TEST_METHOD(compound_assignment_operators)
	{
		int3 v(1, 2, 3);
		(v += 5) += 5;
		Assert::AreEqual(int3(11, 12, 13), v);

		(v -= 7) -= 3;
		Assert::AreEqual(int3(1, 2, 3), v);

		(v *= 2) *= 3;
		Assert::AreEqual(int3(6, 12, 18), v);

		(v /= 3) /= 2;
		Assert::AreEqual(int3(1, 2, 3), v);

		(v += v) += v;
		Assert::AreEqual(int3(4, 8, 12), v);

		v -= v;
		Assert::AreEqual(int3::zero, v);
	}

	TEST_METHOD(conversion_operators_xy)
	{
		int3 v(1, 2, 3);

		Assert::AreEqual(int2(1, 2), xy(v));

		Assert::AreEqual(int2(1, 2), static_cast<int2>(v));
	}

	TEST_METHOD(ctors)
	{
		int3 v0;
		Assert::IsTrue((v0.x == 0) && (v0.y == 0) && (v0.z == 0));

		int3 v1(24);
		Assert::IsTrue((v1.x == 24) && (v1.y == 24) && (v1.z == 24));

		int2 v2(1, 2);
		int3 v1_2(v2, 3);
		Assert::IsTrue((v1_2.x == 1) && (v1_2.y == 2) && (v1_2.z == 3));

		int3 v4(1, 2, 3);
		Assert::IsTrue((v4.x == 1) && (v4.y == 2) && (v4.z == 3));

		// copy ctor
		int3 vc = v4;
		Assert::IsTrue((vc.x == v4.x) && (vc.y == v4.y) && (vc.z == v4.z));

		// move ctor
		int3 vm = std::move(v4);
		Assert::IsTrue((vm.x == vc.x) && (vm.y == vc.y) && (vm.z == vc.z));
	}

	TEST_METHOD(equal_operator)
	{
		int3 v(1, 2, 3);

		Assert::AreNotEqual(v, int3(100, 2, 3));
		Assert::AreNotEqual(v, int3(1, 100, 3));
		Assert::AreNotEqual(v, int3(1, 2, 100));

		Assert::AreEqual(v, v);
		Assert::AreEqual(v, int3(1, 2, 3));
	}

	TEST_METHOD(rational_operators)
	{
		// operator <
		Assert::IsFalse(int3(6, 1, 2) < 6);
		Assert::IsFalse(int3(7, 1, 2) < 6);
		Assert::IsFalse(int3(1, 6, 2) < 6);
		Assert::IsFalse(int3(1, 7, 2) < 6);
		Assert::IsFalse(int3(1, 2, 6) < 6);
		Assert::IsFalse(int3(1, 2, 7) < 6);
		Assert::IsTrue(int3(1, 2, 3) < 6);

		// operator <=
		Assert::IsFalse(int3(7, 1, 2) <= 6);
		Assert::IsFalse(int3(1, 7, 2) <= 6);
		Assert::IsFalse(int3(1, 2, 7) <= 6);
		Assert::IsTrue(int3(1, 2, 3) <= 6);
		Assert::IsTrue(int3(6, 1, 2) <= 6);
		Assert::IsTrue(int3(1, 6, 2) <= 6);
		Assert::IsTrue(int3(1, 2, 6) <= 6);

		// operator >
		Assert::IsFalse(int3(0, 4, 5) > 1);
		Assert::IsFalse(int3(1, 4, 5) > 1);
		Assert::IsFalse(int3(4, 0, 5) > 1);
		Assert::IsFalse(int3(4, 1, 5) > 1);
		Assert::IsFalse(int3(4, 5, 0) > 1);
		Assert::IsFalse(int3(4, 5, 1) > 1);
		Assert::IsTrue(int3(4, 5, 6) > 1);

		// operator >=
		Assert::IsFalse(int3(0, 4, 5) >= 1);
		Assert::IsFalse(int3(4, 0, 5) >= 1);
		Assert::IsFalse(int3(4, 5, 0) >= 1);
		Assert::IsTrue(int3(1, 4, 5) >= 1);
		Assert::IsTrue(int3(4, 1, 5) >= 1);
		Assert::IsTrue(int3(4, 5, 1) >= 1);
		Assert::IsTrue(int3(4, 5, 6) >= 1);
	}

	TEST_METHOD(static_members)
	{
		Assert::AreEqual(int3(1, 0, 0), int3::unit_x);
		Assert::AreEqual(int3(0, 1, 0), int3::unit_y);
		Assert::AreEqual(int3(0, 0, 1), int3::unit_z);
		Assert::AreEqual(int3(1, 1, 1), int3::unit_xyz);
		Assert::AreEqual(int3(0, 0, 0), int3::zero);
	}

	TEST_METHOD(unary_minus_operator)
	{
		Assert::AreEqual(int3(0), -(-int3(0)));
		Assert::AreEqual(int3(1), -(-int3(1)));
		Assert::AreEqual(int3(1, -2, -3), -int3(-1, 2, 3));
		Assert::AreEqual(int3(-1, 2, -3), -int3(1, -2, 3));
		Assert::AreEqual(int3(-1, -2, 3), -int3(1, 2, -3));
		Assert::AreEqual(int3(-1, -2, -3), -int3(1, 2, 3));
	}

	TEST_METHOD(volume)
	{
		using math::volume;

		Assert::AreEqual<int32_t>(0, volume(int3::zero));
		Assert::AreEqual<int32_t>(120, volume(int3(4, 5, 6)));
	}
};

TEST_CLASS(math_vector_int_int4) {
public:

	TEST_METHOD(area)
	{
		using math::area;

		Assert::AreEqual<int32_t>(0, area(int4::zero));
		Assert::AreEqual<int32_t>(20, area(int4(4, 5, 6, 7)));
	}

	TEST_METHOD(arithmetic_operators)
	{
		int4 v(1, 2, 3, 4);
		int4 vo(5, 6, 7, 8);
		Assert::AreEqual(v + 1, int4(2, 3, 4, 5));
		Assert::AreEqual(1 + v, int4(2, 3, 4, 5));
		Assert::AreEqual(v + vo, int4(6, 8, 10, 12));

		Assert::AreEqual(v - 1, int4(0, 1, 2, 3));
		Assert::AreEqual(1 - v, int4(0, -1, -2, -3));
		Assert::AreEqual(v - vo, int4(-4));

		Assert::AreEqual(v * 2, int4(2, 4, 6, 8));
		Assert::AreEqual(2 * v, int4(2, 4, 6, 8));
		Assert::AreEqual(v * vo, int4(5, 12, 21, 32));

		Assert::AreEqual(v * 2, int4(2, 4, 6, 8));
		Assert::AreEqual(2 * v, int4(2, 4, 6, 8));
		Assert::AreEqual(v * vo, int4(5, 12, 21, 32));

		Assert::AreEqual(v / 2, int4(0, 1, 1, 2));
		Assert::AreEqual(10 / v, int4(10, 5, 3, 2));
		Assert::AreEqual(vo / v, int4(5, 3, 2, 2));
	}

	TEST_METHOD(assignment_operators)
	{
		int4 v(5, 6, 7, 8);

		// copy assignment
		int4 vc;
		vc = v;
		Assert::IsTrue((vc.x == v.x) && (vc.y == v.y) && (vc.z == v.z) && (vc.w == v.w));

		// move assignment
		int4 vm;
		vm = std::move(v);
		Assert::IsTrue((vm.x == v.x) && (vm.y == v.y) && (vm.z == v.z) && (vm.w == v.w));
	}

	TEST_METHOD(clamp)
	{
		using math::clamp;

		int4 lo(-5, -7, -9, -11);
		int4 hi(5, 7, 9, 11);
		int4 v(2, 3, 4, 5);

		Assert::AreEqual(lo, clamp(int4(-9, -10, -11, -12), lo, hi));
		Assert::AreEqual(v, clamp(v, lo, hi));
		Assert::AreEqual(hi, clamp(int4(9, 10, 11, 12), lo, hi));
	}

	TEST_METHOD(compound_assignment_operators)
	{
		int4 v(1, 2, 3, 4);
		(v += 5) += 5;
		Assert::AreEqual(int4(11, 12, 13, 14), v);

		(v -= 7) -= 3;
		Assert::AreEqual(int4(1, 2, 3, 4), v);

		(v *= 2) *= 3;
		Assert::AreEqual(int4(6, 12, 18, 24), v);

		(v /= 3) /= 2;
		Assert::AreEqual(int4(1, 2, 3, 4), v);

		(v += v) += v;
		Assert::AreEqual(int4(4, 8, 12, 16), v);

		v -= v;
		Assert::AreEqual(int4::zero, v);
	}

	TEST_METHOD(conversion_operators_xy_xyz)
	{
		int4 v(1, 2, 3, 4);

		Assert::AreEqual(int2(1, 2), xy(v));
		Assert::AreEqual(int3(1, 2, 3), xyz(v));

		Assert::AreEqual(int2(1, 2), static_cast<int2>(v));
		Assert::AreEqual(int3(1, 2, 3), static_cast<int3>(v));
	}

	TEST_METHOD(ctors)
	{
		int4 v0;
		Assert::IsTrue((v0.x == 0) && (v0.y == 0) && (v0.z == 0) && (v0.w == 0));

		int4 v1(24);
		Assert::IsTrue((v1.x == 24) && (v1.y == 24) && (v1.z == 24) && (v1.w == 24));

		int2 v2(1, 2);
		int4 v1_2(v2, 3, 4);
		Assert::IsTrue((v1_2.x == 1) && (v1_2.y == 2) && (v1_2.z == 3) && (v1_2.w == 4));

		int3 v3(1, 2, 3);
		int4 v1_3(v3, 4);
		Assert::IsTrue((v1_3.x == 1) && (v1_3.y == 2) && (v1_3.z == 3) && (v1_3.w == 4));

		int4 v4(1, 2, 3, 4);
		Assert::IsTrue((v4.x == 1) && (v4.y == 2) && (v4.z == 3) && (v4.w == 4));

		// copy ctor
		int4 vc = v4;
		Assert::IsTrue((vc.x == v4.x) && (vc.y == v4.y) && (vc.z == v4.z) && (vc.w == v4.w));

		// move ctor
		int4 vm = std::move(v4);
		Assert::IsTrue((vm.x == vc.x) && (vm.y == vc.y) && (vm.z == vc.z) && (vm.w == vc.w));
	}

	TEST_METHOD(equal_operator)
	{
		int4 v(1, 2, 3, 4);

		Assert::AreNotEqual(v, int4(100, 2, 3, 4));
		Assert::AreNotEqual(v, int4(1, 100, 3, 4));
		Assert::AreNotEqual(v, int4(1, 2, 100, 4));
		Assert::AreNotEqual(v, int4(1, 2, 3, 100));

		Assert::AreEqual(v, v);
		Assert::AreEqual(v, int4(1, 2, 3, 4));
	}

	TEST_METHOD(rational_operators)
	{
		// operator <
		Assert::IsFalse(int4(6, 1, 2, 3) < 6);
		Assert::IsFalse(int4(7, 1, 2, 3) < 6);
		Assert::IsFalse(int4(1, 6, 2, 3) < 6);
		Assert::IsFalse(int4(1, 7, 2, 3) < 6);
		Assert::IsFalse(int4(1, 2, 6, 3) < 6);
		Assert::IsFalse(int4(1, 2, 7, 3) < 6);
		Assert::IsFalse(int4(1, 2, 3, 6) < 6);
		Assert::IsFalse(int4(1, 2, 3, 7) < 6);
		Assert::IsTrue(int4(1, 2, 3, 4) < 6);

		// operator <=
		Assert::IsFalse(int4(7, 1, 2, 3) <= 6);
		Assert::IsFalse(int4(1, 7, 2, 3) <= 6);
		Assert::IsFalse(int4(1, 2, 7, 3) <= 6);
		Assert::IsFalse(int4(1, 2, 3, 7) <= 6);
		Assert::IsTrue(int4(1, 2, 3, 4) <= 6);
		Assert::IsTrue(int4(6, 1, 2, 3) <= 6);
		Assert::IsTrue(int4(1, 6, 2, 3) <= 6);
		Assert::IsTrue(int4(1, 2, 6, 3) <= 6);
		Assert::IsTrue(int4(1, 2, 3, 6) <= 6);

		// operator >
		Assert::IsFalse(int4(0, 4, 5, 6) > 1);
		Assert::IsFalse(int4(1, 4, 5, 6) > 1);
		Assert::IsFalse(int4(4, 0, 5, 6) > 1);
		Assert::IsFalse(int4(4, 1, 5, 6) > 1);
		Assert::IsFalse(int4(4, 5, 0, 6) > 1);
		Assert::IsFalse(int4(4, 5, 1, 6) > 1);
		Assert::IsFalse(int4(4, 5, 6, 0) > 1);
		Assert::IsFalse(int4(4, 5, 6, 1) > 1);
		Assert::IsTrue(int4(4, 5, 6, 7) > 1);

		// operator >=
		Assert::IsFalse(int4(0, 4, 5, 6) >= 1);
		Assert::IsFalse(int4(4, 0, 5, 6) >= 1);
		Assert::IsFalse(int4(4, 5, 0, 6) >= 1);
		Assert::IsFalse(int4(4, 5, 6, 0) >= 1);
		Assert::IsTrue(int4(4, 5, 6, 7) >= 1);
		Assert::IsTrue(int4(1, 4, 5, 6) >= 1);
		Assert::IsTrue(int4(4, 1, 5, 6) >= 1);
		Assert::IsTrue(int4(4, 5, 1, 6) >= 1);
		Assert::IsTrue(int4(4, 5, 6, 1) >= 1);
	}

	TEST_METHOD(static_members)
	{
		Assert::AreEqual(int4(1, 0, 0, 0), int4::unit_x);
		Assert::AreEqual(int4(0, 1, 0, 0), int4::unit_y);
		Assert::AreEqual(int4(0, 0, 1, 0), int4::unit_z);
		Assert::AreEqual(int4(0, 0, 0, 1), int4::unit_w);
		Assert::AreEqual(int4(1, 1, 1, 1), int4::unit_xyzw);
		Assert::AreEqual(int4(0, 0, 0, 0), int4::zero);
	}

	TEST_METHOD(unary_minus_operator)
	{
		Assert::AreEqual(int4(0), -(-int4(0)));
		Assert::AreEqual(int4(1), -(-int4(1)));
		Assert::AreEqual(int4(1, -2, -3, -4), -int4(-1, 2, 3, 4));
		Assert::AreEqual(int4(-1, 2, -3, -4), -int4(1, -2, 3, 4));
		Assert::AreEqual(int4(-1, -2, 3, -4), -int4(1, 2, -3, 4));
		Assert::AreEqual(int4(-1, -2, -3, 4), -int4(1, 2, 3, -4));
	}

	TEST_METHOD(volume)
	{
		using math::volume;

		Assert::AreEqual<int32_t>(0, volume(int4::zero));
		Assert::AreEqual<int32_t>(120, volume(int4(4, 5, 6, 7)));
	}
};

TEST_CLASS(math_vector_int_uint2) {
public:

	TEST_METHOD(area)
	{
		using math::area;

		Assert::AreEqual<uint32_t>(0, area(uint2::zero));
		Assert::AreEqual<uint32_t>(20, area(uint2(4, 5)));
	}

	TEST_METHOD(arithmetic_operators)
	{
		uint2 v(1, 2);
		uint2 vo(5, 6);
		Assert::AreEqual(v + 1u, uint2(2, 3));
		Assert::AreEqual(1u + v, uint2(2, 3));
		Assert::AreEqual(v + vo, uint2(6, 8));

		Assert::AreEqual(v - 1u, uint2(0, 1));
		Assert::AreEqual(10u - v, uint2(9, 8));
		Assert::AreEqual(vo - v, uint2(4));

		Assert::AreEqual(v * 2u, uint2(2, 4));
		Assert::AreEqual(2u * v, uint2(2, 4));
		Assert::AreEqual(v * vo, uint2(5, 12));

		Assert::AreEqual(v * 2u, uint2(2, 4));
		Assert::AreEqual(2u * v, uint2(2, 4));
		Assert::AreEqual(v * vo, uint2(5, 12));

		Assert::AreEqual(v / 2u, uint2(0, 1));
		Assert::AreEqual(10u / v, uint2(10, 5));
		Assert::AreEqual(vo / v, uint2(5, 3));
	}

	TEST_METHOD(aspect_ration)
	{
		using math::aspect_ratio;

		Assert::AreEqual(1.5f, aspect_ratio(uint2(3, 2)));
	}

	TEST_METHOD(assignment_operators)
	{
		uint2 v(5, 6);

		// copy assignment
		uint2 vc;
		vc = v;
		Assert::IsTrue((vc.x == v.x) && (vc.y == v.y));

		// move assignment
		uint2 vm;
		vm = std::move(v);
		Assert::IsTrue((vm.x == v.x) && (vm.y == v.y));
	}

	TEST_METHOD(clamp)
	{
		using math::clamp;

		const uint2 lo(1, 2);
		const uint2 hi(11, 12);
		const uint2 v(2, 3);

		Assert::AreEqual(lo, clamp(uint2::zero, lo, hi));
		Assert::AreEqual(v, clamp(v, lo, hi));
		Assert::AreEqual(hi, clamp(uint2(42), lo, hi));
	}

	TEST_METHOD(compound_assignment_operators)
	{
		uint2 v(1, 2);
		(v += 5) += 5;
		Assert::AreEqual(uint2(11, 12), v);

		(v -= 7) -= 3;
		Assert::AreEqual(uint2(1, 2), v);

		(v *= 2) *= 3;
		Assert::AreEqual(uint2(6, 12), v);

		(v /= 3) /= 2;
		Assert::AreEqual(uint2(1, 2), v);

		(v += v) += v;
		Assert::AreEqual(uint2(4, 8), v);

		v -= v;
		Assert::AreEqual(uint2::zero, v);
	}

	TEST_METHOD(ctors)
	{
		uint2 v0;
		Assert::IsTrue((v0.x == 0) && (v0.y == 0));

		uint2 v1(24);
		Assert::IsTrue((v1.x == 24) && (v1.y == 24));

		uint2 v4(1, 2);
		Assert::IsTrue((v4.x == 1) && (v4.y == 2));

		// copy ctor
		uint2 vc = v4;
		Assert::IsTrue((vc.x == v4.x) && (vc.y == v4.y));

		// move ctor
		uint2 vm = std::move(v4);
		Assert::IsTrue((vm.x == vc.x) && (vm.y == vc.y));
	}

	TEST_METHOD(equal_operator)
	{
		uint2 v(1, 2);

		Assert::AreNotEqual(v, uint2(100, 2));
		Assert::AreNotEqual(v, uint2(1, 100));

		Assert::AreEqual(v, v);
		Assert::AreEqual(v, uint2(1, 2));
	}

	TEST_METHOD(rational_operators)
	{
		// operator <
		Assert::IsFalse(uint2(6, 1) < 6);
		Assert::IsFalse(uint2(7, 1) < 6);
		Assert::IsFalse(uint2(1, 6) < 6);
		Assert::IsFalse(uint2(1, 7) < 6);
		Assert::IsTrue(uint2(1, 2) < 6);

		// operator <=
		Assert::IsFalse(uint2(7, 1) <= 6);
		Assert::IsFalse(uint2(1, 7) <= 6);
		Assert::IsTrue(uint2(1, 2) <= 6);
		Assert::IsTrue(uint2(6, 1) <= 6);
		Assert::IsTrue(uint2(1, 6) <= 6);

		// operator >
		Assert::IsFalse(uint2(0, 4) > 1);
		Assert::IsFalse(uint2(1, 4) > 1);
		Assert::IsFalse(uint2(4, 0) > 1);
		Assert::IsFalse(uint2(4, 1) > 1);
		Assert::IsTrue(uint2(4, 5) > 1);

		// operator >=
		Assert::IsFalse(uint2(0, 4) >= 1);
		Assert::IsFalse(uint2(4, 0) >= 1);
		Assert::IsTrue(uint2(4, 5) >= 1);
		Assert::IsTrue(uint2(1, 4) >= 1);
		Assert::IsTrue(uint2(4, 1) >= 1);
	}

	TEST_METHOD(static_members)
	{
		Assert::AreEqual(uint2(1, 0), uint2::unit_x);
		Assert::AreEqual(uint2(0, 1), uint2::unit_y);
		Assert::AreEqual(uint2(1, 1), uint2::unit_xy);
		Assert::AreEqual(uint2(0, 0), uint2::zero);
	}
};

TEST_CLASS(math_vector_int_uint3) {
public:

	TEST_METHOD(area)
	{
		using math::area;

		Assert::AreEqual<uint32_t>(0, area(uint3::zero));
		Assert::AreEqual<uint32_t>(20, area(uint3(4, 5, 6)));
	}

	TEST_METHOD(arithmetic_operators)
	{
		uint3 v(1, 2, 3);
		uint3 vo(5, 6, 7);
		Assert::AreEqual(v + 1u, uint3(2, 3, 4));
		Assert::AreEqual(1u + v, uint3(2, 3, 4));
		Assert::AreEqual(v + vo, uint3(6, 8, 10));

		Assert::AreEqual(v - 1u, uint3(0, 1, 2));
		Assert::AreEqual(10u - v, uint3(9, 8, 7));
		Assert::AreEqual(vo - v, uint3(4));

		Assert::AreEqual(v * 2u, uint3(2, 4, 6));
		Assert::AreEqual(2u * v, uint3(2, 4, 6));
		Assert::AreEqual(v * vo, uint3(5, 12, 21));

		Assert::AreEqual(v * 2u, uint3(2, 4, 6));
		Assert::AreEqual(2u * v, uint3(2, 4, 6));
		Assert::AreEqual(v * vo, uint3(5, 12, 21));

		Assert::AreEqual(v / 2u, uint3(0, 1, 1));
		Assert::AreEqual(10u / v, uint3(10, 5, 3));
		Assert::AreEqual(vo / v, uint3(5, 3, 2));
	}

	TEST_METHOD(assignment_operators)
	{
		uint3 v(5, 6, 7);

		// copy assignment
		uint3 vc;
		vc = v;
		Assert::IsTrue((vc.x == v.x) && (vc.y == v.y) && (vc.z == v.z));

		// move assignment
		uint3 vm;
		vm = std::move(v);
		Assert::IsTrue((vm.x == v.x) && (vm.y == v.y) && (vm.z == v.z));
	}

	TEST_METHOD(clamp)
	{
		using math::clamp;

		const uint3 lo(1, 2, 3);
		const uint3 hi(11, 12, 13);
		const uint3 v(2, 3, 4);

		Assert::AreEqual(lo, clamp(uint3::zero, lo, hi));
		Assert::AreEqual(v, clamp(v, lo, hi));
		Assert::AreEqual(hi, clamp(uint3(42), lo, hi));
	}

	TEST_METHOD(compound_assignment_operators)
	{
		uint3 v(1, 2, 3);
		(v += 5) += 5;
		Assert::AreEqual(uint3(11, 12, 13), v);

		(v -= 7) -= 3;
		Assert::AreEqual(uint3(1, 2, 3), v);

		(v *= 2) *= 3;
		Assert::AreEqual(uint3(6, 12, 18), v);

		(v /= 3) /= 2;
		Assert::AreEqual(uint3(1, 2, 3), v);

		(v += v) += v;
		Assert::AreEqual(uint3(4, 8, 12), v);

		v -= v;
		Assert::AreEqual(uint3::zero, v);
	}

	TEST_METHOD(conversion_operators_xy)
	{
		uint3 v(1, 2, 3);

		Assert::AreEqual(uint2(1, 2), xy(v));

		Assert::AreEqual(uint2(1, 2), static_cast<uint2>(v));
	}

	TEST_METHOD(ctors)
	{
		uint3 v0;
		Assert::IsTrue((v0.x == 0) && (v0.y == 0) && (v0.z == 0));

		uint3 v1(24);
		Assert::IsTrue((v1.x == 24) && (v1.y == 24) && (v1.z == 24));

		uint2 v2(1, 2);
		uint3 v1_2(v2, 3);
		Assert::IsTrue((v1_2.x == 1) && (v1_2.y == 2) && (v1_2.z == 3));

		uint3 v4(1, 2, 3);
		Assert::IsTrue((v4.x == 1) && (v4.y == 2) && (v4.z == 3));

		// copy ctor
		uint3 vc = v4;
		Assert::IsTrue((vc.x == v4.x) && (vc.y == v4.y) && (vc.z == v4.z));

		// move ctor
		uint3 vm = std::move(v4);
		Assert::IsTrue((vm.x == vc.x) && (vm.y == vc.y) && (vm.z == vc.z));
	}

	TEST_METHOD(equal_operator)
	{
		uint3 v(1, 2, 3);

		Assert::AreNotEqual(v, uint3(100, 2, 3));
		Assert::AreNotEqual(v, uint3(1, 100, 3));
		Assert::AreNotEqual(v, uint3(1, 2, 100));

		Assert::AreEqual(v, v);
		Assert::AreEqual(v, uint3(1, 2, 3));
	}

	TEST_METHOD(rational_operators)
	{
		// operator <
		Assert::IsFalse(uint3(6, 1, 2) < 6);
		Assert::IsFalse(uint3(7, 1, 2) < 6);
		Assert::IsFalse(uint3(1, 6, 2) < 6);
		Assert::IsFalse(uint3(1, 7, 2) < 6);
		Assert::IsFalse(uint3(1, 2, 6) < 6);
		Assert::IsFalse(uint3(1, 2, 7) < 6);
		Assert::IsTrue(uint3(1, 2, 3) < 6);

		// operator <=
		Assert::IsFalse(uint3(7, 1, 2) <= 6);
		Assert::IsFalse(uint3(1, 7, 2) <= 6);
		Assert::IsFalse(uint3(1, 2, 7) <= 6);
		Assert::IsTrue(uint3(1, 2, 3) <= 6);
		Assert::IsTrue(uint3(6, 1, 2) <= 6);
		Assert::IsTrue(uint3(1, 6, 2) <= 6);
		Assert::IsTrue(uint3(1, 2, 6) <= 6);

		// operator >
		Assert::IsFalse(uint3(0, 4, 5) > 1);
		Assert::IsFalse(uint3(1, 4, 5) > 1);
		Assert::IsFalse(uint3(4, 0, 5) > 1);
		Assert::IsFalse(uint3(4, 1, 5) > 1);
		Assert::IsFalse(uint3(4, 5, 0) > 1);
		Assert::IsFalse(uint3(4, 5, 1) > 1);
		Assert::IsTrue(uint3(4, 5, 6) > 1);

		// operator >=
		Assert::IsFalse(uint3(0, 4, 5) >= 1);
		Assert::IsFalse(uint3(4, 0, 5) >= 1);
		Assert::IsFalse(uint3(4, 5, 0) >= 1);
		Assert::IsTrue(uint3(4, 5, 6) >= 1);
		Assert::IsTrue(uint3(1, 4, 5) >= 1);
		Assert::IsTrue(uint3(4, 1, 5) >= 1);
		Assert::IsTrue(uint3(4, 5, 1) >= 1);
	}

	TEST_METHOD(static_members)
	{
		Assert::AreEqual(uint3(1, 0, 0), uint3::unit_x);
		Assert::AreEqual(uint3(0, 1, 0), uint3::unit_y);
		Assert::AreEqual(uint3(0, 0, 1), uint3::unit_z);
		Assert::AreEqual(uint3(1, 1, 1), uint3::unit_xyz);
		Assert::AreEqual(uint3(0, 0, 0), uint3::zero);
	}

	TEST_METHOD(volume)
	{
		using math::volume;

		Assert::AreEqual<uint32_t>(0, volume(uint3::zero));
		Assert::AreEqual<uint32_t>(120, volume(uint3(4, 5, 6)));
	}
};

TEST_CLASS(math_vector_int_uint4) {
public:

	TEST_METHOD(area)
	{
		using math::area;

		Assert::AreEqual<uint32_t>(0, area(uint4::zero));
		Assert::AreEqual<uint32_t>(20, area(uint4(4, 5, 6, 7)));
	}

	TEST_METHOD(arithmetic_operators)
	{
		uint4 v(1, 2, 3, 4);
		uint4 vo(5, 6, 7, 8);
		Assert::AreEqual(v + 1u, uint4(2, 3, 4, 5));
		Assert::AreEqual(1u + v, uint4(2, 3, 4, 5));
		Assert::AreEqual(v + vo, uint4(6, 8, 10, 12));

		Assert::AreEqual(v - 1u, uint4(0, 1, 2, 3));
		Assert::AreEqual(10u - v, uint4(9, 8, 7, 6));
		Assert::AreEqual(vo - v, uint4(4));

		Assert::AreEqual(v * 2u, uint4(2, 4, 6, 8));
		Assert::AreEqual(2u * v, uint4(2, 4, 6, 8));
		Assert::AreEqual(v * vo, uint4(5, 12, 21, 32));

		Assert::AreEqual(v * 2u, uint4(2, 4, 6, 8));
		Assert::AreEqual(2u * v, uint4(2, 4, 6, 8));
		Assert::AreEqual(v * vo, uint4(5, 12, 21, 32));

		Assert::AreEqual(v / 2u, uint4(0, 1, 1, 2));
		Assert::AreEqual(10u / v, uint4(10, 5, 3, 2));
		Assert::AreEqual(vo / v, uint4(5, 3, 2, 2));
	}

	TEST_METHOD(assignment_operators)
	{
		uint4 v(5, 6, 7, 8);

		// copy assignment
		uint4 vc;
		vc = v;
		Assert::IsTrue((vc.x == v.x) && (vc.y == v.y) && (vc.z == v.z) && (vc.w == v.w));

		// move assignment
		uint4 vm;
		vm = std::move(v);
		Assert::IsTrue((vm.x == v.x) && (vm.y == v.y) && (vm.z == v.z) && (vm.w == v.w));
	}

	TEST_METHOD(clamp)
	{
		using math::clamp;

		const uint4 lo(1, 2, 3, 4);
		const uint4 hi(11, 12, 13, 14);
		const uint4 v(2, 3, 4, 5);

		Assert::AreEqual(lo, clamp(uint4::zero, lo, hi));
		Assert::AreEqual(v, clamp(v, lo, hi));
		Assert::AreEqual(hi, clamp(uint4(42), lo, hi));
	}

	TEST_METHOD(compound_assignment_operators)
	{
		uint4 v(1, 2, 3, 4);
		(v += 5) += 5;
		Assert::AreEqual(uint4(11, 12, 13, 14), v);

		(v -= 7) -= 3;
		Assert::AreEqual(uint4(1, 2, 3, 4), v);

		(v *= 2) *= 3;
		Assert::AreEqual(uint4(6, 12, 18, 24), v);

		(v /= 3) /= 2;
		Assert::AreEqual(uint4(1, 2, 3, 4), v);

		(v += v) += v;
		Assert::AreEqual(uint4(4, 8, 12, 16), v);

		v -= v;
		Assert::AreEqual(uint4::zero, v);
	}

	TEST_METHOD(conversion_operators_xy_xyz)
	{
		uint4 v(1, 2, 3, 4);

		Assert::AreEqual(uint2(1, 2), xy(v));
		Assert::AreEqual(uint3(1, 2, 3), xyz(v));

		Assert::AreEqual(uint2(1, 2), static_cast<uint2>(v));
		Assert::AreEqual(uint3(1, 2, 3), static_cast<uint3>(v));
	}

	TEST_METHOD(ctors)
	{
		uint4 v0;
		Assert::IsTrue((v0.x == 0) && (v0.y == 0) && (v0.z == 0) && (v0.w == 0));

		uint4 v1(24);
		Assert::IsTrue((v1.x == 24) && (v1.y == 24) && (v1.z == 24) && (v1.w == 24));

		uint2 v2(1, 2);
		uint4 v1_2(v2, 3, 4);
		Assert::IsTrue((v1_2.x == 1) && (v1_2.y == 2) && (v1_2.z == 3) && (v1_2.w == 4));

		uint3 v3(1, 2, 3);
		uint4 v1_3(v3, 4);
		Assert::IsTrue((v1_3.x == 1) && (v1_3.y == 2) && (v1_3.z == 3) && (v1_3.w == 4));

		uint4 v4(1, 2, 3, 4);
		Assert::IsTrue((v4.x == 1) && (v4.y == 2) && (v4.z == 3) && (v4.w == 4));

		// copy ctor
		uint4 vc = v4;
		Assert::IsTrue((vc.x == v4.x) && (vc.y == v4.y) && (vc.z == v4.z) && (vc.w == v4.w));

		// move ctor
		uint4 vm = std::move(v4);
		Assert::IsTrue((vm.x == vc.x) && (vm.y == vc.y) && (vm.z == vc.z) && (vm.w == vc.w));
	}

	TEST_METHOD(equal_operator)
	{
		uint4 v(1, 2, 3, 4);

		Assert::AreNotEqual(v, uint4(100, 2, 3, 4));
		Assert::AreNotEqual(v, uint4(1, 100, 3, 4));
		Assert::AreNotEqual(v, uint4(1, 2, 100, 4));
		Assert::AreNotEqual(v, uint4(1, 2, 3, 100));

		Assert::AreEqual(v, v);
		Assert::AreEqual(v, uint4(1, 2, 3, 4));
	}

	TEST_METHOD(rational_operators)
	{
		// operator <
		Assert::IsFalse(uint4(6, 1, 2, 3) < 6);
		Assert::IsFalse(uint4(7, 1, 2, 3) < 6);
		Assert::IsFalse(uint4(1, 6, 2, 3) < 6);
		Assert::IsFalse(uint4(1, 7, 2, 3) < 6);
		Assert::IsFalse(uint4(1, 2, 6, 3) < 6);
		Assert::IsFalse(uint4(1, 2, 7, 3) < 6);
		Assert::IsFalse(uint4(1, 2, 3, 6) < 6);
		Assert::IsFalse(uint4(1, 2, 3, 7) < 6);
		Assert::IsTrue(uint4(1, 2, 3, 4) < 6);

		// operator <=
		Assert::IsFalse(uint4(7, 1, 2, 3) <= 6);
		Assert::IsFalse(uint4(1, 7, 2, 3) <= 6);
		Assert::IsFalse(uint4(1, 2, 7, 3) <= 6);
		Assert::IsFalse(uint4(1, 2, 3, 7) <= 6);
		Assert::IsTrue(uint4(1, 2, 3, 4) <= 6);
		Assert::IsTrue(uint4(6, 1, 2, 3) <= 6);
		Assert::IsTrue(uint4(1, 6, 2, 3) <= 6);
		Assert::IsTrue(uint4(1, 2, 6, 3) <= 6);
		Assert::IsTrue(uint4(1, 2, 3, 6) <= 6);

		// operator >
		Assert::IsFalse(uint4(0, 4, 5, 6) > 1);
		Assert::IsFalse(uint4(1, 4, 5, 6) > 1);
		Assert::IsFalse(uint4(4, 0, 5, 6) > 1);
		Assert::IsFalse(uint4(4, 1, 5, 6) > 1);
		Assert::IsFalse(uint4(4, 5, 0, 6) > 1);
		Assert::IsFalse(uint4(4, 5, 1, 6) > 1);
		Assert::IsFalse(uint4(4, 5, 6, 0) > 1);
		Assert::IsFalse(uint4(4, 5, 6, 1) > 1);
		Assert::IsTrue(uint4(4, 5, 6, 7) > 1);

		// operator >=
		Assert::IsFalse(uint4(0, 4, 5, 6) >= 1);
		Assert::IsFalse(uint4(4, 0, 5, 6) >= 1);
		Assert::IsFalse(uint4(4, 5, 0, 6) >= 1);
		Assert::IsFalse(uint4(4, 5, 6, 0) >= 1);
		Assert::IsTrue(uint4(4, 5, 6, 7) >= 1);
		Assert::IsTrue(uint4(1, 4, 5, 6) >= 1);
		Assert::IsTrue(uint4(4, 1, 5, 6) >= 1);
		Assert::IsTrue(uint4(4, 5, 1, 6) >= 1);
		Assert::IsTrue(uint4(4, 5, 6, 1) >= 1);
	}

	TEST_METHOD(static_members)
	{
		Assert::AreEqual(uint4(1, 0, 0, 0), uint4::unit_x);
		Assert::AreEqual(uint4(0, 1, 0, 0), uint4::unit_y);
		Assert::AreEqual(uint4(0, 0, 1, 0), uint4::unit_z);
		Assert::AreEqual(uint4(0, 0, 0, 1), uint4::unit_w);
		Assert::AreEqual(uint4(1, 1, 1, 1), uint4::unit_xyzw);
		Assert::AreEqual(uint4(0, 0, 0, 0), uint4::zero);
	}
	
	TEST_METHOD(volume)
	{
		using math::volume;

		Assert::AreEqual<uint32_t>(0, volume(uint4::zero));
		Assert::AreEqual<uint32_t>(120, volume(uint4(4, 5, 6, 7)));
	}
};

} // namespace unittest
