//
// Created by Pavel Slabunov on 29.03.26.
//

#pragma once

#include <chrono>
#include <optional>
#include <string>
#include <vector>

#include "Person.h"
#include "RelationshipMetadata.h"
#include "RelationshipStrength.h"
#include "ThreatInfo.h"

using RelationshipId = uint64_t;

enum class RelationshipType : uint8_t {
    KnowsOf, // directed: from knows of to, not necessarily vice versa
    Acquaintance,
    Colleague,
    Friend,
    Romantic,
    Family,
    Adversarial,
    Other
};

struct Relationship {
    // Identity
    RelationshipId id;
    PersonId       from_id; // the one who knows / initiates
    PersonId       to_id;   // the one being known

    // Classification
    RelationshipType           type;
    std::optional<std::string> type_label; // free text when type = Other, or extra content otherwise

    RelationshipStrength strength;

    // My role
    std::optional<std::string> my_relationship_role; // e.g. "friend"
    // only relevant on edges
    // connected to the 'self' node

    bool is_active = true;

    // Threat
    ThreatInfo threat_to_from; // does 'to' pose a threat to 'from'?
    ThreatInfo threat_to_me;   // does this relationship pose a threat to me?

    // Observational
    RelationshipMetadata metadata;

    // Freeform
    std::optional<std::string> notes;

    // Audit
    std::chrono::system_clock::time_point created_at;
    std::vector<ChangeRecord>             change_history;
};
