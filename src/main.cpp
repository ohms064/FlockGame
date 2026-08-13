#pragma once

#include <format>
#include <raylib.h>
#include <vector>
#include "BoidGroup.cpp"

int main()
{
    constexpr int screen_width = 1280;
    constexpr int screen_height = 720;
    InitWindow(screen_width, screen_height, "Flappy Flock");

    SetTargetFPS(60);

    int PositionX = 20;
    int PositionY = 20;
    
    int frame_count = 0;
    
    
    Camera2D camera = { 0 };
    camera.rotation = 0.0f;
    camera.offset = Vector2 { screen_width/2.0f, screen_height/2.0f };
    camera.zoom = 1.0f;
    
    BoidGroup boid_group = {};

    auto boid_follow = Vector2 { screen_width/2.0f, screen_height/2.0f }; 
    const float boid_movement_velocity = 2;

    while (!WindowShouldClose())
    {
       if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_B))
       {
           auto created_boid = new Boid(boid_follow);
           boid_group.AddBoid(created_boid);
       }
    
        // Boid group center
        if (IsKeyDown(KEY_DOWN)) boid_follow.y += boid_movement_velocity;
        if (IsKeyDown(KEY_UP)) boid_follow.y -= boid_movement_velocity;
        if (IsKeyDown(KEY_RIGHT)) boid_follow.x += boid_movement_velocity;
        if (IsKeyDown(KEY_LEFT)) boid_follow.x -= boid_movement_velocity;
        
        boid_group.UpdateCenterOfMass(boid_follow);
        camera.target = boid_follow;
        
        BeginDrawing();

            ClearBackground(SKYBLUE);
                
            DrawText("Boid test. Left click to add boid, move the mouse and the boids will follow.", PositionX, PositionY, 30, BLACK);
            DrawText(std::format("Boids: {}", boid_group.GetGroupSize()).c_str(), 20, 70, 30, BLACK);
            DrawText(std::format("Frame Count: {}", frame_count).c_str(), 250, 70, 30, BLACK);
            DrawText(std::format("FPS: {}", GetFPS()).c_str(), 500, 70, 30, BLACK);

            
            BeginMode2D(camera);
           {
               // First update all directions
               boid_group.UpdateDirections();
           
           
               DrawRectangle(0, 5, 50, screen_height - 10, RAYWHITE);
               DrawCircle(boid_follow.x, boid_follow.y, 10, RED);
               boid_group.UpdatePositionAndDraw();
               if (frame_count == 120)
               {
                   boid_group.ToggleFollowCenterOfMass();
               }
           }
            EndMode2D();
        
        // Then with all directions updated move and draw the boids
        
        
        EndDrawing();
         
        frame_count++;
        if (frame_count > 120)
        {
            frame_count = 0;
        }
    }

    CloseWindow();
    return 0;
}
