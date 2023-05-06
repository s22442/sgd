#include "config.h"
#include "utils.h"
#include <SDL.h>
#include <cmath>
#include <memory>
#include <string>

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject {
protected:
    int id;
    std::shared_ptr<SDL_Renderer> renderer;
    double angle;
    double position_x;
    double position_y;
    std::shared_ptr<SDL_Texture> texture;
    SDL_Rect rect;

public:
    GameObject(
        std::shared_ptr<SDL_Renderer> renderer,
        double angle,
        double position_x,
        double position_y,
        std::string texture_filename);

    inline auto get_id() {
        return this->id;
    }

    inline auto get_angle() {
        return this->angle;
    }

    inline auto get_angle_in_radians() -> double {
        return degrees_to_radians(this->angle);
    }

    inline auto get_position_x() {
        return this->position_x;
    }

    inline auto get_position_y() {
        return this->position_y;
    }

    inline auto get_rect() {
        return this->rect;
    }

    auto set_angle(double angle) -> void;

    auto set_position_x(double x) -> void;

    auto set_position_y(double y) -> void;

    auto render() -> void;

    auto calculate_closest_inner_point(double target_x, double target_y)
        -> std::pair<double, double>;
};

#endif // GAME_OBJECT_H