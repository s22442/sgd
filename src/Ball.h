#include "GameObject.h"
#include "config.h"
#include <cmath>
#include <iostream>

#ifndef BALL_H
#define BALL_H

class Ball : public GameObject {
private:
    auto degrees_to_radians(double degrees) -> double {
        return degrees * (M_PI / 180);
    }

    auto angle_in_radians() -> double {
        return this->degrees_to_radians(this->angle);
    }

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

    auto update_position() -> void {
        this->set_position_x(
            this->position_x + (std::cos(this->angle_in_radians()) * BALL_SPEED));

        this->set_position_y(
            this->position_y + (std::sin(this->angle_in_radians()) * BALL_SPEED));
    }

    auto detect_and_handle_colision(GameObject &other_object) -> void {
        auto other_rect = other_object.get_rect();

        auto other_angle_in_radians = this->degrees_to_radians(other_object.get_angle());
        auto other_x = other_object.get_position_x();
        auto other_y = other_object.get_position_y();

        auto half_other_width = other_rect.w / 2;
        auto half_other_height = other_rect.h / 2;

        auto other_x_radius = half_other_width *
                                  std::cos(other_angle_in_radians) +
                              half_other_height *
                                  std::sin(other_angle_in_radians);

        auto other_y_radius = half_other_width *
                                  std::sin(other_angle_in_radians) +
                              half_other_height *
                                  std::cos(other_angle_in_radians);

        auto closest_other_x = this->position_x > other_x
                                   ? std::min(this->position_x, other_x + other_x_radius)
                                   : std::max(this->position_x, other_x - other_x_radius);

        auto closest_other_y = this->position_y > other_y
                                   ? std::min(this->position_y, other_y + other_y_radius)
                                   : std::max(this->position_y, other_y - other_y_radius);

        auto distance = std::sqrt(
            std::pow(closest_other_x - this->position_x, 2) +
            std::pow(closest_other_y - this->position_y, 2));

        if (distance <= this->rect.w / 2) {
            other_object.handle_colision(*this);
        }
    }

    void handle_colision(GameObject &other_object) {
    }
};

#endif // BALL_H