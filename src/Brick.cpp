#include "ReflectiveObject.cpp"

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
        double position_y) : ReflectiveObject(renderer,
                                              angle,
                                              position_x,
                                              position_y,
                                              "brick.bmp") {
    }

    auto is_destroyed() {
        return this->destroyed;
    }

    void handle_colision(GameObject &ball) {
        this->destroyed = true;
        this->ReflectiveObject::handle_colision(ball);
    }
};

#endif // BRICK_H