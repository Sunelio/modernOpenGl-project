#include <Camera.h>
using namespace LowRendere;

Transform Camera::transform;
float Camera::near = 0;
float Camera::far = 0;
float Camera::FOV = 0;

float Camera::top = 0;
float Camera::bottom = 0;
float Camera::left = 0;
float Camera::right = 0;


Camera::Camera(const uint widthIn, const uint heightIn)
{
    width = widthIn;
    height = heightIn;
    aspectRatio = width / height;
    FOV = 90.f;


    far = 10.0f;
    near = 0.1f;

    float scale = tan(FOV * 0.5 * M_PI / 180) * near;
    right = aspectRatio * scale, left = -right;
    top = scale, bottom = -top;
}

void Camera::Update(const float p_deltaTime, const CameraInputs& inputs)
{
    RotateInput(p_deltaTime, inputs);
    PositionInput(p_deltaTime, inputs);
}

// Set Input function

void Camera::PositionInput(const float p_deltaTime, const CameraInputs& inputs)
{
    transform.position.x += inputs.deltaX * p_deltaTime;
    transform.position.y += inputs.deltaY * p_deltaTime;

    if (inputs.moveForward)
    {
        transform.position.z += 1.0f * p_deltaTime;
    }
    if (inputs.moveBackward)
    {
        transform.position.z -= 1.0f * p_deltaTime;
    }
    if (inputs.moveLeftSide)
    {
        transform.position.x -= 1.0f * p_deltaTime;
    }
    if(inputs.moveRightSide)
    {
        transform.position.x += 1.0f * p_deltaTime;
    }
}

void Camera::RotateInput(const float p_deltaTime, const CameraInputs& inputs)
{

    if (inputs.rotateRight)
    {
        transform.rotation.y += 30.0f * p_deltaTime;
    }
    if (inputs.rotateLeft)
    {
        transform.rotation.y -= 30.0f * p_deltaTime;
    }

    if (inputs.rotateUp)
    {
        transform.rotation.x += 30.0f * p_deltaTime;
    }
    if (inputs.rotateDown)
    {
        transform.rotation.x -= 30.0f * p_deltaTime;
    }
}

void Camera::ResetCameraTransform()
{
    transform.ResetTransform();
}


Matrix4D Camera::GetViewMatrix()
{
    Matrix4D transformMatCam = Matrix4D::CreateTransformMatrix(transform);
    transformMatCam = Matrix4D::InverseMatrix(transformMatCam);
    return transformMatCam;
}

Matrix4D Camera::GetProjection()
{
    Matrix4D ProjMat;

    ProjMat.c[0][0] = 2 * near / (right - left);
    ProjMat.c[0][1] = 0;
    ProjMat.c[0][2] = 0;
    ProjMat.c[0][3] = 0;
    ProjMat.c[1][0] = 0;
    ProjMat.c[1][1] = 2 * near / (top - bottom);
    ProjMat.c[1][2] = 0;
    ProjMat.c[1][3] = 0;
    ProjMat.c[2][0] = (right + left) / (right - left);
    ProjMat.c[2][1] = (top + bottom) / (top - bottom);
    ProjMat.c[2][2] = -(far + near) / (far - near);
    ProjMat.c[2][3] = -1;
    ProjMat.c[3][0] = 0;
    ProjMat.c[3][1] = 0;
    ProjMat.c[3][2] = -2 * far * near / (far - near);
    ProjMat.c[3][3] = 1;



    return ProjMat;
}

