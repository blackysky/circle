//
// Created by Pavel Slabunov on 30.03.26.
//

#pragma once
#include <filesystem>

#include "domain/RelationshipGraph.h"

namespace GraphSerializer {
    // Serialises the entire graph to a JSON file at the given path.
    // Throws std::runtime_error if the file cannot be written.
    void save(const RelationshipGraph &graph, const std::filesystem::path &path);

    // Deserialises a graph from a JSON file at the given path.
    // Throws std::runtime_error if the file cannot be read or is malformed.
    RelationshipGraph load(const std::filesystem::path &path);
} // namespace GraphSerializer
