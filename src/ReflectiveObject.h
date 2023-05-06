#include "CollisionObject.h"
#include "config.h"
#include <iostream>

#ifndef REFLECTIVE_OBJECT_H
#define REFLECTIVE_OBJECT_H

class ReflectiveObject : public CollisionObject {
public:
    ReflectiveObject(
        std::shared_ptr<SDL_Renderer> renderer,
        double angle,
        double position_x,
        double position_y,
        std::string texture_filename);

    void handle_colision(GameObject &ball);
};

#endif // REFLECTIVE_OBJECT_H