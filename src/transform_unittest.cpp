#include "math/transform.h"

#include "CppUnitTest.h"

using math::float2;
using math::float3;
using math::float4;
using math::quat;
using math::float3x3;
using math::float4x4;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

template<> inline std::wstring ToString<float2>(const float2& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<float3>(const float3& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<float4>(const float4& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<quat>(const quat& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<float3x3>(const float3x3& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring ToString<float4x4>(const float4x4& t) { RETURN_WIDE_STRING(t); }

}}} // namespace Microsoft::VisualStudio::CppUnitTestFramework


namespace unittest {

TEST_CLASS(math_transform_fucns) {
public:

	TEST_METHOD(from_axis_angle_rotation)
	{
		using math::approx_equal;
		using math::from_axis_angle_rotation;
		using math::is_normalized;
		using math::normalize;

		const float3 axis = normalize(float3(-3.0f, 5.4f, -2.0f));
		const quat q = from_axis_angle_rotation(axis, math::pi_2);

		Assert::IsTrue(is_normalized(q));
		Assert::IsTrue(approx_equal(q.a, std::cos(math::pi_4)));
	}

	TEST_METHOD(from_rotation_matrix)
	{
		using math::from_axis_angle_rotation;
		using math::from_rotation_matrix;
		using math::normalize;
		using math::rotation_matrix;

		Assert::AreEqual(quat::zero, from_rotation_matrix(float3x3::zero));
		Assert::AreEqual(quat::zero, from_rotation_matrix(float4x4::zero));
		Assert::AreEqual(quat::identity, from_rotation_matrix(float3x3::identity));
		Assert::AreEqual(quat::identity, from_rotation_matrix(float4x4::identity));

		const float3 axis = normalize(float3(1, 2, 5));
		const float angle = math::pi_4;
		const quat expected_quat = from_axis_angle_rotation(axis, angle);

		const float4x4 mR = rotation_matrix<float4x4>(axis, angle);
		const quat actual_quat = from_rotation_matrix(mR);
		Assert::IsTrue(approx_equal(expected_quat, actual_quat));
	}

	TEST_METHOD(ox_oy_oz)
	{
		using math::ox;
		using math::oy;
		using math::oz;
		using math::set_ox;
		using math::set_oy;
		using math::set_oz;


		float3x3 m3(
			0, 1, 2,
			3, 4, 5,
			6, 7, 8);

		Assert::AreEqual(float3(0, 3, 6), ox(m3));
		Assert::AreEqual(float3(1, 4, 7), oy(m3));
		Assert::AreEqual(float3(2, 5, 8), oz(m3));

		set_ox(m3, float3(21, 22, 23));
		set_oy(m3, float3(24, 25, 26));
		set_oz(m3, float3(27, 28, 29));
		Assert::AreEqual(float3x3(21, 24, 27, 22, 25, 28, 23, 26, 29), m3);


		float4x4 m4(
			0, 1, 2, 3,
			4, 5, 6, 7,
			8, 9, 10, 11,
			12, 13, 14, 15);

		Assert::AreEqual(float3(0, 4, 8), ox(m4));
		Assert::AreEqual(float3(1, 5, 9), oy(m4));
		Assert::AreEqual(float3(2, 6, 10), oz(m4));

		set_ox(m4, float3(21, 22, 23));
		set_oy(m4, float3(24, 25, 26));
		set_oz(m4, float3(27, 28, 29));
		Assert::AreEqual(float4x4(21, 24, 27, 3, 22, 25, 28, 7, 23, 26, 29, 11, 12, 13, 14, 15), m4);
	}

	TEST_METHOD(orthographic_matrix_directx)
	{
		using math::orthographic_matrix_directx;

		constexpr float width = 800.0f;
		constexpr float height = 600.0f;
		constexpr float near = -5.0f;
		constexpr float far = 100.f;

		// manual computation of (left, right, bottom, top, near, far) tuple
		const float hw = width * 0.5f;
		const float hh = height * 0.5f;

		const float4x4 om1 = orthographic_matrix_directx(-hw, hw, -hh, hh, near, far);
		const float4x4 om2 = orthographic_matrix_directx(width, height, near, far);
		Assert::IsTrue(approx_equal(om1, om2));
	}

	TEST_METHOD(orthographic_matrix_opengl)
	{
		using math::orthographic_matrix_opengl;

		constexpr float width = 800.0f;
		constexpr float height = 600.0f;
		constexpr float near = -5.0f;
		constexpr float far = 10.0f;

		// manual computation of (left, right, bottom, top, near, far) tuple
		const float hw = width * 0.5f;
		const float hh = height * 0.5f;

		const float4x4 om1 = orthographic_matrix_opengl(-hw, hw, -hh, hh, near, far);
		const float4x4 om2 = orthographic_matrix_opengl(width, height, near, far);
		Assert::IsTrue(approx_equal(om1, om2));
	}

	TEST_METHOD(perspective_matrix_directx)
	{
		using math::perspective_matrix_directx;

		constexpr float near = 1.0f;
		constexpr float far = 100.0f;
		constexpr float fov = math::pi_2;
		constexpr float ratio = 800.0f / 600.0f;

		// manual computation of (left, right, bottom, top, near, far) tuple
		const float height = near * std::tan(fov * 0.5f);
		const float width = height * ratio;

		const float4x4 pm1 = perspective_matrix_directx(-width, width, -height, height, near, far);
		const float4x4 pm2 = perspective_matrix_directx(fov, ratio, near, far);
		Assert::IsTrue(approx_equal(pm1, pm2));
	}

	TEST_METHOD(perspective_matrix_opengl)
	{
		using math::perspective_matrix_opengl;

		constexpr float near = 1.0f;
		constexpr float far = 100.0f;
		constexpr float fov = math::pi_2;
		constexpr float ratio = 800.0f / 600.0f;

		// manual computation of (left, right, bottom, top, near, far) tuple
		const float height = near * std::tan(fov / 2.0f);
		const float width = height * ratio;

		const float4x4 pm1 = perspective_matrix_opengl(-width, width, -height, height, near, far);
		const float4x4 pm2 = perspective_matrix_opengl(fov, ratio, near, far);
		Assert::IsTrue(approx_equal(pm1, pm2));
	}

	TEST_METHOD(position_get_set)
	{
		using math::position;
		using math::set_position;

		float4x4 m(
			0, 0, 0, 24,
			0, 0, 0, 42,
			0, 0, 0, 60,
			0, 0, 0, 0);

		Assert::AreEqual(float3(24, 42, 60), position(m));

		set_position(m, float3(1, 2, 3));
		Assert::AreEqual(float3(1, 2, 3), position(m));
	}

	TEST_METHOD(rotate)
	{
		using math::mul;
		using math::from_axis_angle_rotation;
		using math::normalize;
		using math::rotate;
		using math::rotation_matrix;


		const float3 point(17, 100, -3);
		const float3 axis = normalize(float3(-5, 3, 2));
		const float angle = math::pi_32;
		const float3 expected_point = mul(rotation_matrix<float3x3>(axis, angle), point);
		

		const quat q = from_axis_angle_rotation(axis, angle);
		Assert::IsTrue(approx_equal(expected_point, rotate(q, point)));
	}

	TEST_METHOD(rotation_matrix_quat)
	{
		using math::approx_equal;
		using math::from_axis_angle_rotation;
		using math::inverse;
		using math::is_orthogonal;
		using math::mul;
		using math::normalize;
		using math::rotation_matrix;


		Assert::AreEqual(float3x3::zero, rotation_matrix<float3x3>(quat::zero));
		Assert::AreEqual(float3x3::identity, rotation_matrix<float3x3>(quat::identity));
		Assert::AreEqual(float4x4::identity, rotation_matrix<float4x4>(quat::identity));
		Assert::AreEqual(float4x4::identity, rotation_matrix<float4x4>(quat::identity));

		const float3 axis = normalize(float3(-5, 7, 1));
		const float angle = math::pi_2;
		const quat q = from_axis_angle_rotation(axis, angle);

		const float3x3 r3 = rotation_matrix<float3x3>(q);
		Assert::IsTrue(is_orthogonal(r3));
		Assert::IsTrue(approx_equal(r3, rotation_matrix<float3x3>(axis, angle)));

		const float4x4 r4 = rotation_matrix<float4x4>(q);
		Assert::IsTrue(is_orthogonal(r4));
		Assert::IsTrue(approx_equal(r4, rotation_matrix<float4x4>(axis, angle)));

		// conjugation operation test
		const float3 p(3, -7, 1);
		const float3x3 mR = rotation_matrix<float3x3>(q);
		const float3 res_mat_p = mul(mR, p); // rotation matrix * p

		const quat pq = quat(p, 0);
		const quat mult_prod = (q * pq) * inverse(q); // p' = qpq^(-1) = qpq* - conjugation operation
		const float3 res_quat_conj = float3(mult_prod.x, mult_prod.y, mult_prod.z);
		Assert::IsTrue(approx_equal(res_mat_p, res_quat_conj), L"p' = qpq^(-1) = qpq* and RotationMatrix * vector");
	}

	TEST_METHOD(rotation_matrix_axis_angle)
	{
		using math::approx_equal;
		using math::inverse;
		using math::is_orthogonal;
		using math::normalize;
		using math::rotation_matrix;
		using math::trace;
		using math::transpose;

		Assert::AreEqual(float3x3::identity, rotation_matrix<float3x3>(float3::unit_x, 0.0f));
		Assert::AreEqual(float4x4::identity, rotation_matrix<float4x4>(float3::unit_x, 0.0f));

		const float3 axis = normalize(float3(-4, -5, 1));
		// For every 3x3 rotation matrix, that rotates by any radians around any axis, 
		// the trace is constant independent of axis.
		const float angle = math::pi_4;
		const float expected_trace = 1.0f + 2.0f * std::cos(angle);
		const float3x3 r3 = rotation_matrix<float3x3>(axis, angle);
		Assert::IsTrue(approx_equal(expected_trace, trace(r3)));

		// M: mat4
		const float4x4 r = rotation_matrix<float4x4>(axis, angle);
		Assert::IsTrue(is_orthogonal(r));
		Assert::IsTrue(is_orthogonal(transpose(r)));
		Assert::IsTrue(approx_equal(std::abs(det(r)), 1.0f), L"|r| == +/-1");
		Assert::IsTrue(approx_equal(transpose(r), inverse(r)));
	}

	TEST_METHOD(rotation_matrix_look_at)
	{
		using math::rotation_matrix;

		// rotation around the OX axis
		const float3x3 oxM1 = rotation_matrix<float3x3>(float3::zero, float3::unit_y, -float3::unit_z);
		Assert::IsTrue(approx_equal(oxM1, rotation_matrix<float3x3>(float3::unit_x, -math::pi_2))); // -pi_2 - counter clockwise

		 // rotation arount the OY axis
		const float3x3 oyM1 = rotation_matrix<float3x3>(-float3::unit_z, float3::zero, float3::unit_y);
		Assert::IsTrue(approx_equal(oyM1, float3x3::identity));

		const float3x3 oyM2 = rotation_matrix<float3x3>(float3::zero, float3(1, 0, 1), float3::unit_y);
		Assert::IsTrue(approx_equal(oyM2, rotation_matrix<float3x3>(float3::unit_y, math::pi_4)));

		const float4x4 oyM3 = rotation_matrix<float4x4>(float3(0, 0, 7), float3(0, 0, -1), float3::unit_y);
		Assert::IsTrue(approx_equal(oyM3, rotation_matrix<float4x4>(float3::unit_y, math::pi)));
	}

	TEST_METHOD(rotation_matrix_ox_oy_oz)
	{
		using math::approx_equal;
		using math::rotation_matrix;
		using math::rotation_matrix_ox;
		using math::rotation_matrix_oy;
		using math::rotation_matrix_oz;
		using math::trace;

		Assert::AreEqual(float3x3::identity, rotation_matrix_ox<float3x3>(0.0f));
		Assert::AreEqual(float3x3::identity, rotation_matrix_oy<float3x3>(0.0f));
		Assert::AreEqual(float3x3::identity, rotation_matrix_oz<float3x3>(0.0f));
		Assert::AreEqual(float4x4::identity, rotation_matrix_ox<float4x4>(0.0f));
		Assert::AreEqual(float4x4::identity, rotation_matrix_oy<float4x4>(0.0f));
		Assert::AreEqual(float4x4::identity, rotation_matrix_oz<float4x4>(0.0f));

		// For every 3x3 rotation matrix, that rotates by any radians around any axis, 
		// the trace is constant independent of axis.
		const float angle = math::pi_4;
		const float expected_trace = 1.0f + 2.0f * std::cos(angle);

		const float3x3 r_ox = rotation_matrix_ox<float3x3>(angle);
		const float3x3 r_oy = rotation_matrix_oy<float3x3>(angle);
		const float3x3 r_oz = rotation_matrix_oz<float3x3>(angle);

		Assert::IsTrue(approx_equal(expected_trace, trace(r_ox)));
		Assert::IsTrue(approx_equal(expected_trace, trace(r_oy)));
		Assert::IsTrue(approx_equal(expected_trace, trace(r_oz)));

		// TRetMat: mat3
		Assert::IsTrue(approx_equal(r_ox, rotation_matrix<float3x3>(float3::unit_x, angle)));
		Assert::IsTrue(approx_equal(r_oy, rotation_matrix<float3x3>(float3::unit_y, angle)));
		Assert::IsTrue(approx_equal(r_oz, rotation_matrix<float3x3>(float3::unit_z, angle)));

		// TRetMat: mat4
		Assert::IsTrue(approx_equal(rotation_matrix_ox<float4x4>(angle), rotation_matrix<float4x4>(float3::unit_x, angle)));
		Assert::IsTrue(approx_equal(rotation_matrix_oy<float4x4>(angle), rotation_matrix<float4x4>(float3::unit_y, angle)));
		Assert::IsTrue(approx_equal(rotation_matrix_oz<float4x4>(angle), rotation_matrix<float4x4>(float3::unit_z, angle)));
	}

	TEST_METHOD(scale_matrix)
	{
		using math::scale_matrix;

		Assert::AreEqual(float3x3(4, 0, 0, 0, 5, 0, 0, 0, 6), scale_matrix<float3x3>(float3(4, 5, 6)));
		Assert::AreEqual(float4x4(7, 0, 0, 0, 0, 8, 0, 0, 0, 0, 9, 0, 0, 0, 0, 1), scale_matrix<float4x4>(float3(7, 8, 9)));
	}

	TEST_METHOD(tr_matrix_pos_quat)
	{
		using math::approx_equal;
		using math::from_axis_angle_rotation;
		using math::normalize;
		using math::rotation_matrix;
		using math::tr_matrix;
		using math::translation_matrix;

		const quat q = from_axis_angle_rotation(normalize(float3(-5, 3, -10)), math::pi_4);
		const float3 pos(7, 8, 9);

		Assert::IsTrue(approx_equal(translation_matrix(pos) * rotation_matrix<float4x4>(q), tr_matrix(pos, q)));
	}

	TEST_METHOD(tr_matrix_pos_look_at)
	{
		using math::rotation_matrix;
		using math::tr_matrix;
		using math::translation_matrix;

		const float3 p(4, -1, 8);
		const float3 t(1, 1, -8);
		Assert::IsTrue(approx_equal(translation_matrix(p) * rotation_matrix<float4x4>(p, t), tr_matrix(p, t)));
	}

	TEST_METHOD(translation_matrix)
	{
		using math::translation_matrix;

		float3 pos(5, 6, 7);
		float4x4 expected_matrix = float4x4::identity;
		expected_matrix.m03 = pos.x;
		expected_matrix.m13 = pos.y;
		expected_matrix.m23 = pos.z;

		Assert::AreEqual(expected_matrix, translation_matrix(pos));
	}

	TEST_METHOD(trs_matrix)
	{
		using math::from_axis_angle_rotation;
		using math::normalize;
		using math::rotation_matrix;
		using math::scale_matrix;
		using math::trs_matrix;
		using math::translation_matrix;

		const float3 p(7, 8, 9);
		const quat q = from_axis_angle_rotation(normalize(float3(-5, 3, -10)), math::pi_4);
		const float3 s(2, 3, 4);

		const float4x4 mT = translation_matrix(p);
		const float4x4 mR = rotation_matrix<float4x4>(q);
		const float4x4 mS = scale_matrix<float4x4>(s);

		Assert::IsTrue(approx_equal(mT * mR * mS, trs_matrix(p, q, s)));
	}

	TEST_METHOD(ts_matrix)
	{
		using math::scale_matrix;
		using math::translation_matrix;
		using math::ts_matrix;

		const float3 pos(1, 2, 3);
		const float3 scale(4, 5, 6);
		Assert::IsTrue(approx_equal(translation_matrix(pos) * scale_matrix<float4x4>(scale), ts_matrix(pos, scale)));
	}
};

} // namespace unittest
