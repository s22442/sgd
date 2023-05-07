#ifndef CONFIG_H
#define CONFIG_H

inline const auto WINDOW_WIDTH = 800; // px

inline const auto WINDOW_HEIGHT = 600; // px

inline auto const TARGET_DELTA_TIME = 1000 / 60.0;

inline auto const MAX_DELTA_TIME = 10.0;

inline const auto BALL_SPEED = 8;

inline const auto INITIAL_BALL_SPEED = 4;

inline const auto PLATFORM_SPEED = 12;

inline const auto WALL_EXTENSION = 10; // px

inline const auto BRICK_GRID_MARGIN_TOP = 60; // px

inline const auto BRICK_COLS = 9; // px

inline const auto BRICK_ROWS = 6; // px

inline const auto BRICK_CELL_WIDTH = 76; // px

inline const auto BRICK_CELL_HEIGHT = 32; // px

#endif // CONFIG_H
