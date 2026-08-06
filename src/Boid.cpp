#include <raylib.h>

#include "vector"
#include "raymath.h"
#include "utils/constants.h"

namespace
{
    class Boid {

    private:
    
        Vector2 position_;
        Vector2 velocity_;
        bool ignore_center_of_mass_ = false;

    public:
        Boid(const Vector2& position)
            : position_(position),
              velocity_({0, 0})
        {
        }

        Vector2 get_position() const 
        {
            return position_;
        }
        
        Vector2 get_velocity() const
        {
            return velocity_;
        }

        // This is where the boid algorithm is really implemented. 
        void update_directions(const std::vector<Boid*>& other_boids, const Vector2 center_of_mass)
        {
            // This vector defines the overall direction of all the boids in the flock
            Vector2 overall_boids_direction = {};
            
            // This vector defines tha avoidance against other boids
            Vector2 boid_avoidance_direction = {};
            
            // The direction we want all the voids to follow
            Vector2 center_of_mass_direction = Vector2Subtract(center_of_mass, this->get_position());

            // Previous velocity for further uses
            const Vector2 previous_velocity = velocity_;
            
            // Division between int and floats gets weird, so setting this as float
            const float other_boid_size = other_boids.size();
            
            const auto boid_distance_sqr = boid_distance_threshold * boid_distance_threshold;
            
            // Calculating values against other voids
            for (const auto current_boid : other_boids)
            {
                // Ignore ourselves
                if (current_boid == this)
                {
                    continue;
                }
                
                overall_boids_direction = Vector2Add(overall_boids_direction, current_boid->get_velocity());
                
                const auto distance = Vector2DistanceSqr(this->get_position(), current_boid->get_position());
                if (distance <= boid_distance_sqr)
                {
                    boid_avoidance_direction = Vector2Subtract(this->get_position(), current_boid->get_position());
                }
                
            }
                        
            overall_boids_direction = Vector2Scale(overall_boids_direction, 1.f / other_boid_size);
            
            //Normalize and apply biases to every vector
            overall_boids_direction = Vector2Normalize(overall_boids_direction);
            overall_boids_direction = Vector2Scale(overall_boids_direction, boid_overall_direction_bias);
            
            boid_avoidance_direction = Vector2Normalize(boid_avoidance_direction);
            boid_avoidance_direction = Vector2Scale(boid_avoidance_direction, boid_avoidance_bias);
            
            center_of_mass_direction = Vector2Normalize(center_of_mass_direction);
            center_of_mass_direction = Vector2Scale(center_of_mass_direction, center_of_mass_bias);
            
            Vector2 current_velocity_direction = Vector2Normalize(previous_velocity);
            current_velocity_direction = Vector2Scale(current_velocity_direction, current_velocity_bias);
            
            velocity_ = Vector2Add(overall_boids_direction, boid_avoidance_direction);
            if (!ignore_center_of_mass_)
            {
                velocity_ = Vector2Add(velocity_, center_of_mass_direction);
            }
            velocity_ = Vector2Add(velocity_, current_velocity_direction);
            
            velocity_ = Vector2Normalize(velocity_);
            velocity_ = Vector2Scale(velocity_, boid_speed);
            velocity_ = Vector2MoveTowards(previous_velocity, velocity_, 1);
        }
        
        void update_position()
        {
            position_ = Vector2Add(this->get_position(), this->get_velocity());
        }
        
        void draw() const
        {
            DrawCircle(position_.x, position_.y, 10, GREEN);
            DrawLine(position_.x, position_.y, position_.x + velocity_.x, position_.y + velocity_.y, RED);
        }
        
        void set_ignore_center_of_mass(bool ignore_center_of_mass)
        {
            ignore_center_of_mass_ = ignore_center_of_mass;
        }
        
        void toggle_ignore_center_of_mass()
        {
            ignore_center_of_mass_ = !ignore_center_of_mass_;
        }
    };
}
