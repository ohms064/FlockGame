#include <raylib.h>

#include "vector"
#include "Boid.cpp"


class BoidGroup
{
    std::vector<Boid*> current_boids_;
    Vector2 center_of_mass_ = {};
    
public:
    
    void AddBoid(Boid* boid)
    {
        // Some voids ignore center of mass so they don't overlap so much
        boid->set_ignore_center_of_mass(current_boids_.size() % 2 == 0);
        current_boids_.push_back(boid);
    }
    
    void UpdateCenterOfMass(const Vector2 center_of_mass)
    {
        center_of_mass_ = center_of_mass;
    }
    
    Vector2 GetCenterOfMass() const
    {
        return center_of_mass_;
    }
    
    void UpdatePositionAndDraw()
    {
        // Then with all directions updated move and draw the boids
        for (const auto boid : current_boids_)
        {
            boid->update_position();
            boid->draw();
        }
    }
    
    void ToggleFollowCenterOfMass() const
    {
        for (const auto boid : current_boids_)
        {
            boid->toggle_ignore_center_of_mass();
        }
    }
    
    void UpdateDirections() const
    {
        // First update all directions
        for (const auto boid : current_boids_)
        {
            boid->update_directions(current_boids_, center_of_mass_);
        }
    }
    
    int GetGroupSize() const
    {
        return current_boids_.size();
    }
};