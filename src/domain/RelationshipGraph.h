//
// Created by Pavel Slabunov on 29.03.26.
//

#pragma once

#include <chrono>
#include <optional>
#include <unordered_map>
#include <vector>

#include "Person.h"
#include "Relationship.h"

class RelationshipGraph {
public:
    // --- Person ---

    // Takes ownership of a Person. Sets id and created_at internally.
    // Returns the assigned PersonId, or absent if input is invalid.
    std::optional<PersonId> addPerson(Person person);

    // Returns absent if no person with that ID exists.
    [[nodiscard]] std::optional<const Person *> findPerson(PersonId personId) const;

    // Removes the person and all relationships involving them.
    // Returns false if the ID did not exist.
    bool removePerson(PersonId personId);


    // --- Relationship ---

    // Takes ownership of a Relationship. Sets id and created_at internally.
    // Returns absent if either PersonId does not exist, or from_id == to_id.
    std::optional<RelationshipId> addRelationship(Relationship relationship);

    // Returns absent if no relationship with that ID exists.
    [[nodiscard]] std::optional<const Relationship *> findRelationship(RelationshipId relationshipId) const;

    // Returns false if the ID did not exist.
    bool removeRelationship(RelationshipId relationshipId);


    // --- Adjacency queries ---

    // All relationships where from_id == personId.
    [[nodiscard]] std::vector<const Relationship *> outgoingRelationships(PersonId personId) const;

    // All relationships where to_id == personId.
    [[nodiscard]] std::vector<const Relationship *> incomingRelationships(PersonId personId) const;

private:
    std::unordered_map<PersonId, Person>             people_;
    std::unordered_map<RelationshipId, Relationship> relationships_;

    std::unordered_map<PersonId, std::vector<RelationshipId> > outgoing_;
    std::unordered_map<PersonId, std::vector<RelationshipId> > incoming_;

    PersonId       next_person_id_ = 1;
    RelationshipId next_relationship_id_ = 1;
};
