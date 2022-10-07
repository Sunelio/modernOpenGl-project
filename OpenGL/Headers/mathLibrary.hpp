#pragma once
#include <stdint.h>
#include <math.h>
#define M_PI 3.14159265359
#define degToRad(angleInDegrees) ((angleInDegrees)*M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians)*180.0 / M_PI)
#define RED     {1.0f,0.0f,0.0f,1.0f}
#define WHITE   {1.0f,1.0f,1.0f,1.0f}
#define GREEN   {0.0f,1.0f,0.0f,1.0f}
#define BLUE    {0.0f,0.0f,1.0f,1.0f}
#define BLACK   {0.0f,0.0f,0.0f,1.0f}



// --------------- Struct --------------
namespace Core
{
    namespace Maths
    {
        class Vector4D;

        class Vector2D
        {
        private:
        public:
            float x, y;

            Vector2D();
            Vector2D(const int number);
            Vector2D(const float x, const float y);
            Vector2D(const int x, const int y);
            Vector2D(const Vector4D& v);
            ~Vector2D();

            Vector2D operator+(Vector2D const b);
            Vector2D operator-(Vector2D const b);
            Vector2D operator-(Vector2D const b) const;
            Vector2D operator*(float const multiplier);
            const Vector2D operator*(float const multiplier) const;
            Vector2D operator/(float const divider);
            Vector2D operator-();
            Vector2D operator+=(Vector2D const v2);
            Vector2D operator-=(Vector2D const v2);

            Vector2D operator=(Vector4D const v2);
            bool operator==(Vector2D const v2);
            bool operator==(Vector2D const v2) const;
            bool operator!=(Vector2D const v2);

            // operator Vector2() { return {x,y}; }

            Vector2D Normalize(); // Get the direction of vector with two point
            float Magnitude() const;
            Vector2D Normal();

            Vector2D GetDirection2D(const Vector2D& PosB);
            float DotProduct2D(const Vector2D& v2);
            float GetDeterminant2D(const Vector2D& b);

            const static Vector2D zero;
            const static Vector2D up;
            const static Vector2D left;
            const static Vector2D down;
            const static Vector2D right;
        };


        class Vector3D
        {
        private:

        public:
            // Properties
            union
            {

                struct
                {
                    float r, g, b;
                };

                struct
                {
                    float x, y, z;
                };

                float coord[3];
            };

            //Constuctors
            Vector3D();
            Vector3D(const Vector4D& vec);
            ~Vector3D();
            Vector3D(const float c1, const float c2, const float c3);

            float GetMagnitude() const;
            void Normalize();

            Vector3D operator+(const Vector3D v2);
            Vector3D operator-(const Vector3D v2);
            Vector3D operator*(const float multiplier);

            const static Vector3D zero;
            const static Vector3D up;
            const static Vector3D left;
            const static Vector3D down;
            const static Vector3D right;
            const static Vector3D forward;
            const static Vector3D back;
        };




        class Vector4D
        {
        private:
            /* data */
        public:
            union
            {
                struct
                {
                    float r, g, b, a;
                };
                struct
                {
                    float x, y, z, w;
                };

                float coord[4];
            };

            Vector4D(/* args */);
            Vector4D(const Vector3D& vec3, float _w = 1.0f);
            Vector4D(const float _x, const float _y, const float _z, const float _w = 1.0f);
            ~Vector4D();


            void Homogenize();
            float GetMagnitude() const;
            void Normalize();

            Vector4D& operator=(const Vector3D v2);
            Vector4D operator+(const Vector4D v2);
            Vector4D operator-(const Vector4D v2);
            Vector4D operator-(const Vector4D v2) const;
            Vector4D operator*(float const multiplier);
            Vector4D operator*(Vector4D const multiplier);
            Vector4D operator/(float f1);
            bool operator<(const float f1);
            bool operator>(const float f1);
            bool operator<=(const float f1);
            bool operator>=(const float f1);
            bool operator==(const Vector4D& v1);

            const static Vector4D zero;
            const static Vector4D up;
            const static Vector4D left;
            const static Vector4D down;
            const static Vector4D right;
            const static Vector4D forward;
            const static Vector4D back;
        };

        using Color = Vector4D;

        class Transform
        {
        private:
            /* data */
        public:
            Vector3D position = { 0.f, 0.f, 0.0f };
            Vector3D rotation = { 0.f, 0.f, 0.0f };
            Vector3D scale = { 1.f, 1.f, 1.f };

            Transform();
            Transform(const Vector3D& pos);
            Transform(const Vector3D& pos, const Vector3D& rot);
            Transform(const Vector3D& pos, const Vector3D& rot, const Vector3D& sca);

            ~Transform();

            void ResetTransform();
        };

        class Matrix4D
        {
        private:
        public:
            //Properties

            union
            {
                float e[16];
                float c[4][4];
            };

            // Construction
            Matrix4D();
            ~Matrix4D();

            Matrix4D operator+(const Matrix4D m2);
            Matrix4D operator-(const Matrix4D m2);
            Matrix4D operator*(const Matrix4D m2);
            Vector4D operator*(const Vector4D v2);
            float operator[](const unsigned int index);

            void LoadIdentity();
            static Matrix4D Model(Vector3D rotation, const Vector3D& translation, const Vector3D& scale);
            static Matrix4D TransposeMatrix(const Matrix4D& matrix);
            static Matrix4D InverseMatrix(const Matrix4D& matrix);
            static float Determinant2x2(const Matrix4D& matrix);
            static float Determinant3x3(const Matrix4D& matrix);
            static float Determinant4x4(const Matrix4D& matrix);
            static Matrix4D MatrixCofacteur(const Matrix4D& mat4x4);

            static int MatrixSignElement(const int index);
            static Matrix4D Mat3x3ToMat2x2(const int row, const int columns, const Matrix4D& mat3x3);
            static Matrix4D Mat4x4ToMat3x3(const int row, const int columns, const Matrix4D& mat4x4);

            static Matrix4D CreateTransformMatrix(const Transform& trans);
            static Matrix4D CreateTranslationMatrix(const Vector3D& translation);
            static Matrix4D CreateScaleMatrix(const Vector3D& scale);
            static Matrix4D CreateXRotationMatrix(float angle);
            static Matrix4D CreateYRotationMatrix(float angle);
            static Matrix4D CreateZRotationMatrix(float angle);

        };

        /*Vector2D GetDirection2D(Vector2D posA, Vector2D posB);
        float DotProduct2D(Vector2D a, Vector2D b);
        float GetDeterminant2D(Vector2D a, Vector2D b);

        Vector2D operator/(float f1, Vector2D a);*/
    }
        //Vector4D operator/(float f1, Vector4D a)

}
#include "../Sources/mathLibrary.inl"

// ----------- Rotation Vector 2D ---------

// Get angle of degree from a vector to a another.
// The angle is between 0 and 180 degree
        float GetDegreAngle(Vector2D& a, Vector2D& b);
        //float GetDegreeAngle(Vector3D& a, Vector3D& b);
        float GetDegreAngle(Vector4D& a, Vector4D& b);

        // Get angle of degree from a vector to a another.
        // The angle is between -180 and 180 degree
        float GetSignedDegreAngle(Vector2D& a, Vector2D& b);


        // Rotate a vector
        void RotateVector2D(Vector2D& direction, float angle);

        // --------- Math algebric function ------------------

        // Make transition between the start value and the end value
        float LerpFloat(const  float start, const float end, const float t);

        template <typename T>
        T Lerp(T start, T end, float t);

        Vector2D LerpVector(const Vector2D& start, const Vector2D& end, const float t);

        //Limit the value of a variable between a max and a min
        float ClampFloat(const float number, const float min, const float max);
        int ClampInt(const int number, const int min, const int max);

        const int GetSign(const float f);
        // --------- Random function --------
        //int32_t GetSeed();
        int32_t getRandomNumber(int32_t& state);

        // Get a random number between a min (inclusive) and a max (non-inclusive)
        int RandomNumber(int32_t& state, const int min, const int max);
        float RandomNumber(int32_t& state, const float min, const float max);

        // --------------- Vector 3D Functions --------------

        // Multiplication of Vector3D
        Vector3D CrossProduct(Vector3D& a, Vector3D& b);

        // --------------- Vector 4D Functions -----------------
        Vector4D CrossProduct(Vector4D& a, Vector4D& b, Vector4D& c);

        Vector4D CrossProduct(Vector4D& a, Vector4D& b);

        Vector4D CompareMaxXValue(const Vector4D& v1, const Vector4D& v2);
        Vector4D CompareMinXValue(const Vector4D& v1, const Vector4D& v2);
        Vector4D CompareMaxYValue(const Vector4D& v1, const Vector4D& v2);
        Vector4D CompareMinYValue(const Vector4D& v1, const Vector4D& v2);
