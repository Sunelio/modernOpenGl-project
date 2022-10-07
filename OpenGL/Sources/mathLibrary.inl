#include <mathLibrary.hpp>
#include <iostream>

using namespace Core;
using namespace Maths;
// Add a vector2D with a another vector2D
inline Vector2D Vector2D::operator+(Vector2D const b)
{
    return Vector2D{x + b.x, y + b.y};
}

// Substract a Vector2DD with a another Vector2DD
inline Vector2D Vector2D::operator-(Vector2D const b)
{
    return Vector2D{x - b.x, y - b.y};
}

inline Vector2D Vector2D::operator-(Vector2D const b) const 
{
    return Vector2D{x - b.x, y - b.y};
}


// Multiply a Vector2D by a number
inline Vector2D Vector2D::operator*(float multiplier)
{
    Vector2D result = {0, 0};
    result.x = x * multiplier;
    result.y = y * multiplier;
    return result;
}

// Divide a Vector2D by a number
inline Vector2D Vector2D::operator/(float divider)
{
    x = x / divider;
    y = y / divider;
    return *this;
}

// Substract a Vector2DD with a another Vector2DD
inline Vector2D Vector2D::operator-()
{
    return Vector2D{-x, -y};
}

inline Vector2D Vector2D::operator=(Vector4D const v2)
{
    return Vector2D{v2.x, v2.y};
}
// Compare two Vector2D value to see if there are equal
inline bool Vector2D::operator==(Vector2D const v2)
{
    if (x != v2.x)
        return false;
    if (y != v2.y)
        return false;

    return true;
}

inline bool Vector2D::operator==(Vector2D const v2) const
{
    if (x != v2.x)
        return false;
    if (y != v2.y)
        return false;

    return true;
}

// Compare two Vector2D value to see if there are different
inline bool Vector2D::operator!=(Vector2D const v2)
{
    if (x != v2.x)
        return true;
    if (y != v2.y)
        return true;

    return false;
}

inline Vector2D Vector2D::operator+=(Vector2D const v2)
{
    this->x += v2.x;
    this->y += v2.y;

    return *this;
}

inline Vector2D Vector2D::operator-=(Vector2D const v2)
{
    this->x -= v2.x;
    this->y -= v2.y;

    return *this;
}

inline const Vector2D Vector2D::operator*(const float multiplier) const
{
    const Vector2D newVec = {x * multiplier, y * multiplier};
    return newVec;
}

// Get the direction of vector with two point
inline Vector2D Vector2D::GetDirection2D(const Vector2D& PosB)
{
    return PosB - *this;
}

// Dot Product of two Vector2D
inline float Vector2D::DotProduct2D(const Vector2D& v2)
{
    return x * v2.x + y * v2.y;
}

inline float Vector2D::GetDeterminant2D(const Vector2D& b)
{
    return x * b.y - y * b.x;
}

inline float Vector2D::Magnitude() const
{
    return sqrt(x * x + y * y);
}
inline Vector2D Vector2D::Normalize()
{
    float dist = this->Magnitude();
    Vector2D vecNormal;
    vecNormal = x / dist;
    vecNormal = y / dist;
    return vecNormal;
}

inline Vector2D Vector2D::Normal()
{
    return Vector2D{y, -x};
}

inline float DotProduct2D(Vector2D a, Vector2D b)
{
    return a.x * b.x + a.y * b.y;
}

inline float DotProduct3D(Vector3D a, Vector3D b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float DotProduct4D(Vector4D a, Vector4D b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline Vector2D GetDirection2D(Vector2D posA, Vector2D posB)
{
    return posB - posA;
}

inline float GetDeterminant2D(Vector2D a, Vector2D b)
{
    return a.x * b.y - a.y * b.x;
}

// ------------- Vector 3D -----------------

inline Vector3D Vector3D::operator+(const Vector3D v2)
{
    return Vector3D{x + v2.x, y + v2.y, z + v2.z};
}

inline Vector3D Vector3D::operator-(const Vector3D v2)
{
    return Vector3D{x - v2.x, y - v2.y, z - v2.z};
}

inline Vector3D Vector3D::operator*(const float multiplier)
{
    return Vector3D{x * multiplier, y * multiplier, z * multiplier};
}



inline float Vector3D::GetMagnitude() const
{
    return sqrt(x * x + y * y + z * z);
}

inline void Vector3D::Normalize()
{

    float length = GetMagnitude();
    if (length != 0)
    {

        x = x / length;
        y = y / length;
        z = z / length;
    }
}

inline Vector3D CrossProduct(Vector3D& a, Vector3D& b)
{
    Vector3D v;
    v.x = a.y * b.z - a.z * b.y;
    v.y = a.z * b.x - a.x * b.z;
    v.z = a.x * b.y - a.y * b.x;
    return v;
}

// ------------- Vector 4D -----------------

inline Vector4D Vector4D::operator+(const Vector4D v2)
{
    return Vector4D{x + v2.x, y + v2.y, z + v2.z, w + v2.w};
}

inline Vector4D Vector4D::operator-(const Vector4D v2)
{
    return Vector4D{x - v2.x, y - v2.y, z - v2.z, w - v2.w};
}

inline Vector4D Vector4D::operator-(const Vector4D v2) const
{
    return Vector4D{x - v2.x, y - v2.y, z - v2.z, w - v2.w};
}

inline Vector4D Vector4D::operator*(const float multiplier)
{
    return Vector4D{x * multiplier, y * multiplier, z * multiplier, w * multiplier};
}

inline Vector4D Vector4D::operator*(const Vector4D multiplier)
{
    return Vector4D{x * multiplier.x, y * multiplier.y, z * multiplier.z, w * multiplier.w};
}

inline Vector4D &Vector4D::operator=(const Vector3D v2)
{
    x = v2.x;
    y = v2.y;
    z = v2.z;
    w = 1.0f;
    return *this;
}

inline bool Vector4D::operator<(const  float f1)
{
    if (x < f1)
    {
        if (y < f1)
        {
            if (z < f1)
            {
                return true;
            }
        }
    }
    else
        return false;
}

inline bool Vector4D::operator>(const  float f1)
{
    if (x > f1)
    {
        if (y > f1)
        {
            if (z > f1)
            {
                return true;
            }
        }
    }
    else
        return false;
}

inline bool Vector4D::operator<=(const float f1)
{
    if (x <= f1)
    {
        if (y <= f1)
        {
            if (z <= f1)
            {
                return true;
            }
        }
    }
    else
        return false;
}

template <typename T>
T Lerp(T start, T end, float t)
{
    return ((end - start) * t) + start;
}

inline bool Vector4D::operator==(const Vector4D& v1)
{
    if (x == v1.x && y == v1.y && z == v1.z && w == v1.w)
        return true;
    else
        return false;
}

inline bool Vector4D::operator>=(const float f1)
{
    if (x >= f1)
    {
        if (y >= f1)
        {
            if (z >= f1)
            {
                return true;
            }
        }
    }
    else
        return false;
}

inline void Vector4D::Homogenize()
{
    if (w != 0)
    {
        x = x / w;
        y = y / w;
        z = z / w;
        w = w / w;
    }
    else
    {
        std::cout << "Divide by zero" << __FILE__ << __LINE__ << std::endl;
    }
}

inline Vector4D Vector4D::operator/(float f1)
{
    return {x / f1, y / f1, z / f1, w / f1};
}
inline float Vector4D::GetMagnitude() const
{
    return sqrt(x * x + y * y + z * z + w * w);
}

inline void Vector4D::Normalize()
{
    float length = GetMagnitude();
    x = x / length;
    y = y / length;
    z = z / length;
    w = w / length;
}

inline Vector4D operator/(float f1, Vector4D a)
{
    Vector4D f;
    if (a.x != 0.0f)
        f.x = f1 / a.x;
    else
        f.x = 0.0f;

    if (a.y != 0.0f)
        f.y = f1 / a.y;
    else
        f.y = 0.0f;

    if (a.z != 0.0f)
        f.z = f1 / a.z;
    else
        f.z = 0.0f;

    return {f.x, f.y, f.z, f.w};
}

inline Vector2D operator/(float f1, Vector2D a)
{
    float fx;
    if (a.x != 0.0f)
    {
        fx = f1 / a.x;
    }
    else
    {
        fx = 0.0f;
    }

    float fy;
    if (a.y != 0.0f)
    {
        fy = f1 / a.y;
    }
    else
    {
        fy = 0.0f;
    }

    return {fx, fy};
}

inline Vector4D CrossProduct(Vector4D& a, Vector4D& b)
{
    Vector4D v;
    v.x = a.y * b.z - a.z * b.y;
    v.y = a.z * b.x - a.x * b.z;
    v.z = a.x * b.y - a.y * b.x;
    return v;
}

inline Vector4D CrossProduct(Vector4D& a, Vector4D& b, Vector4D& c)
{
    // ----- Cross Product Version -------
    Vector4D d1 = b - a;
    Vector4D d2 = c - a;
    d1.Normalize();
    d2.Normalize();
    Vector4D v = CrossProduct(d1, d2);
    return v;
}

// -------------- Matrice  4x4 -------------

inline float Matrix4D::operator[](const unsigned int index)
{
    return c[index / 4][index % 4];
}
