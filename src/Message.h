#include "GameObject.h"
#include "config.h"

#ifndef MESSAGE_H
#define MESSAGE_H

class Message : public GameObject {
public:
    Message(
        std::shared_ptr<SDL_Renderer> renderer,
        std::string texture_filename);
};

#endif // MESSAGE_H