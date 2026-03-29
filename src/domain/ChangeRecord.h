//
// Created by Pavel Slabunov on 29.03.26.
//

#pragma once

#include <chrono>
#include <optional>
#include <string>

enum class ChangeType : uint8_t {
    FieldModified, // a field value changed - system-generated
    NoteAdded      // user-authored narrative entry
};

struct ChangeRecord {
    std::chrono::system_clock::time_point timestamp;
    ChangeType                            type;
    std::optional<std::string>            field_name; // set when FieldModified
    std::optional<std::string>            old_value;  // serialised as string
    std::optional<std::string>            new_value;  // serialised as string
    std::optional<std::string>            note;       // set when NoteAdded
};
