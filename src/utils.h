#include <cmath>
#include <vector>

#ifndef UTILS_H
#define UTILS_H

auto range(int len) -> std::vector<int>;

auto degrees_to_radians(double degrees) -> double;

auto normalize_angle(double angle) -> double;

#endif // UTILS_H
