#include "CollisionObject.h"
#include "config.h"
#include "utils.h"
#include <iostream>

#ifndef PLATFORM_H
#define PLATFORM_H

class Platform : public CollisionObject {
public:
    Platform(
        std::shared_ptr<SDL_Renderer> renderer,
        double angle,
        double position_x,
        double position_y);

    auto move_left() -> void;

    auto move_right() -> void;

    void handle_colision(GameObject &ball);
};

#endif // PLATFORM_H