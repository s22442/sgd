#include "CollisionObject.h"
#include "config.h"

#ifndef PLATFORM_H
#define PLATFORM_H

class Platform : public CollisionObject {
public:
    Platform(
        SDL_Renderer *renderer,
        int angle,
        double position_x,
        double position_y) : CollisionObject(renderer,
                                             angle,
                                             position_x,
                                             position_y,
                                             "platform.bmp") {
    }

    auto move_left() -> void {
        this->set_position_x(this->get_position_x() - PLATFORM_SPEED);
    }

    auto move_right() -> void {
        this->set_position_x(this->get_position_x() + PLATFORM_SPEED);
    }

    void handle_colision(GameObject &ball) {
    }
};

#endif // PLATFORM_H