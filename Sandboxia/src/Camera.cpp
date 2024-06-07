#include "Camera.h"

SBCamera::SBCamera(Camera3D camera)
	: m_Camera(camera)
{
}

const Camera3D* SBCamera::GetCameraPtr() const
{
	return &m_Camera;
}

Vec3<float> SBCamera::GetPos() const
{
	return Vec3{m_Camera.position.x, m_Camera.position.y, m_Camera.position.z};
}

void SBCamera::SetPos(Vec3<double> pos)
{
	SetPos(pos.CastTo<Vector3, float>());
}

void SBCamera::SetPos(Vector3 pos)
{
	m_Camera.position = pos;
}

void SBCamera::Update()
{
    //Vector2 mousePositionDelta = GetMouseDelta();

    //bool moveInWorldPlane = ((mode == CAMERA_FIRST_PERSON) || (mode == CAMERA_THIRD_PERSON));
    //bool rotateAroundTarget = ((mode == CAMERA_THIRD_PERSON) || (mode == CAMERA_ORBITAL));
    //bool lockView = ((mode == CAMERA_FREE) || (mode == CAMERA_FIRST_PERSON) || (mode == CAMERA_THIRD_PERSON) || (mode == CAMERA_ORBITAL));
    //bool rotateUp = false;

    //if (mode == CAMERA_ORBITAL)
    //{
    //    // Orbital can just orbit
    //    Matrix rotation = MatrixRotate(GetCameraUp(camera), CAMERA_ORBITAL_SPEED * GetFrameTime());
    //    Vector3 view = Vector3Subtract(camera->position, camera->target);
    //    view = Vector3Transform(view, rotation);
    //    camera->position = Vector3Add(camera->target, view);
    //}
    //else
    //{
    //    // Camera rotation
    //    if (IsKeyDown(KEY_DOWN)) CameraPitch(camera, -CAMERA_ROTATION_SPEED, lockView, rotateAroundTarget, rotateUp);
    //    if (IsKeyDown(KEY_UP)) CameraPitch(camera, CAMERA_ROTATION_SPEED, lockView, rotateAroundTarget, rotateUp);
    //    if (IsKeyDown(KEY_RIGHT)) CameraYaw(camera, -CAMERA_ROTATION_SPEED, rotateAroundTarget);
    //    if (IsKeyDown(KEY_LEFT)) CameraYaw(camera, CAMERA_ROTATION_SPEED, rotateAroundTarget);
    //    if (IsKeyDown(KEY_Q)) CameraRoll(camera, -CAMERA_ROTATION_SPEED);
    //    if (IsKeyDown(KEY_E)) CameraRoll(camera, CAMERA_ROTATION_SPEED);

    //    // Camera movement
    //    // Camera pan (for CAMERA_FREE)
    //    if ((mode == CAMERA_FREE) && (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)))
    //    {
    //        const Vector2 mouseDelta = GetMouseDelta();
    //        if (mouseDelta.x > 0.0f) CameraMoveRight(camera, CAMERA_PAN_SPEED, moveInWorldPlane);
    //        if (mouseDelta.x < 0.0f) CameraMoveRight(camera, -CAMERA_PAN_SPEED, moveInWorldPlane);
    //        if (mouseDelta.y > 0.0f) CameraMoveUp(camera, -CAMERA_PAN_SPEED);
    //        if (mouseDelta.y < 0.0f) CameraMoveUp(camera, CAMERA_PAN_SPEED);
    //    }
    //    else
    //    {
    //        // Mouse support
    //        CameraYaw(camera, -mousePositionDelta.x * CAMERA_MOUSE_MOVE_SENSITIVITY, rotateAroundTarget);
    //        CameraPitch(camera, -mousePositionDelta.y * CAMERA_MOUSE_MOVE_SENSITIVITY, lockView, rotateAroundTarget, rotateUp);
    //    }

    //    // Keyboard support
    //    if (IsKeyDown(KEY_W)) CameraMoveForward(camera, CAMERA_MOVE_SPEED, moveInWorldPlane);
    //    if (IsKeyDown(KEY_A)) CameraMoveRight(camera, -CAMERA_MOVE_SPEED, moveInWorldPlane);
    //    if (IsKeyDown(KEY_S)) CameraMoveForward(camera, -CAMERA_MOVE_SPEED, moveInWorldPlane);
    //    if (IsKeyDown(KEY_D)) CameraMoveRight(camera, CAMERA_MOVE_SPEED, moveInWorldPlane);

    //    // Gamepad movement
    //    if (IsGamepadAvailable(0))
    //    {
    //        // Gamepad controller support
    //        CameraYaw(camera, -(GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X) * 2) * CAMERA_MOUSE_MOVE_SENSITIVITY, rotateAroundTarget);
    //        CameraPitch(camera, -(GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y) * 2) * CAMERA_MOUSE_MOVE_SENSITIVITY, lockView, rotateAroundTarget, rotateUp);

    //        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) <= -0.25f) CameraMoveForward(camera, CAMERA_MOVE_SPEED, moveInWorldPlane);
    //        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) <= -0.25f) CameraMoveRight(camera, -CAMERA_MOVE_SPEED, moveInWorldPlane);
    //        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) >= 0.25f) CameraMoveForward(camera, -CAMERA_MOVE_SPEED, moveInWorldPlane);
    //        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) >= 0.25f) CameraMoveRight(camera, CAMERA_MOVE_SPEED, moveInWorldPlane);
    //    }

    //    if (mode == CAMERA_FREE)
    //    {
    //        if (IsKeyDown(KEY_SPACE)) CameraMoveUp(camera, CAMERA_MOVE_SPEED);
    //        if (IsKeyDown(KEY_LEFT_CONTROL)) CameraMoveUp(camera, -CAMERA_MOVE_SPEED);
    //    }
    //}

    //if ((mode == CAMERA_THIRD_PERSON) || (mode == CAMERA_ORBITAL) || (mode == CAMERA_FREE))
    //{
    //    // Zoom target distance
    //    CameraMoveToTarget(camera, -GetMouseWheelMove());
    //    if (IsKeyPressed(KEY_KP_SUBTRACT)) CameraMoveToTarget(camera, 2.0f);
    //    if (IsKeyPressed(KEY_KP_ADD)) CameraMoveToTarget(camera, -2.0f);
    //}
}

