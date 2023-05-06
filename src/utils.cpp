#include "utils.h"
#include <cmath>
#include <vector>

// using std::ranges::iota_view requires GCC v10
auto range(int len) -> std::vector<int> {
    auto v = std::vector<int>{};

    for (int i = 0; i < len; i++) {
        v.push_back(i);
    }

    return v;
}

auto degrees_to_radians(double degrees) -> double {
    return degrees * (M_PI / 180);
}

auto normalize_angle(double angle) -> double {
    auto normalized_angle = std::abs(angle);

    while (normalized_angle > 360) {
        normalized_angle -= 360;
    }

    if (angle < 0) {
        normalized_angle = 360 - normalized_angle;
    }

    return normalized_angle;
}
