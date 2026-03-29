//
// Created by Pavel Slabunov on 29.03.26.
//

#pragma once

#include <cstdint>

enum class RelationshipTier : uint8_t {
    HeardOf,      // 0 - know they exist, no direct contact
    Acquaintance, // 1 - met, exchangeable pleasantries
    Colleague,    // 2 - work/activity context, regular contact
    Friend,       // 3 - genuine personal connection
    CloseFriend,  // 4 - trusted, regular, personal
    Intimate,     // 5 - partner, best friend, inner circle
    Family        // 6 - blood or legal family
};

struct RelationshipStrength {
    static constexpr uint8_t DEFAULT_INTENSITY = 50;

    RelationshipTier tier = RelationshipTier::HeardOf;
    uint8_t          intensity = DEFAULT_INTENSITY; // 0-100, gradation within the tier
};
