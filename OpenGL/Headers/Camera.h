#pragma once
#include <Model.h>
#include <types.hpp>

namespace LowRendere
{


    struct CameraInputs
    {
        float deltaX;
        float deltaY;
        bool moveForward;
        bool moveBackward;
        bool moveLeftSide;
        bool moveRightSide;

        bool rotateLeft;
        bool rotateRight;
        bool rotateUp;
        bool rotateDown;
        // ... and more if needed
    };

    class Camera
    {

    private:

        int width, height;
        float aspectRatio;
        Matrix4D viewMatrix;
        Matrix4D projecitoMatrix;

       static float near, far;
       static float FOV;

    public:
        static Transform transform;
        static float top, bottom;
        static float left, right;
         Camera(const uint p_width, const uint p_height);

        void Update(const float p_deltaTime, const CameraInputs& p_inputs);
       static Matrix4D GetViewMatrix();
       static Matrix4D GetProjection();

        void RotateInput(const float p_deltaTime, const CameraInputs& p_input);
        void PositionInput(const float p_deltaTime, const CameraInputs& p_input);
        void ResetCameraTransform();
    };

}