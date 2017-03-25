Tiny 3d math. Move along, there's nothing to see here.


## vectors
```c++
vector_float.h {float2/3/4, quat}
vector_int.h {ubyte2/3/4 int2/3/4, uint2/3/4}
vector_convert.h

vector_traits {
	constexpr size_t component_count = ...;
	using component_type = ...;
}

operator>
operator>=
operator== exact equality

aspect_ratio<T>(vec)
template<Vec, Component = vector_traits<Vec>::component_type> 
clamp(Vec, Component min, Component max)
dot(float2/3/4)
len_squared
len
is_normalized (float abs_diff = 1e-2)
lerp
normalize
rgb
rgba
```
Get rid of data/r/g/b/a/width/height/…
Unittests (&float3.x)[0] = x, [1] = y, ...

## matrices
```c++
float3x3, float4x4
```

## utility
```c++
approx_equal
pi, pi_2, ..., 
```

## misc
precompiled headers
