#pragma once

#include <raylib.h>
#include <vector>
#include "Boid.cpp"

int main()
{
    InitWindow(1280, 720, "Flappy Flock");

    SetTargetFPS(60);

    int PositionX = 20;
    int PositionY = 20;
    
    int frame_count = 0;
    
    std::vector<Boid*> current_boids;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(SKYBLUE);
        
        DrawText("Boid test. Left click to add boid, move the mouse and the boids will follow.", PositionX, PositionY, 30, BLACK);

       if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
       {
           auto created_boid = new Boid(GetMousePosition());
           // Some voids ignore center of mass so they don't overlap so much
           created_boid->set_ignore_center_of_mass(current_boids.size() % 2 == 0);
           current_boids.push_back(created_boid);
       }
        
        // First update all directions
        for (const auto boid : current_boids)
        {
            boid->update_directions(current_boids, GetMousePosition());
        }
        
        // Then with all directions updated move and draw the boids
        for (const auto boid : current_boids)
        {
            boid->update_position();
            boid->draw();
            
            // Toggle follow of mouse to add some variety to the movement
            if (frame_count > 120)
            {
                boid->toggle_ignore_center_of_mass();
                frame_count = 0;
            }
        }
        
        frame_count++;

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
