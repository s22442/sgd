#include "GameObject.h"
#include "config.h"

#ifndef PLATFORM_H
#define PLATFORM_H

class Platform : public GameObject {
public:
    Platform(
        SDL_Renderer *renderer,
        double angle,
        double position_x,
        double position_y) : GameObject(renderer,
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

    void handle_colision(GameObject &other_object) {
    }
};

#endif // PLATFORM_H