//
// Created by Pavel Slabunov on 29.03.26.
//

#pragma once

#include <string>

struct ThreatInfo {
    bool        active = false;
    std::string reason; // required when active = true; ignored otherwise
};
