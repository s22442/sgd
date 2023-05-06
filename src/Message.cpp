#include "Message.h"
#include "GameObject.h"
#include "config.h"

Message::Message(
    std::shared_ptr<SDL_Renderer> renderer,
    std::string texture_filename) : GameObject(renderer,
                                               0,
                                               WINDOW_WIDTH / 2.0,
                                               (double)(WALL_EXTENSION +
                                                        BRICK_GRID_MARGIN_TOP +
                                                        (BRICK_CELL_HEIGHT * (BRICK_ROWS + 3))),
                                               texture_filename) {
}
