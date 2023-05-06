#include "Brick.h"
#include "ReflectiveObject.h"

Brick::Brick(
    std::shared_ptr<SDL_Renderer> renderer,
    double angle,
    double position_x,
    double position_y) : ReflectiveObject(renderer,
                                          angle,
                                          position_x,
                                          position_y,
                                          "brick.bmp") {
}

void Brick::handle_colision(GameObject &ball) {
    this->destroyed = true;
    this->ReflectiveObject::handle_colision(ball);
}