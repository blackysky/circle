//
// Created by Pavel Slabunov on 29.03.26.
//

#pragma once

#include <cstdint>

class BirthYear {
public:
    explicit BirthYear(const uint16_t year, const bool approximate = false)
        : year_(year), is_approximate_(approximate) {
    }

    [[nodiscard]] uint16_t year() const { return year_; }
    [[nodiscard]] bool     is_approximate() const { return is_approximate_; }

private:
    uint16_t year_;
    bool     is_approximate_;
};
