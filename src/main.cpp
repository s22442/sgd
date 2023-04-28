#include <array>
#include <cmath>
#include <iostream>
#include <memory>
#define SDL_MAIN_HANDLED

#include <SDL.h>

const auto WINDOW_WIDTH = 800;
const auto WINDOW_HEIGHT = 600;

class GameObject {
private:
    SDL_Renderer *renderer;
    double angle;
    double position_x;
    double position_y;
    SDL_Texture *texture;
    SDL_Rect rect;

public:
    GameObject(
        SDL_Renderer *renderer,
        double angle,
        double position_x,
        double position_y,
        std::string texture_filename) {
        this->renderer = renderer;
        this->angle = angle;
        this->position_x = position_x;
        this->position_y = position_y;

        auto *bmp = SDL_LoadBMP(("assets/" + texture_filename).c_str());
        if (!bmp) {
            throw std::invalid_argument("Could not load bmp");
        }

        SDL_SetColorKey(bmp, SDL_TRUE, 0x0ffffff);
        auto *texture = SDL_CreateTextureFromSurface(renderer, bmp);
        if (!texture) {
            throw std::invalid_argument("Could not create texture");
        }

        SDL_FreeSurface(bmp);

        this->texture = texture;

        int w, h;
        SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
        this->rect = SDL_Rect{0, 0, w, h};
    }

    auto get_angle() {
        return this->angle;
    }

    auto get_position_x() {
        return this->position_x;
    }

    auto get_position_y() {
        return this->position_y;
    }

    auto set_angle(double angle) {
        this->angle = angle;
    }

    auto set_position_x(double x) {
        auto half_width = this->rect.w / 2;

        if (x < half_width || x >= WINDOW_WIDTH - half_width) {
            return;
        }

        this->position_x = x;
    }

    auto set_position_y(double y) {
        auto half_height = this->rect.w / 2;

        if (y < half_height || y >= WINDOW_HEIGHT - half_height) {
            return;
        }

        this->position_y = y;
    }

    auto render() {
        this->rect.x = this->position_x - this->rect.w / 2;
        this->rect.y = this->position_y - this->rect.h / 2;

        SDL_RenderCopyEx(this->renderer,
                         this->texture,
                         nullptr,
                         &this->rect,
                         this->angle,
                         nullptr,
                         SDL_FLIP_NONE);
    }

    ~GameObject() {
        SDL_DestroyTexture(this->texture);
    }

    virtual void handleColision(GameObject &otherObject) = 0;
};

class Ball : public GameObject {
public:
    Ball(
        SDL_Renderer *renderer,
        double angle,
        double position_x,
        double position_y) : GameObject(renderer,
                                        angle,
                                        position_x,
                                        position_y,
                                        "ball.bmp") {
    }

    void handleColision(GameObject &otherObject) {
    }
};

class Platform : public GameObject {
public:
    Platform(
        SDL_Renderer *renderer,
        double angle,
        double position_x,
        double position_y) : GameObject(renderer,
                                        angle,
                                        position_x,
                                        position_y,
                                        "platform.bmp") {
    }

    void handleColision(GameObject &otherObject) {
    }
};

class Brick : public GameObject {
public:
    Brick(
        SDL_Renderer *renderer,
        double angle,
        double position_x,
        double position_y) : GameObject(renderer,
                                        angle,
                                        position_x,
                                        position_y,
                                        "brick.bmp") {
    }

    void handleColision(GameObject &otherObject) {
    }
};

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

    void handleColision(GameObject &otherObject) {
    }
};

auto play_game(SDL_Renderer *renderer) -> void {
    auto left_wall = Wall{renderer, 0, 10, WINDOW_HEIGHT / 6};
    auto right_wall = Wall{renderer, 0, WINDOW_WIDTH - 10, WINDOW_HEIGHT / 6};
    auto top_wall = Wall{renderer, 90, WINDOW_WIDTH / 2, 10};

    auto platform = Platform{renderer, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT * 0.9};
    auto ball = Ball{renderer, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT * 0.6};

    auto brick1 = Brick{renderer, 0, WINDOW_WIDTH / 2 - 120, WINDOW_HEIGHT * 0.3};
    auto brick2 = Brick{renderer, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT * 0.3};
    auto brick3 = Brick{renderer, 0, WINDOW_WIDTH / 2 + 120, WINDOW_HEIGHT * 0.3};

    bool gaming = true;
    while (gaming) {
        auto e = SDL_Event{};

        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                gaming = false;
                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_q)
                    gaming = false;
                break;
            }
        }

        auto *keyboard_state = SDL_GetKeyboardState(nullptr);

        if (keyboard_state[SDL_SCANCODE_LEFT]) {
            platform.set_position_x(platform.get_position_x() - 8);
        }

        if (keyboard_state[SDL_SCANCODE_RIGHT]) {
            platform.set_position_x(platform.get_position_x() + 8);
        }

        SDL_SetRenderDrawColor(renderer, 20, 20, 60, 255);
        SDL_RenderClear(renderer);

        left_wall.render();
        right_wall.render();
        top_wall.render();

        brick1.render();
        brick2.render();
        brick3.render();

        platform.render();
        ball.render();

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
}

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT,
                                SDL_WINDOW_SHOWN,
                                &window,
                                &renderer);

    play_game(renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}