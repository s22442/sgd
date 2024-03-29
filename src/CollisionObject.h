#include "GameObject.h"

#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

class CollisionObject : public GameObject {
public:
    CollisionObject(
        std::shared_ptr<SDL_Renderer> renderer,
        double angle,
        double position_x,
        double position_y,
        std::string texture_filename);

    virtual void handle_colision(GameObject &ball) = 0;
};

#endif // COLLISION_OBJECT_H