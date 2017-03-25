
#include "math/utility.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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
		Assert::IsTrue(approx_equal(1.0, 1.0));
		Assert::IsTrue(approx_equal(2.0, 2.0));

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
};

} // namespace unittest
