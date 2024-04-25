#include <iostream>
#include "Game.h"

int main()
{
    GameApp gameApp = GameApp(1280, 720, "BlockGame - Sound");

    while (!gameApp.GameShouldClose()) {
        gameApp.Tick();
    }

    return 0;

    // TODO: Delete this \/

    InitWindow(1280, 720, "BlockGame - Sound");

    SetExitKey(KeyboardKey::KEY_NULL);


    bool mouseLock = true;

    Camera3D camera3D;
    camera3D.position = { 0.0f, 10.0f, 10.0f };  // Camera position
    camera3D.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera3D.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera3D.fovy = 45.0f;                       // Camera field-of-view Y
    camera3D.projection = CAMERA_PERSPECTIVE;    // Camera mode type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    float speed = 2.f; // units/s

    while (!WindowShouldClose()) {
        
        if (IsKeyPressed(KeyboardKey::KEY_ESCAPE)) {
            mouseLock = !mouseLock;
            if (mouseLock) {
                HideCursor();
            }
            else ShowCursor();
        }

        if (IsKeyDown(KeyboardKey::KEY_F)) // -X
        {
            camera3D.position.x -= GetFrameTime() * speed;
        }
        if (IsKeyDown(KeyboardKey::KEY_J)) // +X
        {
            camera3D.position.x += GetFrameTime() * speed;
        }
        if (IsKeyDown(KeyboardKey::KEY_G)) // -Y
        {
            camera3D.position.y -= GetFrameTime() * speed;
        }
        if (IsKeyDown(KeyboardKey::KEY_K)) // +Y
        {
            camera3D.position.y += GetFrameTime() * speed;
        }
        if (IsKeyDown(KeyboardKey::KEY_H)) // -Z
        {
            camera3D.position.z -= GetFrameTime() * speed;
        }
        if (IsKeyDown(KeyboardKey::KEY_L)) // +Z
        {
            camera3D.position.z += GetFrameTime() * speed;
        }
        
        
        

        if (mouseLock and IsWindowFocused()) {
            UpdateCamera(&camera3D, CAMERA_FIRST_PERSON);
            //UpdateCameraPro(&camera3D);
            SetMousePosition(GetRenderWidth() / 2, GetRenderHeight() / 2);
        }

        BeginDrawing();


        ClearBackground(LIGHTGRAY);

        BeginMode3D(camera3D);

        DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
        DrawGrid(50, 1);

        

        EndMode3D();


        DrawFPS(5, 5);
        //ClearBackground(LIGHTGRAY);

        EndDrawing();
        
    }

    CloseWindow();
}