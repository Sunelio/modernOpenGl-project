#pragma once
#include <mathLibrary.hpp>
typedef unsigned int uint;

union float3
{
    float e[3];
    struct
    {
        float x;
        float y;
        float z;
    };
};

union float4
{
    float4() = default;
    float4(float x, float y, float z, float w)
        : x(x), y(y), z(z), w(w)
    {
    }

    float4(float3 xyz, float w)
        : x(xyz.x), y(xyz.y), z(xyz.z), w(w)
    {
    }

    
    float4(Vector4D xyz)
        : x(xyz.x), y(xyz.y), z(xyz.z), w(xyz.w)
    {
    }

    float e[4];
    struct
    {
        float x;
        float y;
        float z;
        float w;
    };
    struct
    {
        float r;
        float g;
        float b;
        float a;
    };
    float3 xyz;

    float4 operator+(float4 f2)
    {
        return {x + f2.x, y + f2.y, z + f2.z, w + f2.w};
    }
    float4 operator-(float4 f2)
    {
        return {x - f2.x, y - f2.y, z - f2.z, w - f2.w};
    }
    float4 operator*(float f2)
    {
        return {x * f2, y * f2, z * f2, w * f2};
    }
    float4 operator/(float f2)
    {
        return {x / f2, y / f2, z / f2, w / f2};
    }

    float4 &operator=(const Vector4D &vec)
    {

        r = vec.r;
        g = vec.g;
        b = vec.b;
        a = vec.a;
        return *this;
    }
    Vector4D operator=(Vector4D &vec)
    {
        vec.r = r;
        vec.g = g;
        vec.b = b;
        vec.a = a;
        return vec;
    }
};

union mat4x4
{
    float e[16];
    float4 c[4];
};