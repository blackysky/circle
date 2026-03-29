//
// Created by Pavel Slabunov on 29.03.26.
//

#pragma once

#include <optional>
#include <string>

enum class MeetingFrequency : uint8_t {
    Daily,
    Weekly,
    Monthly,
    Occasionally,
    Rarely
};

enum class EvidenceLevel : uint8_t {
    Assumed,  // my inference, no direct evidence
    Reported, // told by a third party
    Observed, // i witnessed it directly
    Confirmed // confirmed by the person themselves
};

struct RelationshipMetadata {
    std::optional<MeetingFrequency> meeting_frequency;
    std::optional<std::string>      meeting_context; // e.g. "weekly verein"
    EvidenceLevel                   evidence_level = EvidenceLevel::Assumed;
    std::optional<std::string>      how_they_met;
};
