//
// Created by Pavel Slabunov on 29.03.26.
//

#pragma once

#include <string>

struct Alias {
    std::string name;
    bool        is_primary = false; // at most one per Person should be true
};
