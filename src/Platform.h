#include "GameObject.h"

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

    void handleColision(GameObject &otherObject) {
    }
};

#endif // PLATFORM_H