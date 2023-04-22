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

        SDL_SetColorKey(bmp, SDL_TRUE, 0x0ff00ff);
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
        if (x < 0 || x >= WINDOW_WIDTH) {
            return;
        }

        this->position_x = x;
    }

    auto set_position_y(double y) {
        if (y < 0 || y >= WINDOW_HEIGHT) {
            return;
        }

        this->position_y = y;
    }

    auto render() {
        this->rect.x = this->position_x - rect.w / 2;
        this->rect.y = this->position_y - rect.h / 2;

        SDL_RenderCopyEx(this->renderer,
                         this->texture,
                         nullptr,
                         &this->rect,
                         180.0 * this->angle / M_PI,
                         nullptr,
                         SDL_FLIP_NONE);
    }

    auto destroy() {
        SDL_DestroyTexture(this->texture);
    }
};

auto play_game(SDL_Renderer *renderer) -> void {
    auto player = GameObject{renderer, 0, 320, 200, "player.bmp"};

    int gaming = true;
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

        if (keyboard_state[SDL_SCANCODE_UP]) {
            player.set_position_x(player.get_position_x() + std::cos(player.get_angle()));
            player.set_position_y(player.get_position_y() + std::sin(player.get_angle()));
        }

        if (keyboard_state[SDL_SCANCODE_DOWN]) {
            player.set_position_x(player.get_position_x() - std::cos(player.get_angle()));
            player.set_position_y(player.get_position_y() - std::sin(player.get_angle()));
        }

        if (keyboard_state[SDL_SCANCODE_LEFT]) {
            player.set_angle(player.get_angle() - M_PI / 10.0);
        }

        if (keyboard_state[SDL_SCANCODE_RIGHT]) {
            player.set_angle(player.get_angle() + M_PI / 10.0);
        }

        SDL_SetRenderDrawColor(renderer, 200, 100, 100, 255);
        SDL_RenderClear(renderer);

        player.render();

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    player.destroy();
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