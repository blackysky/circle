#include <domain/Person.h>
#include <domain/RelationshipGraph.h>
#include <iostream>

int main() {
    RelationshipGraph graph;

    // --- Build two people ---
    Person alice;
    alice.first_name = "Alice";
    alice.surname = "Schmidt";
    alice.gender = Gender::Female;
    alice.birth_year = BirthYear{2000}; // NOLINT(*-magic-numbers)
    alice.aliases = {Alias{"Ally", true}, Alias{"Schmidti", false}};

    Person bob;
    bob.first_name = "Bob";
    bob.gender = Gender::Male;
    bob.birth_year = BirthYear{1990, true}; // approximate // NOLINT(*-magic-numbers)


    // --- Adding to the graph ---
    const auto alice_id = graph.addPerson(std::move(alice));
    const auto bob_id = graph.addPerson(std::move(bob));

    if (!alice_id || !bob_id) {
        std::cerr << "Failed to add persons.\n";
        return 1;
    }

    std::cout << "Added Alice with ID: " << *alice_id << "\n";
    std::cout << "Added Bob with ID: " << *bob_id << "\n";


    // --- Build relationship: Bob is Alice's friend ---
    Relationship rel;
    rel.from_id = *alice_id;
    rel.to_id = *bob_id;
    rel.type = RelationshipType::Friend;
    rel.strength = RelationshipStrength{RelationshipTier::Friend, 75}; // NOLINT(*-magic-numbers)
    rel.is_active = true;
    rel.metadata.evidence_level = EvidenceLevel::Observed;
    rel.metadata.meeting_frequency = MeetingFrequency::Weekly;

    const auto rel_id = graph.addRelationship(std::move(rel));

    if (!rel_id) {
        std::cerr << "Failed to add relationships.\n";
        return 1;
    }

    std::cout << "Added relationship with ID: " << *rel_id << "\n";


    // --- Query: outgoing relationships from Alice ---

    std::cout << "\nOutgoing relationships from Alice:\n";

    for (const auto *relationship: graph.outgoingRelationships(*alice_id)) {
        const auto target = graph.findPerson(relationship->to_id);
        if (!target) {
            continue;
        }

        const Person *person = *target;
        std::cout << "  -> " << person->first_name;
        if (person->surname) {
            std::cout << " " << *person->surname;
        }
        std::cout << "  (relationship ID: " << relationship->id << ")\n";
    }


    // --- Query: find Alice directly and print her aliases ---

    if (const auto found = graph.findPerson(*alice_id)) {
        const Person *person = *found;
        std::cout << "\nAliases for " << person->first_name << ":\n";
        for (const auto &alias: person->aliases) {
            std::cout << "  " << alias.name
                    << (alias.is_primary ? " (primary)" : "") << "\n";
        }
    }


    // --- Remove Bob and verify cascade ---

    graph.removePerson(*bob_id);
    std::cout << "\nRemoved Bob.\n";

    const auto &remaining = graph.outgoingRelationships(*alice_id);
    std::cout << "Alice's outgoing relationships after removal: "
            << remaining.size() << "\n";

    return 0;
}
