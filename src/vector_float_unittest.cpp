#include "math/vector_float.h"

#include <utility>
#include "CppUnitTest.h"

using math::float2;
using math::float3;
using math::float4;
using math::quat;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

template<> inline std::wstring ToString<math::float2>(const math::float2& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<math::float3>(const math::float3& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<math::float4>(const math::float4& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<math::quat>(const math::quat& t) { RETURN_WIDE_STRING(t); }

}}} // namespace Microsoft::VisualStudio::CppUnitTestFramework


namespace unittest {

TEST_CLASS(math_vector_float_float2) {
public:

	TEST_METHOD(abs)
	{
		using math::abs;

		const float2 expected_vector(1, 2);

		Assert::AreEqual(expected_vector, abs(float2(-1, -2)));
		Assert::AreEqual(expected_vector, abs(float2(1, 2)));
	}

	TEST_METHOD(address_of)
	{
		float2 v(5, 6);
		float* ptr = &v.x;

		Assert::AreEqual(v.x, ptr[0]);
		Assert::AreEqual(v.y, ptr[1]);
	}

	TEST_METHOD(aspect_ratio)
	{
		using math::approx_equal;
		using math::aspect_ratio;

		Assert::IsTrue(approx_equal(1.0f, aspect_ratio(float2::unit_xy)));
		Assert::IsTrue(approx_equal(3.0f / 2.0f, aspect_ratio(float2(3, 2))));
	}

	TEST_METHOD(approx_equal)
	{
		using math::approx_equal;

		float2 v(1, 2);
		Assert::IsFalse(approx_equal(v, float2(100, 2)));
		Assert::IsFalse(approx_equal(v, float2(1, 100)));
		Assert::IsTrue(approx_equal(v, v));
		Assert::IsTrue(approx_equal(v, float2(1, 2)));

		Assert::IsTrue(approx_equal(v, float2(1, 2), 0.0f));
		Assert::IsFalse(approx_equal(v, float2(1.0001f, 2), 0.0f));
		Assert::IsFalse(approx_equal(v, float2(1, 2.0002f), 0.0f));
	}

	TEST_METHOD(assignments)
	{
		float2 v(5, 6);

		// copy assignment
		float2 vc;
		vc = v;
		Assert::IsTrue((vc.x == v.x) && (vc.y == v.y));

		// move assignment
		float2 vm;
		vm = std::move(v);
		Assert::IsTrue((vm.x == v.x) && (vm.y == v.y));
	}

	TEST_METHOD(binary_operators)
	{
		float2 v(1, 2);

		// operator+
		Assert::AreEqual(float2(11, 12), v + 10);
		Assert::AreEqual(float2(11, 12), 10 + v);
		Assert::AreEqual(float2(1.11f, 2.22f), v + float2(0.11f, 0.22f));
		Assert::AreEqual(float2(1.11f, 2.22f), float2(0.11f, 0.22f) + v);

		// operator-
		Assert::AreEqual(float2(0, 1), v - 1);
		Assert::AreEqual(float2(0, -1), 1 - v);
		Assert::AreEqual(float2::zero, v - float2(1, 2));
		Assert::AreEqual(float2::zero, float2(1, 2) - v);

		// operator*
		Assert::AreEqual(float2(10, 20), v * 10);
		Assert::AreEqual(float2(10, 20), 10 * v);
		Assert::AreEqual(float2(1, 4), v * v);

		// operator/
		Assert::AreEqual(float2(0.5, 1), v / 2);
		Assert::AreEqual(float2::zero, 0.0f / v);
		Assert::AreEqual(float2(1, 1), v / v);
	}

	TEST_METHOD(clamp)
	{
		using math::clamp;

		float2 lo(-5, -7);
		float2 hi(5, 7);
		float2 v(2, 3);

		Assert::AreEqual(lo, clamp(float2(-9, -10), lo, hi));
		Assert::AreEqual(v, clamp(v, lo, hi));
		Assert::AreEqual(hi, clamp(float2(9, 10), lo, hi));

		// default lo and hi
		Assert::AreEqual(float2::zero, clamp(float2(-5), float2::zero, float2::unit_xy));
		Assert::AreEqual(float2(0.5), clamp(float2(0.5), float2::zero, float2::unit_xy));
		Assert::AreEqual(float2::unit_xy, clamp(float2(5), float2::zero, float2::unit_xy));
	}

	TEST_METHOD(compound_assignment_operators)
	{
		float2 v(1, 2);
		(v += 5) += 5;
		Assert::AreEqual(float2(11, 12), v);

		(v -= 7) -= 3;
		Assert::AreEqual(float2(1, 2), v);

		(v *= 2) *= 3;
		Assert::AreEqual(float2(6, 12), v);

		(v /= 3) /= 2;
		Assert::AreEqual(float2(1, 2), v);

		(v += v) += v;
		Assert::AreEqual(float2(4, 8), v);

		v -= v;
		Assert::AreEqual(float2::zero, v);
	}

	TEST_METHOD(ctors)
	{
		float2 v0;
		Assert::IsTrue((v0.x == 0.0f) && (v0.y == 0.0f));

		float2 v1(24);
		Assert::IsTrue((v1.x == 24.0f) && (v1.y == 24.0f));

		float2 v2(1, 2);
		Assert::IsTrue((v2.x == 1.0f) && (v2.y == 2.0f));

		// copy ctor
		float2 vc = v2;
		Assert::IsTrue((vc.x == v2.x) && (vc.y == v2.y));

		// move ctor
		float2 vm = std::move(v2);
		Assert::IsTrue((vm.x == vc.x) && (vm.y == vc.y));
	}

	TEST_METHOD(dot_product)
	{
		using math::dot;
		using math::len_squared;

		float2 u(2, 3);
		float2 v(4, 5);
		float2 w(7, 8);

		Assert::AreEqual(2.0f * 4 + 3 * 5, dot(u, v));
		Assert::AreEqual(0.0f, dot(u, float2::zero));
		Assert::AreEqual(len_squared(u), dot(u, u), L"U * U = |U| * |U|");
		Assert::AreEqual(dot(u, v), dot(v, u), L"U * V = V * U");
		Assert::AreEqual(dot(2 * u, v), 2 * dot(u, v), L"(aU) * V = a(U * V)");
		Assert::AreEqual(dot(u + v, w), dot(u, w) + dot(v, w), L"(U + V)*W = U*W + V*W");
	}

	TEST_METHOD(equal_operator)
	{
		float2 v(1, 2);

		Assert::AreNotEqual(v, float2(100, 2));
		Assert::AreNotEqual(v, float2(1, 100));

		Assert::AreEqual(v, v);
		Assert::AreEqual(v, float2(1, 2));
	}

	TEST_METHOD(is_normalized)
	{
		using math::is_normalized;
		using math::len;

		Assert::IsTrue(is_normalized(float2::unit_x));
		Assert::IsTrue(is_normalized(float2::unit_y));

		float2 v(1, 2);
		Assert::IsTrue(len(v) > 1 && (!is_normalized(v)));
	}

	TEST_METHOD(len_and_len_squared)
	{
		using math::approx_equal;
		using math::len;
		using math::len_squared;

		float2 u(2, 3);
		float2 v(4, 5);

		Assert::AreEqual(2.f * 2 + 3 * 3, len_squared(u));
		Assert::AreEqual(std::sqrt(2.f * 2 + 3 * 3), len(u));

		Assert::AreEqual(2 * len(u), len(2 * u), L"|aU| = |a| * |U|");
		Assert::IsTrue(approx_equal(len(u + v), len(u) + len(v), 0.1f), L"|U + V| <= |U| + |V|");
	}

	TEST_METHOD(lerp)
	{
		using math::lerp;

		Assert::AreEqual(float2(0.0f), lerp(float2::zero, float2::unit_xy, 0.0f));
		Assert::AreEqual(float2(0.6f), lerp(float2::zero, float2::unit_xy, 0.6f));
		Assert::AreEqual(float2(1.0f), lerp(float2::zero, float2::unit_xy, 1.0f));

		float2 v(24);
		Assert::AreEqual(v, lerp(v, v, 0.4f));
		Assert::AreEqual(v, lerp(v, v, 0.7f));
	}

	TEST_METHOD(normalize)
	{
		using math::approx_equal;
		using math::len;
		using math::normalize;

		Assert::AreEqual(float2::zero, normalize(float2::zero));
		Assert::AreEqual(float2::unit_x, normalize(float2::unit_x));
		Assert::AreEqual(float2::unit_y, normalize(float2::unit_y));

		Assert::AreEqual(float2::unit_x, normalize(float2(24, 0)));
		Assert::AreEqual(float2::unit_y, normalize(float2(0, 24)));

		float2 u(-8, 6);
		Assert::IsTrue(approx_equal(1.0f, len(normalize(u))));
	}

	TEST_METHOD(rational_operators)
	{
		// operator <
		Assert::IsFalse(float2(7, 1) < 6);
		Assert::IsFalse(float2(6, 1) < 6);
		Assert::IsFalse(float2(1, 7) < 6);
		Assert::IsFalse(float2(1, 6) < 6);
		Assert::IsTrue(float2(1, 1) < 6);

		// operator <=
		Assert::IsFalse(float2(7, 1) <= 6);
		Assert::IsFalse(float2(1, 7) <= 6);
		Assert::IsTrue(float2(1, 1) <= 6);
		Assert::IsTrue(float2(6, 1) <= 6);
		Assert::IsTrue(float2(1, 6) <= 6);

		// operator >
		Assert::IsFalse(float2(0, 5) > 1);
		Assert::IsFalse(float2(1, 5) > 1);
		Assert::IsFalse(float2(4, 0) > 1);
		Assert::IsFalse(float2(4, 1) > 1);
		Assert::IsTrue(float2(4, 5) > 1);

		// operator >=
		Assert::IsFalse(float2(0, 5) >= 1);
		Assert::IsFalse(float2(4, 0) >= 1);
		Assert::IsTrue(float2(4, 5) >= 1);
		Assert::IsTrue(float2(1, 5) >= 1);
		Assert::IsTrue(float2(4, 1) >= 1);
	}

	TEST_METHOD(saturate)
	{
		using math::saturate;

		Assert::AreEqual(float2::zero, saturate(float2(-24.0f)));
		Assert::AreEqual(float2(0.5f), saturate(float2(0.5f)));
		Assert::AreEqual(float2::unit_xy, saturate(float2(24.0f)));
	}

	TEST_METHOD(static_members)
	{
		Assert::AreEqual(float2(0, 0), float2::zero);
		Assert::AreEqual(float2(1, 0), float2::unit_x);
		Assert::AreEqual(float2(0, 1), float2::unit_y);
		Assert::AreEqual(float2(1, 1), float2::unit_xy);
	}

	TEST_METHOD(unary_operators)
	{
		float2 v(1, 2);

		Assert::AreEqual(float2(-1, -2), -v);
		Assert::AreEqual(float2(1, 2), -(-v));
	}
};

TEST_CLASS(math_vector_float_float3) {
public:

	TEST_METHOD(abs)
	{
		using math::abs;

		const float3 expected_vector(1, 2, 3);

		Assert::AreEqual(expected_vector, abs(float3(-1, -2, -3)));
		Assert::AreEqual(expected_vector, abs(float3(1, 2, 3)));
	}

	TEST_METHOD(address_of)
	{
		float3 v(5, 6, 7);
		float* ptr = &v.x;

		Assert::AreEqual(v.x, ptr[0]);
		Assert::AreEqual(v.y, ptr[1]);
		Assert::AreEqual(v.z, ptr[2]);
	}

	TEST_METHOD(approx_equal)
	{
		using math::approx_equal;

		float3 v(1, 2, 3);
		Assert::IsFalse(approx_equal(v, float3(100, 2, 3)));
		Assert::IsFalse(approx_equal(v, float3(1, 100, 3)));
		Assert::IsFalse(approx_equal(v, float3(1, 2, 100)));
		Assert::IsTrue(approx_equal(v, v));
		Assert::IsTrue(approx_equal(v, float3(1, 2, 3)));

		Assert::IsTrue(approx_equal(v, float3(1, 2, 3), 0.0f));
		Assert::IsFalse(approx_equal(v, float3(1.0001f, 2, 3), 0.0f));
		Assert::IsFalse(approx_equal(v, float3(1, 2.0002f, 3), 0.0f));
		Assert::IsFalse(approx_equal(v, float3(1, 2, 3.0003f), 0.0f));
	}

	TEST_METHOD(assignments)
	{
		float3 v(5, 6, 7);

		// copy assignment
		float3 vc;
		vc = v;
		Assert::IsTrue((vc.x == v.x) && (vc.y == v.y) && (vc.z == v.z));

		// move assignment
		float3 vm;
		vm = std::move(v);
		Assert::IsTrue((vm.x == v.x) && (vm.y == v.y) && (vm.z == v.z));
	}

	TEST_METHOD(binary_operators)
	{
		float3 v(1, 2, 3);

		// operator+
		Assert::AreEqual(float3(11, 12, 13), v + 10);
		Assert::AreEqual(float3(11, 12, 13), 10 + v);
		Assert::AreEqual(float3(1.11f, 2.22f, 3.33f), v + float3(0.11f, 0.22f, 0.33f));
		Assert::AreEqual(float3(1.11f, 2.22f, 3.33f), float3(0.11f, 0.22f, 0.33f) + v);

		// operator-
		Assert::AreEqual(float3(0, 1, 2), v - 1);
		Assert::AreEqual(float3(0, -1, -2), 1 - v);
		Assert::AreEqual(float3::zero, v - float3(1, 2, 3));
		Assert::AreEqual(float3::zero, float3(1, 2, 3) - v);

		// operator*
		Assert::AreEqual(float3(10, 20, 30), v * 10);
		Assert::AreEqual(float3(10, 20, 30), 10 * v);
		Assert::AreEqual(float3(1, 4, 9), v * v);

		// operator/
		Assert::AreEqual(float3(0.5, 1, 1.5), v / 2);
		Assert::AreEqual(float3::zero, 0 / v);
		Assert::AreEqual(float3(1, 1, 1), v / v);
	}

	TEST_METHOD(clamp)
	{
		using math::clamp;

		float3 lo(-5, -7, -9);
		float3 hi(5, 7, 9);
		float3 v(2, 3, 4);

		Assert::AreEqual(lo, clamp(float3(-9, -10, -11), lo, hi));
		Assert::AreEqual(v, clamp(v, lo, hi));
		Assert::AreEqual(hi, clamp(float3(9, 10, 11), lo, hi));

		// default lo and hi
		Assert::AreEqual(float3::zero, clamp(float3(-5), float3::zero, float3::unit_xyz));
		Assert::AreEqual(float3(0.5), clamp(float3(0.5), float3::zero, float3::unit_xyz));
		Assert::AreEqual(float3::unit_xyz, clamp(float3(5), float3::zero, float3::unit_xyz));
	}

	TEST_METHOD(compound_assignment_operators)
	{
		float3 v(1, 2, 3);
		(v += 5) += 5;
		Assert::AreEqual(float3(11, 12, 13), v);

		(v -= 7) -= 3;
		Assert::AreEqual(float3(1, 2, 3), v);

		(v *= 2) *= 3;
		Assert::AreEqual(float3(6, 12, 18), v);

		(v /= 3) /= 2;
		Assert::AreEqual(float3(1, 2, 3), v);

		(v += v) += v;
		Assert::AreEqual(float3(4, 8, 12), v);

		v -= v;
		Assert::AreEqual(float3::zero, v);
	}

	TEST_METHOD(conversion_operators_xy)
	{
		float3 v(1, 2, 3);

		Assert::AreEqual(float2(1, 2), xy(v));

		Assert::AreEqual(float2(1, 2), static_cast<float2>(v));
	}

	TEST_METHOD(cross_product)
	{
		using math::cross;

		float3 u(1, 2, 3);
		float3 v(4, 5, -6);
		float3 w(7, -8, 9);

		Assert::AreEqual(cross(u, v), cross(-v, u), L"U x V = -V x U");

		Assert::AreEqual(
			cross((5 * u) + (7 * v), w),
			5 * cross(u, w) + 7 * cross(v, w),
			L"(aU + bV) x W = a(U x W) + b(V x W)");

		Assert::AreEqual(
			cross(u + v, w),
			cross(u, w) + cross(v, w),
			L"(U + V) x W = U x W + V x W");

		Assert::AreEqual(
			cross(w, u + v),
			cross(w, u) + cross(w, v),
			L"W x (U + V) = W x U + W x V");

		Assert::AreEqual(
			cross(u, cross(v, w)),
			(dot(u, w) * v) - (dot(u, v) * w),
			L"U x (V x W) = (U * W) * V - (U * V) * W");

		auto r1 = 5 * cross(u, v);
		auto r2 = cross(5 * u, v);
		auto r3 = cross(u, 5 * v);
		Assert::IsTrue(r1 == r2 && r2 == r3, L"(aU) x V = U x (aV) = a(U x V)");

		// scalar triple product
		float s1 = dot(cross(u, v), w);		// (U x V)*W
		float s2 = dot(cross(v, w), u);		// (V x W)*U
		float s3 = dot(cross(w, u), v);		// (W x U)*V
		Assert::IsTrue(s1 == s2 && s2 == s3);
		Assert::AreEqual(s1, dot(-cross(v, u), w), L"(U x V)*W = -(V x U)*W");
		Assert::AreEqual(s2, dot(-cross(w, v), u), L"(V x W)*U = -(W x V)*U");
		Assert::AreEqual(s3, dot(-cross(u, w), v), L"(W x U)*V = -(U x W)*V");

		float3 uv = cross(u, v);
		Assert::AreEqual(0.0f, dot(uv, u));
		Assert::AreEqual(0.0f, dot(uv, v));
		Assert::AreEqual(float3::zero, cross(u, u));
	}

	TEST_METHOD(ctors)
	{
		float3 v0;
		Assert::IsTrue((v0.x == 0) && (v0.y == 0) && (v0.z == 0));

		float3 v1(24);
		Assert::IsTrue((v1.x == 24) && (v1.y == 24) && (v1.z == 24));

		float2 vec2(3, 4);
		float3 v3(vec2, 5);
		Assert::IsTrue((v3.x == vec2.x) && (v3.y == vec2.y) && (v3.z == 5));

		float3 v4(1, 2, 3);
		Assert::IsTrue((v4.x == 1) && (v4.y == 2) && (v4.z == 3));

		// copy ctor
		float3 vc = v4;
		Assert::IsTrue((vc.x == v4.x) && (vc.y == v4.y) && (vc.z == v4.z));

		// move ctor
		float3 vm = std::move(v4);
		Assert::IsTrue((vm.x == vc.x) && (vm.y == vc.y) && (vm.z == vc.z));
	}

	TEST_METHOD(dot_product)
	{
		using math::dot;
		using math::len_squared;

		float3 u(2, 3, 4);
		float3 v(4, 5, 6);
		float3 w(7, 8, 9);

		Assert::AreEqual(2.f * 4 + 3 * 5 + 4 * 6, dot(u, v));
		Assert::AreEqual(0.f, dot(u, float3::zero));
		Assert::AreEqual(len_squared(u), dot(u, u), L"U * U = |U| * |U|");
		Assert::AreEqual(dot(u, v), dot(v, u), L"U * V = V * U");
		Assert::AreEqual(dot(2 * u, v), 2 * dot(u, v), L"(aU) * V = a(U * V)");
		Assert::AreEqual(dot(u + v, w), dot(u, w) + dot(v, w), L"(U + V)*W = U*W + V*W");
	}

	TEST_METHOD(equal_operator)
	{
		float3 v(1, 2, 3);

		Assert::AreNotEqual(v, float3(100, 2, 3));
		Assert::AreNotEqual(v, float3(1, 100, 3));
		Assert::AreNotEqual(v, float3(1, 2, 100));

		Assert::AreEqual(v, v);
		Assert::AreEqual(v, float3(1, 2, 3));
	}

	TEST_METHOD(is_normalized)
	{
		using math::is_normalized;
		using math::len;

		Assert::IsTrue(is_normalized(float3::unit_x));
		Assert::IsTrue(is_normalized(float3::unit_y));
		Assert::IsTrue(is_normalized(float3::unit_z));

		float3 v(1, 2, 3);
		Assert::IsTrue(len(v) > 1 && (!is_normalized(v)));
	}

	TEST_METHOD(len_and_len_squared)
	{
		using math::approx_equal;
		using math::len;
		using math::len_squared;

		float3 u(2, 3, 4);
		float3 v(4, 5, 6);

		Assert::AreEqual(2.0f * 2 + 3 * 3 + 4 * 4, len_squared(u));
		Assert::AreEqual(std::sqrt(2.0f * 2 + 3 * 3 + 4 * 4), len(u));

		Assert::AreEqual(2 * len(u), len(2 * u), L"|aU| = |a| * |U|");
		Assert::IsTrue(approx_equal(len(u + v), len(u) + len(v), 0.1f), L"|U + V| <= |U| + |V|");
	}

	TEST_METHOD(lerp)
	{
		using math::lerp;

		Assert::AreEqual(float3(0.0f), lerp(float3::zero, float3::unit_xyz, 0.0f));
		Assert::AreEqual(float3(0.6f), lerp(float3::zero, float3::unit_xyz, 0.6f));
		Assert::AreEqual(float3(1.0f), lerp(float3::zero, float3::unit_xyz, 1.0f));

		float3 v(24);
		Assert::AreEqual(v, lerp(v, v, 0.4f));
		Assert::AreEqual(v, lerp(v, v, 0.7f));
	}

	TEST_METHOD(normalize)
	{
		using math::approx_equal;
		using math::len;
		using math::normalize;

		Assert::AreEqual(float3::zero, normalize(float3::zero));
		Assert::AreEqual(float3::unit_x, normalize(float3::unit_x));
		Assert::AreEqual(float3::unit_y, normalize(float3::unit_y));
		Assert::AreEqual(float3::unit_z, normalize(float3::unit_z));

		Assert::AreEqual(float3::unit_x, normalize(float3(24, 0, 0)));
		Assert::AreEqual(float3::unit_y, normalize(float3(0, 24, 0)));
		Assert::AreEqual(float3::unit_z, normalize(float3(0, 0, 24)));

		float3 u(-8, 6, 24);
		Assert::IsTrue(approx_equal(1.f, len(normalize(u))));
	}

	TEST_METHOD(rational_operators)
	{
		// operator <
		Assert::IsFalse(float3(6, 1, 2) < 6);
		Assert::IsFalse(float3(7, 1, 2) < 6);
		Assert::IsFalse(float3(1, 6, 2) < 6);
		Assert::IsFalse(float3(1, 7, 2) < 6);
		Assert::IsFalse(float3(1, 2, 6) < 6);
		Assert::IsFalse(float3(1, 2, 7) < 6);
		Assert::IsTrue(float3(1, 2, 3) < 6);

		// operator <=
		Assert::IsFalse(float3(7, 1, 2) <= 6);
		Assert::IsFalse(float3(1, 7, 2) <= 6);
		Assert::IsFalse(float3(1, 2, 7) <= 6);
		Assert::IsTrue(float3(1, 2, 3) <= 6);
		Assert::IsTrue(float3(6, 1, 2) <= 6);
		Assert::IsTrue(float3(1, 6, 2) <= 6);
		Assert::IsTrue(float3(1, 2, 6) <= 6);

		// operator >
		Assert::IsFalse(float3(0, 5, 7) > 1);
		Assert::IsFalse(float3(1, 5, 7) > 1);
		Assert::IsFalse(float3(4, 0, 7) > 1);
		Assert::IsFalse(float3(4, 1, 7) > 1);
		Assert::IsFalse(float3(4, 5, 0) > 1);
		Assert::IsFalse(float3(4, 5, 1) > 1);
		Assert::IsTrue(float3(4, 5, 7) > 1);

		// operator >=
		Assert::IsFalse(float3(0, 5, 7) >= 1);
		Assert::IsFalse(float3(4, 0, 7) >= 1);
		Assert::IsFalse(float3(4, 5, 0) >= 1);
		Assert::IsTrue(float3(4, 5, 7) >= 1);
		Assert::IsTrue(float3(1, 5, 7) >= 1);
		Assert::IsTrue(float3(4, 1, 7) >= 1);
		Assert::IsTrue(float3(4, 5, 1) >= 1);
	}

	TEST_METHOD(saturate)
	{
		using math::saturate;

		Assert::AreEqual(float3::zero, saturate(float3(-24.0f)));
		Assert::AreEqual(float3(0.5f), saturate(float3(0.5f)));
		Assert::AreEqual(float3::unit_xyz, saturate(float3(24.0f)));
	}

	TEST_METHOD(static_members)
	{
		Assert::AreEqual(float3(0, 0, 0), float3::zero);
		Assert::AreEqual(float3(1, 0, 0), float3::unit_x);
		Assert::AreEqual(float3(0, 1, 0), float3::unit_y);
		Assert::AreEqual(float3(0, 0, 1), float3::unit_z);
		Assert::AreEqual(float3(1, 1, 0), float3::unit_xy);
		Assert::AreEqual(float3(1, 1, 1), float3::unit_xyz);
	}

	TEST_METHOD(unary_operators)
	{
		float3 v(1, 2, 3);

		Assert::AreEqual(float3(-1, -2, -3), -v);
		Assert::AreEqual(float3(1, 2, 3), -(-v));
	}
};

TEST_CLASS(math_vector_float_float4) {
public:

	TEST_METHOD(abs)
	{
		using math::abs;

		const float4 expected_vector(1, 2, 3, 4);

		Assert::AreEqual(expected_vector, abs(float4(-1, -2, -3, -4)));
		Assert::AreEqual(expected_vector, abs(float4(1, 2, 3, 4)));
	}

	TEST_METHOD(address_of)
	{
		float4 v(5, 6, 7, 8);
		float* ptr = &v.x;

		Assert::AreEqual(v.x, ptr[0]);
		Assert::AreEqual(v.y, ptr[1]);
		Assert::AreEqual(v.z, ptr[2]);
		Assert::AreEqual(v.w, ptr[3]);
	}

	TEST_METHOD(approx_equal)
	{
		using math::approx_equal;

		float4 v(1, 2, 3, 4);
		Assert::IsFalse(approx_equal(v, float4(100, 2, 3, 4)));
		Assert::IsFalse(approx_equal(v, float4(1, 100, 3, 4)));
		Assert::IsFalse(approx_equal(v, float4(1, 2, 100, 4)));
		Assert::IsFalse(approx_equal(v, float4(1, 2, 3, 100)));
		Assert::IsTrue(approx_equal(v, v));
		Assert::IsTrue(approx_equal(v, float4(1, 2, 3, 4)));

		Assert::IsTrue(approx_equal(v, float4(1, 2, 3, 4), 0.0f));
		Assert::IsFalse(approx_equal(v, float4(1.0001f, 2, 3, 4), 0.0f));
		Assert::IsFalse(approx_equal(v, float4(1, 2.0002f, 3, 4), 0.0f));
		Assert::IsFalse(approx_equal(v, float4(1, 2, 3.0003f, 4), 0.0f));
		Assert::IsFalse(approx_equal(v, float4(1, 2, 3, 4.0004f), 0.0f));
	}

	TEST_METHOD(assignments)
	{
		float4 v(5, 6, 7, 8);

		// copy assignment
		float4 vc;
		vc = v;
		Assert::IsTrue((vc.x == v.x) && (vc.y == v.y) && (vc.z == v.z) && (vc.w == v.w));

		// move assignment
		float4 vm;
		vm = std::move(v);
		Assert::IsTrue((vm.x == v.x) && (vm.y == v.y) && (vm.z == v.z) && (vm.w == v.w));
	}

	TEST_METHOD(binary_operators)
	{
		float4 v(1, 2, 3, 4);

		// operator+
		Assert::AreEqual(float4(11, 12, 13, 14), v + 10);
		Assert::AreEqual(float4(11, 12, 13, 14), 10 + v);
		Assert::AreEqual(float4(1.11f, 2.22f, 3.33f, 4.44f), v + float4(0.11f, 0.22f, 0.33f, 0.44f));
		Assert::AreEqual(float4(1.11f, 2.22f, 3.33f, 4.44f), float4(0.11f, 0.22f, 0.33f, 0.44f) + v);

		// operator-
		Assert::AreEqual(float4(0, 1, 2, 3), v - 1);
		Assert::AreEqual(float4(0, -1, -2, -3), 1 - v);
		Assert::AreEqual(float4::zero, v - float4(1, 2, 3, 4));
		Assert::AreEqual(float4::zero, float4(1, 2, 3, 4) - v);

		// operator*
		Assert::AreEqual(float4(10, 20, 30, 40), v * 10);
		Assert::AreEqual(float4(10, 20, 30, 40), 10 * v);
		Assert::AreEqual(float4(1, 4, 9, 16), v * v);

		// operator/
		Assert::AreEqual(float4(0.5, 1, 1.5, 2), v / 2);
		Assert::AreEqual(float4::zero, 0 / v);
		Assert::AreEqual(float4::unit_xyzw, v / v);
	}

	TEST_METHOD(clamp)
	{
		using math::clamp;

		float4 lo(-5, -7, -9, -11);
		float4 hi(5, 7, 9, 11);
		float4 v(2, 3, 4, 5);

		Assert::AreEqual(lo, clamp(float4(-9, -10, -11, -12), lo, hi));
		Assert::AreEqual(v, clamp(v, lo, hi));
		Assert::AreEqual(hi, clamp(float4(9, 10, 11, 12), lo, hi));

		// default lo and hi
		Assert::AreEqual(float4::zero, clamp(float4(-5), float4::zero, float4::unit_xyzw));
		Assert::AreEqual(float4(0.5), clamp(float4(0.5), float4::zero, float4::unit_xyzw));
		Assert::AreEqual(float4::unit_xyzw, clamp(float4(5), float4::zero, float4::unit_xyzw));
	}

	TEST_METHOD(compound_assignment_operators)
	{
		float4 v(1, 2, 3, 4);
		(v += 5) += 5;
		Assert::AreEqual(float4(11, 12, 13, 14), v);

		(v -= 7) -= 3;
		Assert::AreEqual(float4(1, 2, 3, 4), v);

		(v *= 2) *= 3;
		Assert::AreEqual(float4(6, 12, 18, 24), v);

		(v /= 3) /= 2;
		Assert::AreEqual(float4(1, 2, 3, 4), v);

		(v += v) += v;
		Assert::AreEqual(float4(4, 8, 12, 16), v);

		v -= v;
		Assert::AreEqual(float4::zero, v);
	}

	TEST_METHOD(conversion_operators_xy_xyz)
	{
		float4 v(1, 2, 3, 4);

		Assert::AreEqual(float2(1, 2), xy(v));
		Assert::AreEqual(float3(1, 2, 3), xyz(v));

		Assert::AreEqual(float2(1, 2), static_cast<float2>(v));
		Assert::AreEqual(float3(1, 2, 3), static_cast<float3>(v));
	}

	TEST_METHOD(ctors)
	{
		float4 v0;
		Assert::IsTrue((v0.x == 0) && (v0.y == 0) && (v0.z == 0) && (v0.w == 0));

		float4 v1(24);
		Assert::IsTrue((v1.x == 24) && (v1.y == 24) && (v1.z == 24) && (v1.w == 24));

		float4 v4(1, 2, 3, 4);
		Assert::IsTrue((v4.x == 1) && (v4.y == 2) && (v4.z == 3) && (v4.w == 4));

		// copy ctor
		float4 vc = v4;
		Assert::IsTrue((vc.x == v4.x) && (vc.y == v4.y) && (vc.z == v4.z) && (vc.w == v4.w));

		// move ctor
		float4 vm = std::move(v4);
		Assert::IsTrue((vm.x == vc.x) && (vm.y == vc.y) && (vm.z == vc.z) && (vm.w == vc.w));
	}

	TEST_METHOD(dot_product)
	{
		using math::dot;
		using math::len_squared;

		float4 u(2, 3, 4, 5);
		float4 v(5, 6, 7, 8);
		float4 w(9, 10, 11, 12);

		Assert::AreEqual(2.0f * 5 + 3 * 6 + 4 * 7 + 5 * 8, dot(u, v));
		Assert::AreEqual(0.0f, dot(u, float4::zero));
		Assert::AreEqual(len_squared(u), dot(u, u), L"U * U = |U| * |U|");
		Assert::AreEqual(dot(u, v), dot(v, u), L"U * V = V * U");
		Assert::AreEqual(dot(2 * u, v), 2 * dot(u, v), L"(aU) * V = a(U * V)");
		Assert::AreEqual(dot(u + v, w), dot(u, w) + dot(v, w), L"(U + V)*W = U*W + V*W");
	}

	TEST_METHOD(equal_operator)
	{
		float4 v(1, 2, 3, 4);

		Assert::AreNotEqual(v, float4(100, 2, 3, 4));
		Assert::AreNotEqual(v, float4(1, 100, 3, 4));
		Assert::AreNotEqual(v, float4(1, 2, 100, 4));
		Assert::AreNotEqual(v, float4(1, 2, 3, 100));

		Assert::AreEqual(v, v);
		Assert::AreEqual(v, float4(1, 2, 3, 4));
	}

	TEST_METHOD(is_normalized)
	{
		using math::is_normalized;
		using math::len;

		Assert::IsTrue(is_normalized(float4::unit_x));
		Assert::IsTrue(is_normalized(float4::unit_y));
		Assert::IsTrue(is_normalized(float4::unit_z));
		Assert::IsTrue(is_normalized(float4::unit_w));

		float4 v(1, 2, 3, 4);
		Assert::IsTrue(len(v) > 1 && (!is_normalized(v)));
	}

	TEST_METHOD(len_and_len_squared)
	{
		using math::approx_equal;
		using math::len;
		using math::len_squared;

		float4 u(2, 3, 4, 5);
		float4 v(4, 5, 6, 7);

		Assert::AreEqual(2.0f * 2 + 3 * 3 + 4 * 4 + 5 * 5, len_squared(u));
		Assert::AreEqual(std::sqrt(2.0f * 2 + 3 * 3 + 4 * 4 + 5 * 5), len(u));

		Assert::AreEqual(2 * len(u), len(2 * u), L"|aU| = |a| * |U|");
		Assert::IsTrue(approx_equal(len(u + v), len(u) + len(v), 0.1f), L"|U + V| <= |U| + |V|");
	}

	TEST_METHOD(lerp)
	{
		using math::lerp;

		Assert::AreEqual(float4(0.0f), lerp(float4::zero, float4::unit_xyzw, 0.0f));
		Assert::AreEqual(float4(0.6f), lerp(float4::zero, float4::unit_xyzw, 0.6f));
		Assert::AreEqual(float4(1.0f), lerp(float4::zero, float4::unit_xyzw, 1.0f));

		float4 v(24);
		Assert::AreEqual(v, lerp(v, v, 0.4f));
		Assert::AreEqual(v, lerp(v, v, 0.7f));
	}

	TEST_METHOD(normalize)
	{
		using math::approx_equal;
		using math::len;
		using math::normalize;

		Assert::AreEqual(float4::zero, normalize(float4::zero));
		Assert::AreEqual(float4::unit_x, normalize(float4::unit_x));
		Assert::AreEqual(float4::unit_y, normalize(float4::unit_y));
		Assert::AreEqual(float4::unit_z, normalize(float4::unit_z));
		Assert::AreEqual(float4::unit_w, normalize(float4::unit_w));

		Assert::AreEqual(float4::unit_x, normalize(float4(24, 0, 0, 0)));
		Assert::AreEqual(float4::unit_y, normalize(float4(0, 24, 0, 0)));
		Assert::AreEqual(float4::unit_z, normalize(float4(0, 0, 24, 0)));
		Assert::AreEqual(float4::unit_w, normalize(float4(0, 0, 0, 24)));

		float4 u(-8, 6, 24, -0.1f);
		Assert::IsTrue(approx_equal(1.f, len(normalize(u))));
	}

	TEST_METHOD(rational_operators)
	{
		// operator <
		Assert::IsFalse(float4(6, 1, 2, 3) < 6);
		Assert::IsFalse(float4(7, 1, 2, 3) < 6);
		Assert::IsFalse(float4(1, 6, 2, 3) < 6);
		Assert::IsFalse(float4(1, 7, 2, 3) < 6);
		Assert::IsFalse(float4(1, 2, 6, 3) < 6);
		Assert::IsFalse(float4(1, 2, 7, 3) < 6);
		Assert::IsFalse(float4(1, 2, 3, 6) < 6);
		Assert::IsFalse(float4(1, 2, 3, 7) < 6);
		Assert::IsTrue(float4(1, 2, 3, 4) < 6);

		// operator <=
		Assert::IsFalse(float4(7, 1, 2, 3) <= 6);
		Assert::IsFalse(float4(1, 7, 2, 3) <= 6);
		Assert::IsFalse(float4(1, 2, 7, 3) <= 6);
		Assert::IsFalse(float4(1, 2, 3, 7) <= 6);
		Assert::IsTrue(float4(1, 2, 3, 4) <= 6);
		Assert::IsTrue(float4(6, 1, 2, 3) <= 6);
		Assert::IsTrue(float4(1, 6, 2, 3) <= 6);
		Assert::IsTrue(float4(1, 2, 6, 3) <= 6);
		Assert::IsTrue(float4(1, 2, 3, 6) <= 6);

		// operator >
		Assert::IsFalse(float4(0, 5, 7, 9) > 1);
		Assert::IsFalse(float4(1, 5, 7, 9) > 1);
		Assert::IsFalse(float4(4, 0, 7, 9) > 1);
		Assert::IsFalse(float4(4, 1, 7, 9) > 1);
		Assert::IsFalse(float4(4, 5, 0, 9) > 1);
		Assert::IsFalse(float4(4, 5, 1, 9) > 1);
		Assert::IsFalse(float4(4, 5, 7, 0) > 1);
		Assert::IsFalse(float4(4, 5, 7, 1) > 1);
		Assert::IsTrue(float4(4, 5, 7, 9) > 1);

		// operator >=
		Assert::IsFalse(float4(0, 5, 7, 9) >= 1);
		Assert::IsFalse(float4(4, 0, 7, 9) >= 1);
		Assert::IsFalse(float4(4, 5, 0, 9) >= 1);
		Assert::IsFalse(float4(4, 5, 7, 0) >= 1);
		Assert::IsTrue(float4(4, 5, 7, 9) >= 1);
		Assert::IsTrue(float4(1, 5, 7, 9) >= 1);
		Assert::IsTrue(float4(4, 1, 7, 9) >= 1);
		Assert::IsTrue(float4(4, 5, 1, 9) >= 1);
		Assert::IsTrue(float4(4, 5, 7, 1) >= 1);
	}

	TEST_METHOD(round)
	{
		using math::approx_equal;
		using math::round;

		const float4 v(-2.5f, -1.1f, 1.1f, 2.5f);
		const float4 v_expected(std::round(v.x), std::round(v.y), std::round(v.z), std::round(v.w));
		Assert::AreEqual(v_expected, round(v));
	}

	TEST_METHOD(saturate)
	{
		using math::saturate;

		Assert::AreEqual(float4::zero, saturate(float4(-24.0f)));
		Assert::AreEqual(float4(0.5f), saturate(float4(0.5f)));
		Assert::AreEqual(float4::unit_xyzw, saturate(float4(24.0f)));
	}

	TEST_METHOD(static_members)
	{
		Assert::AreEqual(float4(0, 0, 0, 0), float4::zero);
		Assert::AreEqual(float4(1, 0, 0, 0), float4::unit_x);
		Assert::AreEqual(float4(0, 1, 0, 0), float4::unit_y);
		Assert::AreEqual(float4(0, 0, 1, 0), float4::unit_z);
		Assert::AreEqual(float4(0, 0, 0, 1), float4::unit_w);
		Assert::AreEqual(float4(1, 1, 1, 1), float4::unit_xyzw);
	}

	TEST_METHOD(unary_operators)
	{
		float4 v(1, 2, 3, 4);

		Assert::AreEqual(float4(-1, -2, -3, -4), -v);
		Assert::AreEqual(float4(1, 2, 3, 4), -(-v));
	}
};

TEST_CLASS(math_vector_float_quat) {
public:

	TEST_METHOD(address_of)
	{
		quat q(5, 6, 7, 8);
		float* ptr = &q.x;

		Assert::AreEqual(q.x, ptr[0]);
		Assert::AreEqual(q.y, ptr[1]);
		Assert::AreEqual(q.z, ptr[2]);
		Assert::AreEqual(q.a, ptr[3]);
	}

	TEST_METHOD(approx_equal)
	{
		using math::approx_equal;

		quat q(1, 2, 3, 4);
		Assert::IsFalse(approx_equal(q, quat(100, 2, 3, 4)));
		Assert::IsFalse(approx_equal(q, quat(1, 100, 3, 4)));
		Assert::IsFalse(approx_equal(q, quat(1, 2, 100, 4)));
		Assert::IsFalse(approx_equal(q, quat(1, 2, 3, 100)));
		Assert::IsTrue(approx_equal(q, q));
		Assert::IsTrue(approx_equal(q, quat(1, 2, 3, 4)));

		Assert::IsTrue(approx_equal(q, quat(1, 2, 3, 4), 0.0f));
		Assert::IsFalse(approx_equal(q, quat(1.0001f, 2, 3, 4), 0.0f));
		Assert::IsFalse(approx_equal(q, quat(1, 2.0002f, 3, 4), 0.0f));
		Assert::IsFalse(approx_equal(q, quat(1, 2, 3.0003f, 4), 0.0f));
		Assert::IsFalse(approx_equal(q, quat(1, 2, 3, 4.0004f), 0.0f));
	}

	TEST_METHOD(assignments)
	{
		quat q(5, 6, 7, 8);

		// copy assignment
		quat qc;
		qc = q;
		Assert::IsTrue((qc.x == q.x) && (qc.y == q.y) && (qc.z == q.z) && (qc.a == q.a));

		// move assignment
		quat qm;
		qm = std::move(q);
		Assert::IsTrue((qm.x == q.x) && (qm.y == q.y) && (qm.z == q.z) && (qm.a == q.a));
	}

	TEST_METHOD(binary_operator)
	{
		quat q(1, 2, 3, 4);

		Assert::AreEqual(quat(1.11f, 2.22f, 3.33f, 4.44f), q + quat(0.11f, 0.22f, 0.33f, 0.44f));
		Assert::AreEqual(quat(1.11f, 2.22f, 3.33f, 4.44f), quat(0.11f, 0.22f, 0.33f, 0.44f) + q);

		Assert::AreEqual(quat(0, 1, 2, 3), q - quat(1, 1, 1, 1));
		Assert::AreEqual(quat(0, -1, -2, -3), quat(1, 1, 1, 1) - q);

		Assert::AreEqual(quat(10, 20, 30, 40), q * 10);
		Assert::AreEqual(quat(10, 20, 30, 40), 10 * q);

		Assert::AreEqual(quat(0.5f, 1, 1.5f, 2), q / 2);
		Assert::AreEqual(quat(2, 1, 2.f / 3, 0.5f), 2 / q);

		// Hamilton product
		quat neg_identity(0, 0, 0, -1);
		Assert::AreEqual(neg_identity, quat::i * quat::i);
		Assert::AreEqual(neg_identity, quat::j * quat::j);
		Assert::AreEqual(neg_identity, quat::k * quat::k);
		Assert::AreEqual(neg_identity, (quat::i * quat::j) * quat::k);

		Assert::AreEqual(quat::k, quat::i * quat::j, L"ij = k");
		Assert::AreEqual(quat::i, quat::j * quat::k, L"jk = i");
		Assert::AreEqual(quat::j, quat::k * quat::i, L"ki = j");
		Assert::AreEqual(-quat::k, quat::j * quat::i, L"ji = -k");
		Assert::AreEqual(-quat::i, quat::k * quat::j, L"kj = -i");
		Assert::AreEqual(-quat::j, quat::i * quat::k, L"ik = -j");

		quat p(2, 3, 4, 1);
		quat r(10, 11, 12, 9);

		Assert::AreEqual(p * (q * r), (p * q) * r);
		Assert::AreEqual(p*(5 * q + 7 * r), 5 * (p*q) + 7 * (p*r), L"linearity: p(5q + 7r) = 5pq + 7pr");
		Assert::AreEqual((5 * p + 7 * q)*r, 5 * (p*r) + 7 * (q*r), L"linearity: (5p + 7q)r = 5pr + 7qr");

		Assert::AreEqual(q * 5, q*quat(0, 0, 0, 5));

		// Hamilton product compaund assignment operator
		quat p1 = p;
		Assert::AreEqual(p * q * r, (p1 *= q) *= r);
	}

	TEST_METHOD(compound_assignment_operators)
	{
		quat q(5, 6, 7, 8);
		quat r(1, 2, 3, 4);

		(q += r) += r;
		Assert::AreEqual(quat(7, 10, 13, 16), q);

		(q -= r) -= r;
		Assert::AreEqual(quat(5, 6, 7, 8), q);

		(q *= 2) *= 3;
		Assert::AreEqual(quat(30, 36, 42, 48), q);

		(q /= 3) /= 2;
		Assert::AreEqual(quat(5, 6, 7, 8), q);

		// NOTE(ref2401): Hamilton product compaund assignment operator 
		// is tested in the binary_operators test method.
	}

	TEST_METHOD(ctors)
	{
		quat q0;
		Assert::IsTrue((q0.x == 0) && (q0.y == 0) && (q0.z == 0) && (q0.a == 0));

		quat q1(1, 2, 3, 4);
		Assert::IsTrue((q1.x == 1) && (q1.y == 2) && (q1.z == 3) && (q1.a == 4));

		quat q2(float3(1, 2, 3), 4);
		Assert::IsTrue((q2.x == 1) && (q2.y == 2) && (q2.z == 3) && (q2.a == 4));

		// copy ctor.
		quat qc = q1;
		Assert::IsTrue((qc.x == q1.x) && (qc.y == q1.y) && (qc.z == q1.z) && (qc.a == q1.a));

		// move ctor.
		quat qm = std::move(qc);
		Assert::IsTrue((qm.x == q1.x) && (qm.y == q1.y) && (qm.z == q1.z) && (qm.a == q1.a));
	}

	TEST_METHOD(conjugate)
	{
		using math::approx_equal;
		using math::conjugate;
		using math::len;

		quat q(2, 3, 4, 1);
		quat r(6, 7, 8, 5);

		Assert::IsTrue(approx_equal(len(q), len(conjugate(q))), L"|q*| = |q|");
		Assert::AreEqual(q, conjugate(conjugate(q)), L"(q*)* = q");
		Assert::AreEqual(conjugate(q + r), conjugate(q) + conjugate(r), L"(q + r)* = q* + r*");
		Assert::AreEqual(conjugate(q * r), conjugate(r) * conjugate(q), L"(qr)* = r*q*");
	}

	TEST_METHOD(equal_operator)
	{
		quat q(1, 2, 3, 4);

		Assert::AreNotEqual(q, quat(100, 2, 3, 4));
		Assert::AreNotEqual(q, quat(1, 100, 3, 4));
		Assert::AreNotEqual(q, quat(1, 2, 100, 4));
		Assert::AreNotEqual(q, quat(1, 2, 3, 100));

		Assert::AreEqual(q, q);
		Assert::AreEqual(q, quat(1, 2, 3, 4));
	}

	TEST_METHOD(inverse)
	{
		using math::inverse;

		Assert::AreEqual(quat::identity, inverse(quat::identity));

		quat q = quat(2, 3, 4, 5);

		Assert::AreEqual(quat::identity, q * inverse(q));
		Assert::AreEqual(quat::identity, inverse(q) * q);
	}

	TEST_METHOD(is_normalized)
	{
		using math::is_normalized;
		using math::len;

		Assert::IsTrue(is_normalized(quat::i));
		Assert::IsTrue(is_normalized(quat::j));
		Assert::IsTrue(is_normalized(quat::k));
		Assert::IsTrue(is_normalized(quat::identity));

		quat q(1, 2, 3, 4);
		Assert::IsTrue(len(q) > 1 && (!is_normalized(q)));
	}

	TEST_METHOD(len_and_len_squared)
	{
		using math::approx_equal;
		using math::len_squared;
		using math::len;

		quat q(2, 3, 4, 5);
		quat r(4, 5, 6, 7);

		Assert::AreEqual(2.0f * 2 + 3 * 3 + 4 * 4 + 5 * 5, len_squared(q));
		Assert::AreEqual(std::sqrt(2.0f * 2 + 3 * 3 + 4 * 4 + 5 * 5), len(q));

		Assert::AreEqual(2 * len(q), len(2 * q), L"|aQ| = |a| * |Q|");

		Assert::IsTrue(
			approx_equal(len(q + r),
			len(q) + len(r), 0.1f),
			L"|Q + P| <= |Q| + |P|");

		Assert::IsTrue(
			approx_equal(len(q * r),
			len(q) * len(r)),
			L"|QP| = |Q| * |P|");
	}

	TEST_METHOD(normalize)
	{
		using math::approx_equal;
		using math::len;
		using math::normalize;

		Assert::AreEqual(quat::zero, normalize(quat::zero));
		Assert::AreEqual(quat::identity, normalize(quat::identity));

		quat q = quat(6, 7, -8, 0);
		Assert::IsTrue(approx_equal(1.f, len(normalize(q))));
	}

	TEST_METHOD(slerp)
	{
		using math::is_normalized;
		using math::normalize;
		using math::slerp;

		quat q = normalize(quat(1, 2, 3, 4));
		quat r = normalize(quat(5, 6, 7, 8));
		Assert::AreEqual(q, slerp(q, r, 0.f));
		Assert::AreEqual(r, slerp(q, r, 1.f));

		quat qs = slerp(q, r, 0.5f);
		Assert::IsTrue(is_normalized(qs));
	}

	TEST_METHOD(static_members)
	{
		Assert::AreEqual(quat(1, 0, 0, 0), quat::i);
		Assert::AreEqual(quat(0, 1, 0, 0), quat::j);
		Assert::AreEqual(quat(0, 0, 1, 0), quat::k);
		Assert::AreEqual(quat(0, 0, 0, 1), quat::identity);
		Assert::AreEqual(quat(0, 0, 0, 0), quat::zero);
	}

	TEST_METHOD(unary_operators)
	{
		quat q(1, 2, 3, 4);

		Assert::AreEqual(quat(-1, -2, -3, -4), -q);
		Assert::AreEqual(quat(1, 2, 3, 4), -(-q));
	}
};

} // namespace unittest
