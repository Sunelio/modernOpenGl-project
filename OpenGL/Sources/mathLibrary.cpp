#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <ctime>
#include<mathLibrary.hpp>

using namespace Core;
using namespace Maths;

const Vector2D Vector2D::zero = {0, 0};
const Vector2D Vector2D::up = {0, 1};
const Vector2D Vector2D::left = {-1, 0};
const Vector2D Vector2D::down = {0, -1};
const Vector2D Vector2D::right = {1, 0};

Vector2D::Vector2D()
{
    x = 0;
    y = 0;
}

Vector2D::~Vector2D()
{
}
Vector2D::Vector2D(const float x,const float y)
{
    this->x = x;
    this->y = y;
}
Vector2D::Vector2D(const int x,  const int y)
{
    this->x = (float)x;
    this->y = (float)y;
}
Vector2D::Vector2D(const int number)
{
    x = number;
    y = number;
}
Vector2D::Vector2D(const Vector4D& v)
{
    x = v.x;
    y = v.y;
}

// Get angle of degree from a vector to a another.
// The angle is between 0 and 180 degree
float GetDegreAngle(Vector2D& a, Vector2D& b)
{
    Vector2D aNor = a.Normalize();
    Vector2D bNor = b.Normalize();
    float dot = aNor.DotProduct2D(bNor);
    return radToDeg(acos(dot));
}

float GeDegreeAngle(Vector3D& a, Vector3D& b)
{
    a.Normalize();
    b.Normalize();
    float dot = DotProduct3D(a, b);
    return radToDeg(acos(dot));
}

float GetDegreAngle(Vector4D& a, Vector4D& b)
{
    a.Normalize();
    b.Normalize();
    float dot = DotProduct4D(a, b);
    return radToDeg(acos(dot));
}

// Get angle of degree from a vector to a another.
// The angle is between -180 and 180 degree
float GetSignedDegreAngle(Vector2D& a, Vector2D& b)
{
    float angle = atan2(b.y, b.x) - atan2(a.y, a.x);
    return radToDeg(angle);
}


// Rotate a vector;
void RotateVector2D( Vector2D& direction, float angle)
{
    angle = degToRad(angle);
    Vector2D startVector = direction;
    direction.x = startVector.x * cosf(angle) - (startVector.y * sinf(angle));
    direction.y = startVector.x * sinf(angle) + (startVector.y * cosf(angle));
}

// ---------- Algebric Function -----------------

// Make transition between the start value and the end value
float LerpFloat(const float start, const float end, const float t)
{
    return ((end - start) * t) + start;
}

Vector2D LerpVector(const Vector2D start, const Vector2D end, const float t)
{
    return ((end - start) * t) + start;
}

//Limit the value of a variable between a max and a min
float ClampFloat(float number, const float min, const float max)
{
    number = number > max ? max : number;
    number = number < min ? min : number;
    return number;
}
int ClampInt(int number, const int min, const int max)
{
    number = number > max ? max : number;
    number = number < min ? min : number;
    return number;
}

//int32_t GetSeed()
//{
//    time_t currentTime;
//    struct tm *localTime;
//    time(&currentTime);
//    localTime = localtime(&currentTime);
//    int32_t seed = localTime->tm_min * localTime->tm_sec * localTime->tm_hour;
//    return seed;
//}

int32_t getRandomNumber(int32_t &state)
{
    uint64_t x = (uint64_t)state;
    int m = (int)pow(2, 31);
    int a = 1103515245;
    int c = 12345;
    uint64_t result = (a * x + c) % m; // La formule

    return result;
}

int RandomNumber(int32_t &state, const int min, const int max)
{
    state = getRandomNumber(state);
    int number = state % (max - 1 - min);
    number += min;
    return number;
}

float RandomNumber(int32_t &state, const float min, const float max)
{
    state = getRandomNumber(state);
    float number = state / (RAND_MAX / (max - 1 - min));
    number += min;
    return number;
}

const int GetSign(const float f)
{
    if (f > 0.f)
        return 1;
    if (f < 0.f)
        return -1;

    return 0;
}

//--------------- Vector 3 ------------ //

Vector3D::Vector3D()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Vector3D::Vector3D(const Vector4D& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
}
Vector3D::Vector3D(const float c1, const float c2, const float c3)
{
    x = c1;
    y = c2;
    z = c3;
}
Vector3D::~Vector3D()
{
}

const Vector3D Vector3D::zero = {0.0f, 0.0f, 0.f};
const Vector3D Vector3D::up = {0.0f, 1.0f, 0.f};
const Vector3D Vector3D::down = {0.f, -1.f, 0.f};
const Vector3D Vector3D::left = {-1.0f, 0.f, 0.f};
const Vector3D Vector3D::right = {1.f, 0.f, 0.f};
const Vector3D Vector3D::forward = {0.f, 0.f, 1.f};
const Vector3D Vector3D::back = {0.f, 0.f, -1.f};

// --------------- Vector 4 ------------ //

const Vector4D Vector4D::zero = {0.0f, 0.0f, 0.f, 1.0f};
const Vector4D Vector4D::up = {0.0f, 1.0f, 0.f, 1.0f};
const Vector4D Vector4D::down = {0.f, -1.f, 0.f, 1.0f};
const Vector4D Vector4D::left = {-1.0f, 0.f, 0.f, 1.0f};
const Vector4D Vector4D::right = {1.f, 0.f, 0.f, 1.0f};
const Vector4D Vector4D::forward = {0.f, 0.f, 1.f, 1.0f};
const Vector4D Vector4D::back = {0.f, 0.f, -1.f, 1.0f};

Vector4D::Vector4D(/* args */)
{
}

Vector4D::Vector4D(const float _x, const float _y,  const float _z, const float _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

Vector4D::Vector4D(const Vector3D &vec3, const float _w)
{
    x = vec3.x;
    y = vec3.y;
    z = vec3.z;
    w = _w;
}


Vector4D::~Vector4D()
{
}

// -----------------  Transform ----------------------

Transform::Transform(/* args */)
{
}

Transform::Transform(const Vector3D &pos)
{
    position = pos;
}
Transform::Transform(const Vector3D &pos, const  Vector3D &rot)
{
    position = pos;
    rotation = rot;
}
Transform::Transform(const Vector3D &pos, const Vector3D &rot,const Vector3D &sca)
{
    position = pos;
    rotation = rot;
    scale = sca;
}
Transform::~Transform()
{
}

void Transform::ResetTransform()
{
    position = {0.f, 0.f, 0.0f};
    rotation = {0.f, 0.f, 0.0f};
    scale = {1.f, 1.f, 1.f};
}

// ------------------------- Matrix 4D -----------------------

Matrix4D::Matrix4D()
{
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            c[j][i] = 0.0f;
        }
    }
}

Matrix4D::~Matrix4D()
{
}

Matrix4D Matrix4D::operator+(const Matrix4D m2)
{
    Matrix4D result;
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            result.c[j][i] = c[j][i] + m2.c[j][i];
        }
    }

    return result;
}

Matrix4D Matrix4D::operator-(const Matrix4D m2)
{
    Matrix4D result;
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            result.c[j][i] = c[j][i] - m2.c[j][i];
        }
    }

    return result;
}

Vector4D Matrix4D::operator*(const Vector4D v2)
{
    Vector4D result = {0.0f, 0.0f, 0.f, 0.0f};
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            result.coord[j] += c[i][j] * v2.coord[i];
        }
    }

    return result;
}

Matrix4D Matrix4D::operator*(const Matrix4D m2)
{
    Matrix4D multMatrix;

    for (int k = 0; k < 4; k++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 4; i++)
            {
                multMatrix.c[j][k] += c[i][k] * m2.c[j][i];
            }
        }
    }

    return multMatrix;
}

void Matrix4D::LoadIdentity()
{
    for (int i = 0; i < 4; i++)
    {
        c[i][i] = 1.0f;
    }
}

Matrix4D Matrix4D::Model(Vector3D rotation, const Vector3D& translation, const Vector3D& scale)
{
    Matrix4D rotationMatrix = Matrix4D::CreateXRotationMatrix(rotation.x) * Matrix4D::CreateYRotationMatrix(rotation.y) * Matrix4D::CreateZRotationMatrix(rotation.z);
    Matrix4D translationMatrix = Matrix4D::CreateTranslationMatrix(translation);
    Matrix4D scaleMatrix = Matrix4D::CreateScaleMatrix(scale);


    return scaleMatrix * rotationMatrix * translationMatrix;
}

Matrix4D Matrix4D::CreateTranslationMatrix(const Vector3D &translation)
{
    Matrix4D transMatrix;
    transMatrix.LoadIdentity();

    transMatrix.c[3][0] = translation.x;
    transMatrix.c[3][1] = translation.y;
    transMatrix.c[3][2] = translation.z;

    return transMatrix;
}

Matrix4D Matrix4D::CreateScaleMatrix(const Vector3D &scale)
{
    Matrix4D scaled;
    scaled.LoadIdentity();
    scaled.c[0][0] = scale.x;
    scaled.c[1][1] = scale.y;
    scaled.c[2][2] = scale.z;

    return scaled;
}

Matrix4D Matrix4D::CreateXRotationMatrix(float angle)
{
    Matrix4D rotXMat;
    rotXMat.LoadIdentity();
    angle = angle * M_PI / 180.0f;
    rotXMat.c[1][1] = cosf(angle);
    rotXMat.c[1][2] = sinf(angle);
    rotXMat.c[2][1] = -sinf(angle);
    rotXMat.c[2][2] = cosf(angle);

    return rotXMat;
}

Matrix4D Matrix4D::CreateYRotationMatrix(float angle)
{
    Matrix4D rotYMat;
    rotYMat.LoadIdentity();
    angle = angle * M_PI / 180.0f;
    rotYMat.c[0][0] = cosf(angle);
    rotYMat.c[0][2] = -sinf(angle);
    rotYMat.c[2][0] = sinf(angle);
    rotYMat.c[2][2] = cosf(angle);

    return rotYMat;
}

Matrix4D Matrix4D::CreateZRotationMatrix(float angle)
{
    Matrix4D rotZMat;
    rotZMat.LoadIdentity();
    angle = angle * M_PI / 180.0f;
    rotZMat.c[0][0] = cosf(angle);
    rotZMat.c[1][0] = -sinf(angle);
    rotZMat.c[0][1] = sinf(angle);
    rotZMat.c[1][1] = cosf(angle);

    return rotZMat;
}


Matrix4D Matrix4D::CreateTransformMatrix(const Transform &trans)
{
    Matrix4D transfMatrix;
    transfMatrix = CreateTranslationMatrix(trans.position);
    transfMatrix = transfMatrix * CreateYRotationMatrix(trans.rotation.y);
    transfMatrix = transfMatrix * CreateXRotationMatrix(trans.rotation.x);
    transfMatrix = transfMatrix * CreateZRotationMatrix(trans.rotation.z);
    transfMatrix = transfMatrix * CreateScaleMatrix(trans.scale);

    return transfMatrix;
}

Matrix4D Matrix4D::TransposeMatrix(const Matrix4D&   matrix)
{
    Matrix4D matTransp;

    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            matTransp.c[i][j] = matrix.c[j][i];
        }
    }
    return matTransp;
}

float Matrix4D::Determinant2x2(const Matrix4D& matrix)
{
    float det = 0.0f;
    det = matrix.c[0][0] * matrix.c[1][1] - matrix.c[0][1] * matrix.c[1][0];
    return det;
}

Matrix4D Matrix4D::Mat3x3ToMat2x2( const int row, const int columns, const Matrix4D& mat3x3)
{
    Matrix4D mat2x2;
    int index = 0;
    for (int j = 0; j < 3; j++)
    {
        if (j != columns)
        {
            for (int i = 0; i < 3; i++)
            {
                if (i != row)
                {
                    mat2x2.c[index / 2][index % 2] = mat3x3.c[j][i];
                    index++;
                }
            }
        }
    }

    return mat2x2;
}

int Matrix4D::MatrixSignElement(int index)
{
    if (index % 2 == 0)
        return 1;
    else
        return -1;
}

float Matrix4D::Determinant3x3(const Matrix4D& matrix)
{
    float det = 0.0f;

    for (int j = 0; j < 3; j++)
    {
        Matrix4D mat2x2 = Matrix4D::Mat3x3ToMat2x2(0, j, matrix);
        det += MatrixSignElement(j) * matrix.c[j][0] * Determinant2x2(mat2x2);
    }
    return det;
}

Matrix4D Matrix4D::Mat4x4ToMat3x3(const int row, const int columns,const Matrix4D& mat4x4)
{

    Matrix4D mat3x3;
    int index = 0;
    for (int j = 0; j < 4; j++)
    {
        if (j != columns)
        {
            for (int i = 0; i < 4; i++)
            {
                if (i != row)
                {
                    mat3x3.c[index / 3][index % 3] = mat4x4.c[j][i];
                    index++;
                }
            }
        }
    }

    return mat3x3;
}

float Matrix4D::Determinant4x4(const Matrix4D&  matrix)
{
    float det = 0.0f;

    for (int j = 0; j < 4; j++)
    {
        Matrix4D mat3x3 = Matrix4D::Mat4x4ToMat3x3(0, j, matrix);
        det += MatrixSignElement(j) * matrix.c[j][0] * Determinant3x3(mat3x3);
    }
    return det;
}

Matrix4D Matrix4D::MatrixCofacteur(const Matrix4D&  mat4x4)
{
    Matrix4D mat4x4Cof;
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            Matrix4D mat3x3 = Matrix4D::Mat4x4ToMat3x3(i, j, mat4x4);
            mat4x4Cof.c[j][i] = Matrix4D::MatrixSignElement(j + i) * Determinant3x3(mat3x3);
        }
    }

    return mat4x4Cof;
}

Matrix4D Matrix4D::InverseMatrix(const Matrix4D&  matrix)
{
    Matrix4D matInverse;
    Matrix4D mat4x4 = Matrix4D::MatrixCofacteur(matrix);
    mat4x4 = TransposeMatrix(mat4x4);
    float det = Matrix4D::Determinant4x4(matrix);
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            matInverse.c[j][i] = (1 / det) * mat4x4.c[j][i];
        }
    }
    return matInverse;
}

Vector4D CompareMaxXValue(const Vector4D &v1, const Vector4D &v2)
{
    Vector4D maxVec;

    if (v1.x > v2.x)
        return maxVec = v1;
    else
        return maxVec = v2;
}

Vector4D CompareMinXValue(const Vector4D &v1, const Vector4D &v2)
{
    Vector4D minVec;

    if (v1.x > v2.x)
        return minVec = v2;
    else
        return minVec = v1;
}

Vector4D CompareMaxYValue(const Vector4D &v1, const Vector4D &v2)
{
    Vector4D maxVec;

    if (v1.y > v2.y)
        return maxVec = v1;
    else
        return maxVec = v2;
}

Vector4D CompareMinYValue(const Vector4D &v1, const Vector4D &v2)
{
    Vector4D minVec;

    if (v1.y > v2.y)
        return minVec = v2;
    else
        return minVec = v1;
}