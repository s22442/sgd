#include "GameObject.h"
#include "config.h"

#ifndef MESSAGE_H
#define MESSAGE_H

class Message : public GameObject {
public:
    Message(
        std::shared_ptr<SDL_Renderer> renderer,
        std::string texture_filename) : GameObject(renderer,
                                                   0,
                                                   WINDOW_WIDTH / 2.0,
                                                   (double)(WALL_EXTENSION +
                                                            BRICK_GRID_MARGIN_TOP +
                                                            (BRICK_CELL_HEIGHT * (BRICK_ROWS + 3))),
                                                   texture_filename) {
    }
};

#endif // MESSAGE_H