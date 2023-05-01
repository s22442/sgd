#include "GameObject.h"

#ifndef BRICK_H
#define BRICK_H

class Brick : public GameObject {
public:
    Brick(
        SDL_Renderer *renderer,
        double angle,
        double position_x,
        double position_y) : GameObject(renderer,
                                        angle,
                                        position_x,
                                        position_y,
                                        "brick.bmp") {
    }

    void handleColision(GameObject &otherObject) {
    }
};

#endif // BRICK_H