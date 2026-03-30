//
// Created by Pavel Slabunov on 30.03.26.
//

#include "RelationshipGraph.h"

// --- Person ---

std::optional<PersonId> RelationshipGraph::addPerson(Person person) {
    if (person.first_name.empty()) {
        return std::nullopt;
    }

    const PersonId person_id = next_person_id_++;
    person.id = person_id;
    person.created_at = std::chrono::system_clock::now();

    people_.emplace(person_id, std::move(person));
    outgoing_.emplace(person_id, std::vector<RelationshipId>{});
    incoming_.emplace(person_id, std::vector<RelationshipId>{});

    return person_id;
}

std::optional<const Person *> RelationshipGraph::findPerson(const PersonId personId) const {
    const auto person_it = people_.find(personId);
    if (person_it == people_.end()) {
        return std::nullopt;
    }
    return &person_it->second;
}

bool RelationshipGraph::removePerson(const PersonId personId) {
    if (!people_.contains(personId)) {
        return false;
    }

    // Collect all relationship IDs touching this person before removing anything.
    std::vector<RelationshipId> to_remove;
    for (const auto rel_id: outgoing_.at(personId)) {
        to_remove.push_back(rel_id);
    }
    for (const auto rel_id: incoming_.at(personId)) {
        to_remove.push_back(rel_id);
    }

    for (const auto rel_id: to_remove) {
        removeRelationship(rel_id);
    }

    outgoing_.erase(personId);
    incoming_.erase(personId);
    people_.erase(personId);

    return true;
}


// --- Relationship ---

std::optional<RelationshipId> RelationshipGraph::addRelationship(Relationship relationship) {
    if (!people_.contains(relationship.from_id)) {
        return std::nullopt;
    }
    if (!people_.contains(relationship.to_id)) {
        return std::nullopt;
    }
    if (relationship.from_id == relationship.to_id) {
        return std::nullopt;
    }

    const RelationshipId relationship_id = next_relationship_id_++;
    relationship.id = relationship_id;
    relationship.created_at = std::chrono::system_clock::now();

    outgoing_.at(relationship.from_id).push_back(relationship_id);
    incoming_.at(relationship.to_id).push_back(relationship_id);

    relationships_.emplace(relationship_id, std::move(relationship));

    return relationship_id;
}

std::optional<const Relationship *> RelationshipGraph::findRelationship(RelationshipId relationshipId) const {
    const auto relationship_it = relationships_.find(relationshipId);
    if (relationship_it == relationships_.end()) {
        return std::nullopt;
    }
    return &relationship_it->second;
}

bool RelationshipGraph::removeRelationship(RelationshipId relationshipId) {
    const auto relationship_it = relationships_.find(relationshipId);
    if (relationship_it == relationships_.end()) {
        return false;
    }

    const PersonId from_id = relationship_it->second.from_id;
    const PersonId to_id = relationship_it->second.to_id;

    auto &out = outgoing_.at(from_id);
    std::erase(out, relationshipId);

    auto &inc = incoming_.at(from_id);
    std::erase(inc, to_id);

    relationships_.erase(relationship_it);
    return true;
}


// --- Adjacency ---

std::vector<const Relationship *> RelationshipGraph::outgoingRelationships(const PersonId personId) const {
    std::vector<const Relationship *> result;
    const auto                        outgoing_it = outgoing_.find(personId);
    if (outgoing_it == outgoing_.end()) {
        return result;
    }

    for (const auto rel_id: outgoing_it->second) {
        result.push_back(&relationships_.at(rel_id));
    }
    return result;
}

std::vector<const Relationship *> RelationshipGraph::incomingRelationships(const PersonId personId) const {
    std::vector<const Relationship *> result;
    const auto                        incoming_it = incoming_.find(personId);
    if (incoming_it == incoming_.end()) {
        return result;
    }

    for (const auto rel_id: incoming_it->second) {
        result.push_back(&relationships_.at(rel_id));
    }
    return result;
}
