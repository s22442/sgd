#include "config.h"
#include <SDL.h>
#include <cmath>
#include <memory>
#include <string>

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

auto _normalize_angle(int angle) {
    return (angle + 360) % 360;
}

class GameObject {
protected:
    SDL_Renderer *renderer;
    int angle;
    double position_x;
    double position_y;
    SDL_Texture *texture;
    SDL_Rect rect;

    auto degrees_to_radians(double degrees) -> double {
        return degrees * (M_PI / 180);
    }

public:
    GameObject(
        SDL_Renderer *renderer,
        int angle,
        double position_x,
        double position_y,
        std::string texture_filename) {
        this->renderer = renderer;
        this->angle = _normalize_angle(angle);
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

    auto get_angle_in_radians() -> double {
        return this->degrees_to_radians(this->angle);
    }

    auto get_position_x() {
        return this->position_x;
    }

    auto get_position_y() {
        return this->position_y;
    }

    auto get_rect() {
        return this->rect;
    }

    auto set_angle(int angle) {
        this->angle = _normalize_angle(angle);
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

    auto calculate_closest_inner_point(double target_x, double target_y) -> std::pair<int, int> {
        auto rect = this->get_rect();

        auto angle_in_radians = this->get_angle_in_radians();
        auto x = this->get_position_x();
        auto y = this->get_position_y();

        auto half_width = rect.w / 2;
        auto half_height = rect.h / 2;

        auto x_radius = half_width *
                            std::cos(angle_in_radians) +
                        half_height *
                            std::sin(angle_in_radians);

        auto y_radius = half_width *
                            std::sin(angle_in_radians) +
                        half_height *
                            std::cos(angle_in_radians);

        auto closest_x = target_x > x
                             ? std::min(target_x, x + x_radius)
                             : std::max(target_x, x - x_radius);

        auto closest_y = target_y > y
                             ? std::min(target_y, y + y_radius)
                             : std::max(target_y, y - y_radius);

        return {closest_x, closest_y};
    }

    ~GameObject() {
        SDL_DestroyTexture(this->texture);
    }
};

#endif // GAME_OBJECT_H