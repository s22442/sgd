#include "CollisionObject.h"
#include "GameObject.h"
#include "Platform.h"
#include "config.h"
#include <SDL.h>
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
        double position_y);

    auto update_position() -> void;

    auto calculate_distance(CollisionObject &other_object) -> double;

    auto detect_and_handle_colision(CollisionObject &other_object) -> void;

    auto is_unreachable(Platform &platform) -> bool;
};

#endif // BALL_H