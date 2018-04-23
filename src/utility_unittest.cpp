#include "math/utility.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

template<> inline std::wstring ToString<long double>(const long double& t) { RETURN_WIDE_STRING(t); }

}}} // namespace Microsoft::VisualStudio::CppUnitTestFramework


namespace unittest {

TEST_CLASS(math_utility) {
public:

	TEST_METHOD(approx_equal)
	{
		using math::approx_equal;

		// float
		Assert::IsTrue(approx_equal(1.0f, 1.0f));
		Assert::IsTrue(approx_equal(2.0f, 2.0f));

		// double
		Assert::IsTrue(approx_equal(3.0, 3.0));
		Assert::IsTrue(approx_equal(4.0, 4.0));

		// long double
		Assert::IsTrue(approx_equal(5.0l, 5.0l));
		Assert::IsTrue(approx_equal(6.0l, 6.0l));

		// max_abs param
		Assert::IsTrue(approx_equal(1.0, 1.0, 0.0));
		Assert::IsFalse(approx_equal(1.0, 1.00001, 0.0));

		Assert::IsTrue(approx_equal(1.0, 1.001, 1.0));
		Assert::IsTrue(approx_equal(1.0, 1.001, 0.1));
		Assert::IsTrue(approx_equal(1.0, 1.001, 0.01));
		Assert::IsTrue(approx_equal(1.0, 1.001, 0.001));

		Assert::IsFalse(approx_equal(1.0, 1.001, 0.0009));
		Assert::IsFalse(approx_equal(1.0, 1.001, 0.0001));
	}

	TEST_METHOD(clamp)
	{
		using math::clamp;

		Assert::AreEqual(-1, clamp(-24, -1, 1));
		Assert::AreEqual(-1, clamp(-1, -1, 1));
		Assert::AreEqual(0, clamp(0, -1, 1));
		Assert::AreEqual(1, clamp(1, -1, 1));
		Assert::AreEqual(1, clamp(24, -1, 1));
	}

	TEST_METHOD(lerp)
	{
		using math::lerp;

		Assert::AreEqual(0.0f, lerp(0.0f, 1.0f, 0.0f));
		Assert::AreEqual(0.6, lerp(0.0, 1.0, 0.6));
		Assert::AreEqual(1.0l, lerp(0.0l, 1.0l, 1.0l));

		//Assert::AreEqual(24.0f, lerp(24.0f, 24.0f, 0.4f));
		//Assert::AreEqual(24.0f, lerp(24.0f, 24.0f, 0.7f));
	}

	TEST_METHOD(saturate)
	{
		using math::saturate;

		Assert::AreEqual(0.0f, saturate(-24.0f));
		Assert::AreEqual(0, saturate(0));
		Assert::AreEqual(1u, saturate(1u));
		Assert::AreEqual(1.0, saturate(24.0));
	}

	TEST_METHOD(sign)
	{
		using math::sign;

		Assert::AreEqual(-1.0f, sign(-24.0f));
		//Assert::AreEqual(0.0, sign(0.0));
		//Assert::AreEqual(1, sign(24));
	}
};

} // namespace unittest
