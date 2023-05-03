#include "Ball.h"
#include "Brick.h"
#include "Platform.h"
#include "Wall.h"
#include "config.h"
#include "utils.h"
#include <SDL.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#define SDL_MAIN_HANDLED

auto _rd = std::random_device{};
auto _rgen = std::mt19937{_rd()};

auto init_random_ball_angle() -> double {
    return std::uniform_int_distribution<int>{
        70,
        110}(_rgen);
}

auto init_walls(std::shared_ptr<SDL_Renderer> renderer) -> std::array<Wall, 3> {
    return {
        Wall{renderer, 90, WINDOW_WIDTH / 2, WALL_EXTENSION},
        Wall{renderer, 0, WALL_EXTENSION, WINDOW_HEIGHT / 5},
        Wall{renderer, 0, WINDOW_WIDTH - WALL_EXTENSION, WINDOW_HEIGHT / 5},
    };
}

auto init_bricks(std::shared_ptr<SDL_Renderer> renderer)
    -> std::vector<Brick> {
    auto bricks = std::vector<Brick>{};

    auto first_brick_x = WINDOW_WIDTH / 2 -
                         (BRICK_CELL_WIDTH * (BRICK_COLS - 1) / 2);

    auto first_brick_y = WALL_EXTENSION +
                         BRICK_GRID_MARGIN_TOP +
                         (BRICK_CELL_HEIGHT / 2);

    for (auto row_i : range(BRICK_ROWS)) {
        for (auto col_i : range(BRICK_COLS)) {
            bricks.push_back(
                Brick{
                    renderer,
                    0,
                    (double)(first_brick_x + (col_i * BRICK_CELL_WIDTH)),
                    (double)(first_brick_y + (row_i * BRICK_CELL_HEIGHT)),
                });
        }
    }

    return bricks;
}

auto play_game(std::shared_ptr<SDL_Renderer> renderer) -> void {
    auto walls = init_walls(renderer);
    auto bricks = init_bricks(renderer);

    auto platform = Platform{
        renderer,
        0,
        WINDOW_WIDTH / 2,
        WINDOW_HEIGHT * 0.9,
    };

    auto ball = Ball{
        renderer,
        init_random_ball_angle(),
        WINDOW_WIDTH / 2,
        (double)(WALL_EXTENSION +
                 BRICK_GRID_MARGIN_TOP +
                 (BRICK_CELL_HEIGHT * BRICK_ROWS)) +
            (BRICK_CELL_HEIGHT / 2),
    };

    bool game_active = true;
    while (game_active) {
        auto e = SDL_Event{};

        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                game_active = false;
                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_q)
                    game_active = false;
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

        ball.detect_and_handle_colision(platform);

        for (auto &wall : walls) {
            ball.detect_and_handle_colision(wall);
        }

        for (auto &brick : bricks) {
            ball.detect_and_handle_colision(brick);
        }

        auto i = 0;
        while (i < bricks.size()) {
            if (bricks[i].is_destroyed()) {
                bricks.erase(bricks.begin() + i);
            } else {
                i++;
            }
        }

        SDL_SetRenderDrawColor(renderer.get(), 20, 20, 60, 255);
        SDL_RenderClear(renderer.get());

        ball.render();
        platform.render();

        for (auto &wall : walls) {
            wall.render();
        }

        for (auto &brick : bricks) {
            brick.render();
        }

        SDL_RenderPresent(renderer.get());
        SDL_Delay(10);
    }
}

auto init_window() -> std::shared_ptr<SDL_Window> {
    auto window = SDL_CreateWindow("SGD - Yet another lame Breakout clone",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   WINDOW_WIDTH, WINDOW_HEIGHT,
                                   SDL_WINDOW_SHOWN);

    return {window,
            [](SDL_Window *ptr) {
                SDL_DestroyWindow(ptr);
            }};
}

auto init_renderer(std::shared_ptr<SDL_Window> window)
    -> std::shared_ptr<SDL_Renderer> {
    auto renderer = SDL_CreateRenderer(window.get(),
                                       -1,
                                       SDL_RENDERER_ACCELERATED |
                                           SDL_RENDERER_PRESENTVSYNC);

    return {renderer,
            [](SDL_Renderer *ptr) {
                SDL_DestroyRenderer(ptr);
            }};
}

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

    auto window = init_window();
    auto renderer = init_renderer(window);

    play_game(renderer);

    SDL_Quit();

    return 0;
}