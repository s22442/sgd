#include "Ball.h"
#include "Brick.h"
#include "Platform.h"
#include "Wall.h"
#include "config.h"
#include <SDL.h>
#include <array>
#include <cmath>
#include <iostream>
#include <memory>

#define SDL_MAIN_HANDLED

auto play_game(SDL_Renderer *renderer) -> void {
    auto left_wall = Wall{renderer, 0, 10, WINDOW_HEIGHT / 6};
    auto right_wall = Wall{renderer, 0, WINDOW_WIDTH - 10, WINDOW_HEIGHT / 6};
    auto top_wall = Wall{renderer, 90, WINDOW_WIDTH / 2, 10};

    auto platform = Platform{renderer, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT * 0.9};
    auto ball = Ball{renderer, -30, WINDOW_WIDTH / 2, WINDOW_HEIGHT * 0.6};

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
            platform.move_left();
        }

        if (keyboard_state[SDL_SCANCODE_RIGHT]) {
            platform.move_right();
        }

        ball.update_position();

        ball.detect_and_handle_colision(top_wall);
        ball.detect_and_handle_colision(left_wall);
        ball.detect_and_handle_colision(right_wall);

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