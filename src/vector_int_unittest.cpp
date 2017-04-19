#include "math/vector_int.h"

#include <utility>
#include "CppUnitTest.h"

using math::int4;
using math::uint4;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

template<> inline std::wstring ToString<int4>(const int4& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<uint4>(const uint4& t) { RETURN_WIDE_STRING(t); }

}}} // namespace Microsoft::VisualStudio::CppUnitTestFramework


namespace unittest {

TEST_CLASS(math_vector_int_int4) {
public:

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

	TEST_METHOD(ctors)
	{
		int4 v0;
		Assert::IsTrue((v0.x == 0) && (v0.y == 0) && (v0.z == 0) && (v0.w == 0));

		int4 v1(24);
		Assert::IsTrue((v1.x == 24) && (v1.y == 24) && (v1.z == 24) && (v1.w == 24));

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
		Assert::IsFalse(int4(6, 1, 2, 3) < int32_t(6));
		Assert::IsFalse(int4(7, 1, 2, 3) < int32_t(6));
		Assert::IsFalse(int4(1, 6, 2, 3) < int32_t(6));
		Assert::IsFalse(int4(1, 7, 2, 3) < int32_t(6));
		Assert::IsFalse(int4(1, 2, 6, 3) < int32_t(6));
		Assert::IsFalse(int4(1, 2, 7, 3) < int32_t(6));
		Assert::IsFalse(int4(1, 2, 3, 6) < int32_t(6));
		Assert::IsFalse(int4(1, 2, 3, 7) < int32_t(6));
		Assert::IsTrue(int4(1, 2, 3, 4) < int32_t(6));

		// operator <=
		Assert::IsFalse(int4(7, 1, 2, 3) <= int32_t(6));
		Assert::IsFalse(int4(1, 7, 2, 3) <= int32_t(6));
		Assert::IsFalse(int4(1, 2, 7, 3) <= int32_t(6));
		Assert::IsFalse(int4(1, 2, 3, 7) <= int32_t(6));
		Assert::IsTrue(int4(1, 2, 3, 4) <= int32_t(6));
		Assert::IsTrue(int4(6, 1, 2, 3) <= int32_t(6));
		Assert::IsTrue(int4(1, 6, 2, 3) <= int32_t(6));
		Assert::IsTrue(int4(1, 2, 6, 3) <= int32_t(6));
		Assert::IsTrue(int4(1, 2, 3, 6) <= int32_t(6));

		// operator >
		Assert::IsFalse(int4(0, 4, 5, 6) > int32_t(1));
		Assert::IsFalse(int4(1, 4, 5, 6) > int32_t(1));
		Assert::IsFalse(int4(4, 0, 5, 6) > int32_t(1));
		Assert::IsFalse(int4(4, 1, 5, 6) > int32_t(1));
		Assert::IsFalse(int4(4, 5, 0, 6) > int32_t(1));
		Assert::IsFalse(int4(4, 5, 1, 6) > int32_t(1));
		Assert::IsFalse(int4(4, 5, 6, 0) > int32_t(1));
		Assert::IsFalse(int4(4, 5, 6, 1) > int32_t(1));
		Assert::IsTrue(int4(4, 5, 6, 7) > int32_t(1));

		// operator >=
		Assert::IsFalse(int4(0, 4, 5, 6) >= int32_t(1));
		Assert::IsFalse(int4(4, 0, 5, 6) >= int32_t(1));
		Assert::IsFalse(int4(4, 5, 0, 6) >= int32_t(1));
		Assert::IsFalse(int4(4, 5, 6, 0) >= int32_t(1));
		Assert::IsTrue(int4(4, 5, 6, 7) >= int32_t(1));
		Assert::IsTrue(int4(1, 4, 5, 6) >= int32_t(1));
		Assert::IsTrue(int4(4, 1, 5, 6) >= int32_t(1));
		Assert::IsTrue(int4(4, 5, 1, 6) >= int32_t(1));
		Assert::IsTrue(int4(4, 5, 6, 1) >= int32_t(1));
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
};

TEST_CLASS(math_vector_int_uint4) {
public:

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

	TEST_METHOD(ctors)
	{
		uint4 v0;
		Assert::IsTrue((v0.x == 0) && (v0.y == 0) && (v0.z == 0) && (v0.w == 0));

		uint4 v1(24);
		Assert::IsTrue((v1.x == 24) && (v1.y == 24) && (v1.z == 24) && (v1.w == 24));

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
		Assert::IsFalse(uint4(6, 1, 2, 3) < uint32_t(6));
		Assert::IsFalse(uint4(7, 1, 2, 3) < uint32_t(6));
		Assert::IsFalse(uint4(1, 6, 2, 3) < uint32_t(6));
		Assert::IsFalse(uint4(1, 7, 2, 3) < uint32_t(6));
		Assert::IsFalse(uint4(1, 2, 6, 3) < uint32_t(6));
		Assert::IsFalse(uint4(1, 2, 7, 3) < uint32_t(6));
		Assert::IsFalse(uint4(1, 2, 3, 6) < uint32_t(6));
		Assert::IsFalse(uint4(1, 2, 3, 7) < uint32_t(6));
		Assert::IsTrue(uint4(1, 2, 3, 4) < uint32_t(6));

		// operator <=
		Assert::IsFalse(uint4(7, 1, 2, 3) <= uint32_t(6));
		Assert::IsFalse(uint4(1, 7, 2, 3) <= uint32_t(6));
		Assert::IsFalse(uint4(1, 2, 7, 3) <= uint32_t(6));
		Assert::IsFalse(uint4(1, 2, 3, 7) <= uint32_t(6));
		Assert::IsTrue(uint4(1, 2, 3, 4) <= uint32_t(6));
		Assert::IsTrue(uint4(6, 1, 2, 3) <= uint32_t(6));
		Assert::IsTrue(uint4(1, 6, 2, 3) <= uint32_t(6));
		Assert::IsTrue(uint4(1, 2, 6, 3) <= uint32_t(6));
		Assert::IsTrue(uint4(1, 2, 3, 6) <= uint32_t(6));

		// operator >
		Assert::IsFalse(uint4(0, 4, 5, 6) > uint32_t(1));
		Assert::IsFalse(uint4(1, 4, 5, 6) > uint32_t(1));
		Assert::IsFalse(uint4(4, 0, 5, 6) > uint32_t(1));
		Assert::IsFalse(uint4(4, 1, 5, 6) > uint32_t(1));
		Assert::IsFalse(uint4(4, 5, 0, 6) > uint32_t(1));
		Assert::IsFalse(uint4(4, 5, 1, 6) > uint32_t(1));
		Assert::IsFalse(uint4(4, 5, 6, 0) > uint32_t(1));
		Assert::IsFalse(uint4(4, 5, 6, 1) > uint32_t(1));
		Assert::IsTrue(uint4(4, 5, 6, 7) > uint32_t(1));

		// operator >=
		Assert::IsFalse(uint4(0, 4, 5, 6) >= uint32_t(1));
		Assert::IsFalse(uint4(4, 0, 5, 6) >= uint32_t(1));
		Assert::IsFalse(uint4(4, 5, 0, 6) >= uint32_t(1));
		Assert::IsFalse(uint4(4, 5, 6, 0) >= uint32_t(1));
		Assert::IsTrue(uint4(4, 5, 6, 7) >= uint32_t(1));
		Assert::IsTrue(uint4(1, 4, 5, 6) >= uint32_t(1));
		Assert::IsTrue(uint4(4, 1, 5, 6) >= uint32_t(1));
		Assert::IsTrue(uint4(4, 5, 1, 6) >= uint32_t(1));
		Assert::IsTrue(uint4(4, 5, 6, 1) >= uint32_t(1));
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
};

} // namespace unittest
