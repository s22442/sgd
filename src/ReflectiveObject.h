#include "CollisionObject.h"
#include "config.h"
#include <iostream>

#ifndef REFLECTIVE_OBJECT_H
#define REFLECTIVE_OBJECT_H

class ReflectiveObject : public CollisionObject {
public:
    ReflectiveObject(
        SDL_Renderer *renderer,
        int angle,
        double position_x,
        double position_y,
        std::string texture_filename) : CollisionObject(renderer,
                                                        angle,
                                                        position_x,
                                                        position_y,
                                                        texture_filename) {
    }

    void handle_colision(GameObject &ball) {
        auto ball_x = ball.get_position_x();
        auto ball_y = ball.get_position_y();

        auto new_angle = 180 - ball.get_angle();

        auto [closest_x,
              closest_y] = this->calculate_closest_inner_point(ball_x,
                                                               ball_y);

        auto x_overlaps = closest_x <= ball_x &&
                          closest_x >= ball_x - BALL_SPEED;

        auto y_overlaps = closest_y <= ball_y &&
                          closest_y >= ball_y - BALL_SPEED;

        auto vertical_collision = (x_overlaps && !y_overlaps) ||
                                  (x_overlaps && std::abs(closest_x - ball_x) < std::abs(closest_y - ball_y));

        if (vertical_collision) {
            new_angle += 180;
        }

        ball.set_angle(new_angle);
    }
};

#endif // REFLECTIVE_OBJECT_H