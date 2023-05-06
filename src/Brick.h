#include "ReflectiveObject.h"

#ifndef BRICK_H
#define BRICK_H

class Brick : public ReflectiveObject {
private:
    bool destroyed = false;

public:
    Brick(
        std::shared_ptr<SDL_Renderer> renderer,
        double angle,
        double position_x,
        double position_y);

    inline auto is_destroyed() {
        return this->destroyed;
    }

    void handle_colision(GameObject &ball);
};

#endif // BRICK_H