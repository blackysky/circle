//
// Created by Pavel Slabunov on 29.03.26.
//

#pragma once

#include <optional>
#include <string>

enum class ReligionType : uint8_t {
    None,
    Atheism,
    Christianity,
    Islam,
    Buddhism,
    Hinduism,
    Judaism,
    Other,
    Unknown
};

struct Religion {
    ReligionType                observed;    // what they present
    std::optional<ReligionType> actual;      // absent = no reason to doubt observed
    std::optional<std::string>  other_label; // used when type == Other
};
