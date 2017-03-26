#include "math/vector_float.h"

namespace math {

const float2 float2::unit_x(1, 0);
const float2 float2::unit_y(0, 1);
const float2 float2::unit_xy(1);
const float2 float2::zero(0);

const float3 float3::unit_x(1, 0, 0);
const float3 float3::unit_y(0, 1, 0);
const float3 float3::unit_z(0, 0, 1);
const float3 float3::unit_xy(1, 1, 0);
const float3 float3::unit_xyz(1);
const float3 float3::zero(0);


std::ostream& operator<<(std::ostream& out, const float2& v)
{
	out << "float2(" << v.x << ", " << v.y << ")";
	return out;
}

std::wostream& operator<<(std::wostream& out, const float2& v)
{
	out << "float2(" << v.x << ", " << v.y << ")";
	return out;
}

std::ostream& operator<<(std::ostream& out, const float3& v)
{
	out << "float3(" << v.x << ", " << v.y << ", " << v.z << ")";
	return out;
}

std::wostream& operator<<(std::wostream& out, const float3& v)
{
	out << "float3(" << v.x << ", " << v.y << ", " << v.z << ")";
	return out;
}

//std::ostream& operator<<(std::ostream& out, const float4& v)
//{
//	out << "float4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
//	return out;
//}
//
//std::wostream& operator<<(std::wostream& out, const float4& v)
//{
//	out << "float4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
//	return out;
//}

} // namespace math