#include "CollisionObject.h"
#include "GameObject.h"
#include <SDL.h>

CollisionObject::CollisionObject(
    std::shared_ptr<SDL_Renderer> renderer,
    double angle,
    double position_x,
    double position_y,
    std::string texture_filename) : GameObject(renderer,
                                               angle,
                                               position_x,
                                               position_y,
                                               texture_filename) {
}
