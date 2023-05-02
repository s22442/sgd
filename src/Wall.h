#include "ReflectiveObject.h"

#ifndef WALL_H
#define WALL_H

class Wall : public ReflectiveObject {
public:
    Wall(
        SDL_Renderer *renderer,
        int angle,
        double position_x,
        double position_y) : ReflectiveObject(renderer,
                                              angle,
                                              position_x,
                                              position_y,
                                              "wall.bmp") {
    }
};

#endif // WALL_H