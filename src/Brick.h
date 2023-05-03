#include "ReflectiveObject.h"

#ifndef BRICK_H
#define BRICK_H

class Brick : public ReflectiveObject {
public:
    Brick(
        SDL_Renderer *renderer,
        double angle,
        double position_x,
        double position_y) : ReflectiveObject(renderer,
                                              angle,
                                              position_x,
                                              position_y,
                                              "brick.bmp") {
    }
};

#endif // BRICK_H