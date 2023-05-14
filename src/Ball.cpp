#include "Ball.h"
#include "CollisionObject.h"
#include "GameObject.h"
#include "Platform.h"
#include "config.h"
#include <cmath>
#include <iostream>

Ball::Ball(
    std::shared_ptr<SDL_Renderer> renderer,
    double angle,
    double position_x,
    double position_y) : GameObject(renderer,
                                    angle,
                                    position_x,
                                    position_y,
                                    "ball.bmp") {
}

auto Ball::update_position(double game_speed_multiplier) -> void {
    this->set_position_x(
        this->position_x + (std::cos(this->get_angle_in_radians()) *
                            (this->speed * game_speed_multiplier)));

    this->set_position_y(
        this->position_y + (std::sin(this->get_angle_in_radians()) *
                            (this->speed * game_speed_multiplier)));
}

auto Ball::calculate_distance(CollisionObject &other_object) -> double {
    auto [closest_other_x,
          closest_other_y] = other_object.calculate_closest_inner_point(this->position_x,
                                                                        this->position_y);

    auto distance = std::sqrt(
        std::pow(closest_other_x - this->position_x, 2) +
        std::pow(closest_other_y - this->position_y, 2));

    return distance;
}

auto Ball::detect_and_handle_colision(CollisionObject &other_object) -> void {
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

auto Ball::is_unreachable(Platform &platform) -> bool {
    return this->position_y >=
           (platform.get_position_y() + platform.get_rect().h);
}
