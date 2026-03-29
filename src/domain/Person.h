//
// Created by Pavel Slabunov on 29.03.26.
//

#pragma once

#include <string>
#include <vector>
#include <optional>
#include <chrono>

#include "Address.h"
#include "Alias.h"
#include "BirthYear.h"
#include "ChangeRecord.h"
#include "Gender.h"
#include "Religion.h"
#include "SexualOrientation.h"

using PersonId = uint64_t;

struct Person {
    // Identity
    PersonId                   id;
    std::string                first_name;
    std::optional<std::string> surname;
    std::vector<Alias>         aliases;
    Gender                     gender = Gender::Unspecified;

    // Demographics
    std::optional<BirthYear>         birth_year;
    std::optional<SexualOrientation> sexual_orientation;
    std::optional<Religion>          religion;

    // Location
    std::vector<TaggedAddress> addresses;

    // Freeform
    std::optional<std::string> notes;

    // Audit
    std::chrono::system_clock::time_point created_at;
    std::vector<ChangeRecord>             change_history;
};
