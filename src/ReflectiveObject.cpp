#include "ReflectiveObject.h"
#include "CollisionObject.h"
#include "config.h"
#include <iostream>

ReflectiveObject::ReflectiveObject(
    std::shared_ptr<SDL_Renderer> renderer,
    double angle,
    double position_x,
    double position_y,
    std::string texture_filename) : CollisionObject(renderer,
                                                    angle,
                                                    position_x,
                                                    position_y,
                                                    texture_filename) {
}

auto ReflectiveObject::handle_colision(GameObject &ball) -> void {
    auto ball_x = ball.get_position_x();
    auto ball_y = ball.get_position_y();
    auto ball_rect = ball.get_rect();
    auto ball_w = ball_rect.w;
    auto ball_h = ball_rect.h;

    auto new_angle = 180 - ball.get_angle();

    auto [closest_x,
          closest_y] = this->calculate_closest_inner_point(ball_x,
                                                           ball_y);

    auto x_overlaps = closest_x <= ball_x + ball_w &&
                      closest_x >= ball_x - ball_w;

    auto y_overlaps = closest_y <= ball_y + ball_h &&
                      closest_y >= ball_y - ball_h;

    auto vertical_collision = (x_overlaps && !y_overlaps) ||
                              (x_overlaps && std::abs(closest_x - ball_x) < std::abs(closest_y - ball_y));

    if (vertical_collision) {
        new_angle += 180;
    }

    ball.set_angle(new_angle);
}
