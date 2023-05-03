#include "ReflectiveObject.h"

#ifndef WALL_H
#define WALL_H

class Wall : public ReflectiveObject {
public:
    Wall(
        std::shared_ptr<SDL_Renderer> renderer,
        double angle,
        double position_x,
        double position_y) : ReflectiveObject(renderer,
                                              angle,
                                              position_x,
                                              position_y,
                                              "wall.bmp") {
    }
};

#endif // WALL_H