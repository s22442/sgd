#include "GameObject.h"

#ifndef BALL_H
#define BALL_H

class Ball : public GameObject {
public:
    Ball(
        SDL_Renderer *renderer,
        double angle,
        double position_x,
        double position_y) : GameObject(renderer,
                                        angle,
                                        position_x,
                                        position_y,
                                        "ball.bmp") {
    }

    void handleColision(GameObject &otherObject) {
    }
};

#endif // BALL_H