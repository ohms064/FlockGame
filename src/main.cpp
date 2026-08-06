#include <raylib.h>

int main()
{
    InitWindow(1280, 720, "Flappy Flock");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(SKYBLUE);

        DrawText("Hello Raylib!", 20, 20, 30, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}