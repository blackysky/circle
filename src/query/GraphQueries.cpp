//
// Created by Pavel Slabunov on 30.03.26.
//

#pragma once

#include <optional>
#include <queue>
#include <unordered_map>
#include <vector>

#include "GraphQueries.h"

namespace GraphQueries {
    std::vector<const Person *> neighbours(const RelationshipGraph &graph, const PersonId personId) {
        std::vector<const Person *> result;

        for (const auto *rel: graph.outgoingRelationships(personId)) {
            if (const auto found = graph.findPerson(rel->to_id)) {
                result.push_back(*found);
            }
        }

        return result;
    }

    std::optional<std::vector<PersonId> > shortestPath(
        const RelationshipGraph &graph,
        const PersonId           fromId,
        const PersonId           toId
    ) {
        if (fromId == toId) {
            return std::vector{fromId};
        }

        // For each visited node, records which node we arrived from.
        // Also serves as the visited set - if a key exists, it's been seen.
        std::unordered_map<PersonId, PersonId> came_from;

        std::queue<PersonId> frontier;
        frontier.push(fromId);
        came_from[fromId] = 0; // 0 is the reserved invalid ID - no predecessor

        while (!frontier.empty()) {
            const PersonId current = frontier.front();
            frontier.pop();

            for (const auto *rel: graph.outgoingRelationships(current)) {
                const PersonId neighbour = rel->to_id;

                if (came_from.contains(neighbour)) {
                    continue; // already visited
                }

                came_from[neighbour] = current;

                if (neighbour == toId) {
                    // Reconstruct path by walking came_from backwards
                    std::vector<PersonId> path;
                    PersonId              step = toId;

                    while (step != fromId) {
                        path.push_back(step);
                        step = came_from.at(step);
                    }
                    path.push_back(fromId);

                    std::ranges::reverse(path);
                    return path;
                }

                frontier.push(neighbour);
            }
        }

        return std::nullopt;
    }
} // namespace GraphQueries
