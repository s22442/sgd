#include "CollisionObject.h"
#include "GameObject.h"
#include "config.h"
#include <cmath>

#ifndef BALL_H
#define BALL_H

class Ball : public GameObject {

public:
    Ball(
        SDL_Renderer *renderer,
        int angle,
        double position_x,
        double position_y) : GameObject(renderer,
                                        angle,
                                        position_x,
                                        position_y,
                                        "ball.bmp") {
    }

    auto update_position(int speed = BALL_SPEED) -> void {
        this->set_position_x(
            this->position_x + (std::cos(this->get_angle_in_radians()) * speed));

        this->set_position_y(
            this->position_y + (std::sin(this->get_angle_in_radians()) * speed));
    }

    auto calculate_distance(CollisionObject &other_object) {
        auto [closest_other_x,
              closest_other_y] = other_object.calculate_closest_inner_point(this->position_x,
                                                                            this->position_y);

        auto distance = std::sqrt(
            std::pow(closest_other_x - this->position_x, 2) +
            std::pow(closest_other_y - this->position_y, 2));

        return distance;
    }

    auto detect_and_handle_colision(CollisionObject &other_object) -> void {
        auto distance = this->calculate_distance(other_object);

        if (distance <= this->rect.w / 2) {
            other_object.handle_colision(*this);
            this->update_position(1);
        }
    }
};

#endif // BALL_H