#include "Platform.h"
#include "CollisionObject.h"
#include "config.h"
#include "utils.h"
#include <iostream>

Platform::Platform(
    std::shared_ptr<SDL_Renderer> renderer,
    double angle,
    double position_x,
    double position_y) : CollisionObject(renderer,
                                         angle,
                                         position_x,
                                         position_y,
                                         "platform.bmp") {
}

auto Platform::move_left(double game_speed_multiplier) -> void {
    this->set_position_x(
        this->get_position_x() - (PLATFORM_SPEED * game_speed_multiplier));
}

auto Platform::move_right(double game_speed_multiplier) -> void {
    this->set_position_x(
        this->get_position_x() + (PLATFORM_SPEED * game_speed_multiplier));
}

void Platform::handle_colision(GameObject &ball) {
    auto ball_x = ball.get_position_x();
    auto ball_y = ball.get_position_y();

    auto new_angle = 360 - ball.get_angle();

    auto [closest_x,
          closest_y] = this->calculate_closest_inner_point(ball_x,
                                                           ball_y);

    if (ball_y > this->position_y) {
        return;
    }

    auto distance_from_center = std::abs(this->position_x - closest_x);
    auto angle_modifier = 90 * distance_from_center / (this->rect.w / 2);

    if (closest_x < this->position_x) {
        angle_modifier *= -1;
    }

    new_angle += angle_modifier;

    new_angle = std::max(
        190.0,
        std::min(350.0, new_angle));

    ball.set_angle(new_angle);
}
