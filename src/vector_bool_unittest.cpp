#include "math/vector_bool.h"

#include <utility>
#include "CppUnitTest.h"

using math::bool2;
using math::bool3;
using math::bool4;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

template<> inline std::wstring ToString<math::bool2>(const math::bool2& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<math::bool3>(const math::bool3& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<math::bool4>(const math::bool4& t) { RETURN_WIDE_STRING(t); }

}}} // namespace Microsoft::VisualStudio::CppUnitTestFramework


namespace unittest {

TEST_CLASS(math_vector_bool_bool2) {
public:

	TEST_METHOD(all)
	{
		using math::all;

		Assert::IsFalse(all(bool2(false, false)));
		Assert::IsFalse(all(bool2(true, false)));
		Assert::IsFalse(all(bool2(false, true)));

		Assert::IsTrue(all(bool2(true, true)));
	}

	TEST_METHOD(any)
	{
		using math::any;

		Assert::IsFalse(any(bool2(false, false)));

		Assert::IsTrue(any(bool2(true, false)));
		Assert::IsTrue(any(bool2(false, true)));
		Assert::IsTrue(any(bool2(true, true)));
	}

	TEST_METHOD(ctors)
	{
		bool2 v0;
		Assert::IsTrue((v0.x == false) && (v0.y == false));

		bool2 v1(true);
		Assert::IsTrue((v1.x == true) && (v1.y == true));

		bool2 v4(true, false);
		Assert::IsTrue((v4.x == true) && (v4.y == false));

		// copy ctor
		bool2 vc = v4;
		Assert::IsTrue((vc.x == v4.x) && (vc.y == v4.y));

		// move ctor
		bool2 vm = std::move(v4);
		Assert::IsTrue((vm.x == vc.x) && (vm.y == vc.y));
	}

	TEST_METHOD(equal_operator)
	{
		bool2 v(true);

		Assert::AreNotEqual(v, bool2(false, true));
		Assert::AreNotEqual(v, bool2(true, false));

		Assert::AreEqual(v, v);
		Assert::AreEqual(v, bool2(true));
	}

	TEST_METHOD(not_impl)
	{
		using math::not_impl;

		Assert::AreEqual(bool2(true), not_impl(bool2(false)));
		Assert::AreEqual(bool2(false), not_impl(bool2(true)));

		Assert::AreEqual(bool2(false, true), not_impl(bool2(true, false)));
		Assert::AreEqual(bool2(true, false), not_impl(bool2(false, true)));
	}
};

TEST_CLASS(math_vector_bool_bool3) {
public:

	TEST_METHOD(all)
	{
		using math::all;

		Assert::IsFalse(all(bool3(false, false, false)));
		Assert::IsFalse(all(bool3(true, false, false)));
		Assert::IsFalse(all(bool3(false, true, false)));
		Assert::IsFalse(all(bool3(false, false, true)));

		Assert::IsTrue(all(bool3(true, true, true)));
	}

	TEST_METHOD(any)
	{
		using math::any;

		Assert::IsFalse(any(bool3(false, false, false)));

		Assert::IsTrue(any(bool3(true, false, false)));
		Assert::IsTrue(any(bool3(false, true, false)));
		Assert::IsTrue(any(bool3(false, false, true)));
		Assert::IsTrue(any(bool3(true, true, true)));
	}

	TEST_METHOD(ctors)
	{
		bool3 v0;
		Assert::IsTrue((v0.x == false) && (v0.y == false) && (v0.z == false));

		bool3 v1(true);
		Assert::IsTrue((v1.x == true) && (v1.y == true) && (v1.z == true));

		bool3 v4(true, false, true);
		Assert::IsTrue((v4.x == true) && (v4.y == false) && (v4.z == true));

		// copy ctor
		bool3 vc = v4;
		Assert::IsTrue((vc.x == v4.x) && (vc.y == v4.y) && (vc.z == v4.z));

		// move ctor
		bool3 vm = std::move(v4);
		Assert::IsTrue((vm.x == vc.x) && (vm.y == vc.y) && (vm.z == vc.z));
	}

	TEST_METHOD(equal_operator)
	{
		bool3 v(true);

		Assert::AreNotEqual(v, bool3(false, true, true));
		Assert::AreNotEqual(v, bool3(true, false, true));
		Assert::AreNotEqual(v, bool3(true, true, false));

		Assert::AreEqual(v, v);
		Assert::AreEqual(v, bool3(true));
	}

	TEST_METHOD(not)
	{
		using math::not_impl;

		Assert::AreEqual(bool3(true), not_impl(bool3(false)));
		Assert::AreEqual(bool3(false), not_impl(bool3(true)));

		Assert::AreEqual(bool3(false, true, true), not_impl(bool3(true, false, false)));
		Assert::AreEqual(bool3(true, false, true), not_impl(bool3(false, true, false)));
		Assert::AreEqual(bool3(true, true, false), not_impl(bool3(false, false, true)));
	}

	TEST_METHOD(xy)
	{
		using math::xy;

		bool3 v(true, false, true);

		Assert::AreEqual(bool2(true, false), xy(v));
	}
};

TEST_CLASS(math_vector_bool_bool4) {
public:

	TEST_METHOD(all)
	{
		using math::all;

		Assert::IsFalse(all(bool4(false, false, false, false)));
		Assert::IsFalse(all(bool4(true, false, false, false)));
		Assert::IsFalse(all(bool4(false, true, false, false)));
		Assert::IsFalse(all(bool4(false, false, true, false)));
		Assert::IsFalse(all(bool4(false, false, false, true)));

		Assert::IsTrue(all(bool4(true, true, true, true)));
	}

	TEST_METHOD(any)
	{
		using math::any;

		Assert::IsFalse(any(bool4(false, false, false, false)));

		Assert::IsTrue(any(bool4(true, false, false, false)));
		Assert::IsTrue(any(bool4(false, true, false, false)));
		Assert::IsTrue(any(bool4(false, false, true, false)));
		Assert::IsTrue(any(bool4(false, false, false, true)));
		Assert::IsTrue(any(bool4(true, true, true, true)));
	}

	TEST_METHOD(ctors)
	{
		bool4 v0;
		Assert::IsTrue((v0.x == false) && (v0.y == false) && (v0.z == false) && (v0.w == false));

		bool4 v1(true);
		Assert::IsTrue((v1.x == true) && (v1.y == true) && (v1.z == true) && (v1.w == true));

		bool4 v4(true, false, true, false);
		Assert::IsTrue((v4.x == true) && (v4.y == false) && (v4.z == true) && (v4.w == false));

		// copy ctor
		bool4 vc = v4;
		Assert::IsTrue((vc.x == v4.x) && (vc.y == v4.y) && (vc.z == v4.z) && (vc.w == v4.w));

		// move ctor
		bool4 vm = std::move(v4);
		Assert::IsTrue((vm.x == vc.x) && (vm.y == vc.y) && (vm.z == vc.z) && (vm.w == vc.w));
	}

	TEST_METHOD(equal_operator)
	{
		bool4 v(true);

		Assert::AreNotEqual(v, bool4(false, true, true, true));
		Assert::AreNotEqual(v, bool4(true, false, true, true));
		Assert::AreNotEqual(v, bool4(true, true, false, true));
		Assert::AreNotEqual(v, bool4(true, true, true, false));

		Assert::AreEqual(v, v);
		Assert::AreEqual(v, bool4(true));
	}

	TEST_METHOD(not_impl)
	{
		using math::not_impl;

		Assert::AreEqual(bool4(true), not_impl(bool4(false)));
		Assert::AreEqual(bool4(false), not_impl(bool4(true)));

		Assert::AreEqual(bool4(false, true, true, true), not_impl(bool4(true, false, false, false)));
		Assert::AreEqual(bool4(true, false, true, true), not_impl(bool4(false, true, false, false)));
		Assert::AreEqual(bool4(true, true, false, true), not_impl(bool4(false, false, true, false)));
		Assert::AreEqual(bool4(true, true, true, false), not_impl(bool4(false, false, false, true)));
	}

	TEST_METHOD(xy_xyz)
	{
		using math::xy;
		using math::xyz;

		bool4 v(true, false, true, false);

		Assert::AreEqual(bool2(true, false), xy(v));
		Assert::AreEqual(bool3(true, false, true), xyz(v));
	}
};

} // namespace unittest
