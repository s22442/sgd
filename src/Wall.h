#include "GameObject.h"

#ifndef WALL_H
#define WALL_H

class Wall : public GameObject {
public:
    Wall(
        SDL_Renderer *renderer,
        int angle,
        double position_x,
        double position_y) : GameObject(renderer,
                                        angle,
                                        position_x,
                                        position_y,
                                        "wall.bmp") {
    }

    void handle_colision(GameObject &other_object) {
        auto new_angle = 180 - other_object.get_angle();

        auto vertical_colision = std::abs(
                                     this->position_x -
                                     other_object.get_position_x()) >
                                 std::abs(this->position_y -
                                          other_object.get_position_y());

        if (vertical_colision) {
            new_angle += 180;
        }

        other_object.set_angle(new_angle);
    }
};

#endif // WALL_H