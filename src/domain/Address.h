//
// Created by Pavel Slabunov on 29.03.26.
//

#pragma once

#include <optional>
#include <string>

enum class AddressType : uint8_t {
    Home,
    Work,
    School,
    Gym,
    Verein,
    Other
};

struct Address {
    std::string                city;
    std::string                country;
    std::optional<std::string> street; // often unknown
};

struct TaggedAddress {
    AddressType                type;
    std::optional<std::string> label; // e.g. "B. Braun"
    Address                    location;
    std::optional<std::string> notes;
};
