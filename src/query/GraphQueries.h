//
// Created by Pavel Slabunov on 30.03.26.
//

#pragma once
#include <vector>

#include "domain/Person.h"
#include "domain/RelationshipGraph.h"

namespace GraphQueries {
    // Returns all people directly reachable from personId via outgoing edges.
    // Returns an empty vector if the person doesn't exist or has no outgoing relationships.
    std::vector<const Person *> neighbours(const RelationshipGraph &graph, PersonId personId);

    // Returns the shortest directed path from 'fromId' to 'toId' as an ordered list of PersonIds,
    // including both endpoints. Returns std::nullopt if no path exists.
    std::optional<std::vector<PersonId> > shortestPath(
        const RelationshipGraph &graph,
        PersonId                 fromId,
        PersonId                 toId
    );
} // namespace GraphQueries
