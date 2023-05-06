#include "GameObject.h"
#include "config.h"
#include "utils.h"
#include <SDL.h>
#include <cmath>
#include <memory>
#include <string>

auto _game_object_instance_count = 0;

GameObject::GameObject(
    std::shared_ptr<SDL_Renderer> renderer,
    double angle,
    double position_x,
    double position_y,
    std::string texture_filename) {
    this->id = _game_object_instance_count++;

    this->renderer = renderer;
    this->angle = normalize_angle(angle);
    this->position_x = position_x;
    this->position_y = position_y;

    auto *bmp = SDL_LoadBMP(("assets/" + texture_filename).c_str());
    if (!bmp) {
        throw std::invalid_argument("Could not load bmp");
    }

    SDL_SetColorKey(bmp, SDL_TRUE, 0x0ffffff);
    auto *texture = SDL_CreateTextureFromSurface(renderer.get(), bmp);
    if (!texture) {
        throw std::invalid_argument("Could not create texture");
    }

    SDL_FreeSurface(bmp);

    this->texture = {texture,
                     [](SDL_Texture *ptr) {
                         SDL_DestroyTexture(ptr);
                     }};

    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    this->rect = SDL_Rect{0, 0, w, h};
}

auto GameObject::set_angle(double angle) -> void {
    this->angle = normalize_angle(angle);
}

auto GameObject::set_position_x(double x) -> void {
    auto half_width = this->rect.w / 2;

    if (x < half_width || x >= WINDOW_WIDTH - half_width) {
        return;
    }

    this->position_x = x;
}

auto GameObject::set_position_y(double y) -> void {
    auto half_height = this->rect.w / 2;

    if (y < half_height || y >= WINDOW_HEIGHT - half_height) {
        return;
    }

    this->position_y = y;
}

auto GameObject::render() -> void {
    this->rect.x = this->position_x - this->rect.w / 2;
    this->rect.y = this->position_y - this->rect.h / 2;

    SDL_RenderCopyEx(this->renderer.get(),
                     this->texture.get(),
                     nullptr,
                     &this->rect,
                     this->angle,
                     nullptr,
                     SDL_FLIP_NONE);
}

auto GameObject::calculate_closest_inner_point(double target_x, double target_y)
    -> std::pair<double, double> {
    auto rect = this->get_rect();

    auto angle_in_radians = this->get_angle_in_radians();
    auto x = this->get_position_x();
    auto y = this->get_position_y();

    auto half_width = rect.w / 2.0;
    auto half_height = rect.h / 2.0;

    auto x_radius = half_width *
                        std::cos(angle_in_radians) +
                    half_height *
                        std::sin(angle_in_radians);

    auto y_radius = half_width *
                        std::sin(angle_in_radians) +
                    half_height *
                        std::cos(angle_in_radians);

    auto min_boundary_x = x - x_radius;
    auto max_boundary_x = x + x_radius;
    auto min_boundary_y = y - y_radius;
    auto max_boundary_y = y + y_radius;

    auto closest_x = std::abs(target_x - min_boundary_x) <
                             std::abs(target_x - max_boundary_x)
                         ? min_boundary_x
                         : max_boundary_x;

    auto closest_y = std::abs(target_y - min_boundary_y) <
                             std::abs(target_y - max_boundary_y)
                         ? min_boundary_y
                         : max_boundary_y;

    if (target_x < max_boundary_x && target_x > min_boundary_x) {
        closest_x = target_x;
    }

    if (target_y < max_boundary_y && target_y > min_boundary_y) {
        closest_y = target_y;
    }

    return {closest_x, closest_y};
}
