#include "CollisionObject.h"
#include "GameObject.h"
#include "config.h"
#include <cmath>
#include <iostream>

#ifndef BALL_H
#define BALL_H

class Ball : public GameObject {
private:
    int object_collision_lock_id = -1;
    int speed = INITIAL_BALL_SPEED;

public:
    Ball(
        std::shared_ptr<SDL_Renderer> renderer,
        double angle,
        double position_x,
        double position_y) : GameObject(renderer,
                                        angle,
                                        position_x,
                                        position_y,
                                        "ball.bmp") {
    }

    auto update_position() -> void {
        this->set_position_x(
            this->position_x + (std::cos(this->get_angle_in_radians()) * this->speed));

        this->set_position_y(
            this->position_y + (std::sin(this->get_angle_in_radians()) * this->speed));
    }

    auto calculate_distance(CollisionObject &other_object) -> double {
        auto [closest_other_x,
              closest_other_y] = other_object.calculate_closest_inner_point(this->position_x,
                                                                            this->position_y);

        auto distance = std::sqrt(
            std::pow(closest_other_x - this->position_x, 2) +
            std::pow(closest_other_y - this->position_y, 2));

        return distance;
    }

    auto detect_and_handle_colision(CollisionObject &other_object) -> void {
        auto half_width = this->rect.w / 2;
        auto distance = this->calculate_distance(other_object);

        if (distance > half_width ||
            this->object_collision_lock_id == other_object.get_id()) {
            return;
        }

        other_object.handle_colision(*this);
        this->object_collision_lock_id = other_object.get_id();

        if (this->speed == INITIAL_BALL_SPEED) {
            this->speed = BALL_SPEED;
        }
    }

    auto is_lost() -> bool {
        return (this->position_y + (this->rect.h / 2) + 1) >= WINDOW_HEIGHT;
    }
};

#endif // BALL_H