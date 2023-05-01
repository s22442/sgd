#include "GameObject.h"

#ifndef WALL_H
#define WALL_H

class Wall : public GameObject {
public:
    Wall(
        SDL_Renderer *renderer,
        double angle,
        double position_x,
        double position_y) : GameObject(renderer,
                                        angle,
                                        position_x,
                                        position_y,
                                        "wall.bmp") {
    }

    void handle_colision(GameObject &other_object) {
        other_object.set_angle(other_object.get_angle() + 180);
    }
};

#endif // WALL_H