#include <filesystem>
#include <domain/Person.h>
#include <domain/RelationshipGraph.h>
#include <iostream>

#include "persistence/GraphSerializer.h"

int main() {
    RelationshipGraph graph;


    // --- Build two people ---
    Person alice;
    alice.first_name = "Alice";
    alice.surname = "Schmidt";
    alice.gender = Gender::Female;
    alice.birth_year = BirthYear{2000}; // NOLINT(*-magic-numbers)
    alice.aliases = {
        Alias{.name = "Ally", .is_primary = true},
        Alias{.name = "Schmidti", .is_primary = false}
    };

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
    rel.strength = RelationshipStrength{.tier = RelationshipTier::Friend, .intensity = 75}; // NOLINT(*-magic-numbers)
    rel.is_active = true;
    rel.metadata.evidence_level = EvidenceLevel::Observed;
    rel.metadata.meeting_frequency = MeetingFrequency::Weekly;

    const auto rel_id = graph.addRelationship(std::move(rel));

    if (!rel_id) {
        std::cerr << "Failed to add relationships.\n";
        return 1;
    }

    std::cout << "Built graph: "
            << graph.allPeople().size() << " person(s), "
            << graph.allRelationships().size() << " relationship(s).\n";


    // --- Save ---

    const std::filesystem::path save_path = "circle_test.json";
    GraphSerializer::save(graph, save_path);
    std::cout << "Saved to " << save_path << "\n";


    // --- Load ---

    const RelationshipGraph loaded = GraphSerializer::load(save_path);
    std::cout << "Loaded graph: "
            << loaded.allPeople().size() << " person(s), "
            << loaded.allRelationships().size() << " relationship(s).\n";


    // --- Verify ---

    const auto found = loaded.findPerson(*alice_id);
    if (!found) {
        std::cerr << "Alice not found after load.\n";
        return 1;
    }

    const Person *restored_alice = *found;
    std::cout << "\nRestored Alice:\n";
    std::cout << "  first_name : " << restored_alice->first_name << "\n";
    std::cout << "  surname : " << restored_alice->surname.value_or("(none)") << "\n";
    std::cout << "  birth_year : " << restored_alice->birth_year->year() << "\n";
    std::cout << "  aliases : ";
    for (const auto &[name, is_primary]: restored_alice->aliases) {
        std::cout << name << (is_primary ? " (primary)" : "") << "  ";
    }
    std::cout << "\n";

    const auto restored_rel = loaded.findRelationship(*rel_id);
    if (!restored_rel) {
        std::cerr << "Relationship not found after load.\n";
        return 1;
    }

    std::cout << "\nRestored relationship:\n";
    std::cout << "  from_id : " << (*restored_rel)->from_id << "\n";
    std::cout << "  to_id : " << (*restored_rel)->to_id << "\n";
    std::cout << "  is_active : " << std::boolalpha << (*restored_rel)->is_active << "\n";

    return 0;
}
